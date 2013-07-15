#include <stdio.h>
#include <stdlib.h>
#include <glib.h>
#include <poll.h>

typedef struct _GTimeoutSource GTimeoutSource;
static gint timer_perturb = -1;
struct _GTimeoutSource
{
  GSource     source;
  GTimeVal    expiration;
  guint       interval;
  guint	      granularity;
};

static gboolean my_timeout_prepare  (GSource     *source,
				    gint        *timeout);
static gboolean my_timeout_check    (GSource     *source);
static gboolean my_timeout_dispatch (GSource     *source,
				    GSourceFunc  callback,
				    gpointer     user_data);
GSourceFuncs my_timeout_funcs =
{
  my_timeout_prepare,
  my_timeout_check,
  my_timeout_dispatch,
  NULL
};

static void
my_timeout_set_expiration (GTimeoutSource *timeout_source,
			  GTimeVal       *current_time)
{
  guint seconds = timeout_source->interval / 1000;
  guint msecs = timeout_source->interval - seconds * 1000;
printf("%s\n", __func__);
  timeout_source->expiration.tv_sec = current_time->tv_sec + seconds;
  timeout_source->expiration.tv_usec = current_time->tv_usec + msecs * 1000;
  if (timeout_source->expiration.tv_usec >= 1000000)
    {
      timeout_source->expiration.tv_usec -= 1000000;
      timeout_source->expiration.tv_sec++;
    }
  if (timer_perturb==-1)
    {
      /*
       * we want a per machine/session unique 'random' value; try the dbus
       * address first, that has a UUID in it. If there is no dbus, use the
       * hostname for hashing.
       */
      const char *session_bus_address = g_getenv ("DBUS_SESSION_BUS_ADDRESS");
      if (!session_bus_address)
        session_bus_address = g_getenv ("HOSTNAME");
      if (session_bus_address)
        timer_perturb = ABS ((gint) g_str_hash (session_bus_address));
      else
        timer_perturb = 0;
    }
  if (timeout_source->granularity)
    {
      gint remainder;
      gint gran; /* in usecs */
      gint perturb;

      gran = timeout_source->granularity * 1000;
      perturb = timer_perturb % gran;
      /*
       * We want to give each machine a per machine pertubation;
       * shift time back first, and forward later after the rounding
       */

      timeout_source->expiration.tv_usec -= perturb;
      if (timeout_source->expiration.tv_usec < 0)
        {
          timeout_source->expiration.tv_usec += 1000000;
          timeout_source->expiration.tv_sec--;
        }

      remainder = timeout_source->expiration.tv_usec % gran;
      if (remainder >= gran/4) /* round up */
        timeout_source->expiration.tv_usec += gran;
      timeout_source->expiration.tv_usec -= remainder;
      /* shift back */
      timeout_source->expiration.tv_usec += perturb;

      /* the rounding may have overflown tv_usec */
      while (timeout_source->expiration.tv_usec > 1000000)
        {
          timeout_source->expiration.tv_usec -= 1000000;
          timeout_source->expiration.tv_sec++;
        }
    }
}

static gboolean
my_timeout_prepare (GSource *source,
		   gint    *timeout)
{
  glong sec;
  glong msec;
  GTimeVal current_time;
  
  GTimeoutSource *timeout_source = (GTimeoutSource *)source;
  printf("%s\n", __func__);
  g_source_get_current_time (source, &current_time);

  sec = timeout_source->expiration.tv_sec - current_time.tv_sec;
  msec = (timeout_source->expiration.tv_usec - current_time.tv_usec) / 1000;

  /* We do the following in a rather convoluted fashion to deal with
   * the fact that we don't have an integral type big enough to hold
   * the difference of two timevals in millseconds.
   */
  if (sec < 0 || (sec == 0 && msec < 0))
    msec = 0;
  else
    {
      glong interval_sec = timeout_source->interval / 1000;
      glong interval_msec = timeout_source->interval % 1000;

      if (msec < 0)
	{
	  msec += 1000;
	  sec -= 1;
	}
      
      if (sec > interval_sec ||
	  (sec == interval_sec && msec > interval_msec))
	{
	  /* The system time has been set backwards, so we
	   * reset the expiration time to now + timeout_source->interval;
	   * this at least avoids hanging for long periods of time.
	   */
	  my_timeout_set_expiration (timeout_source, &current_time);
	  msec = MIN (G_MAXINT, timeout_source->interval);
	}
      else
	{
	  msec = MIN (G_MAXINT, (guint)msec + 1000 * (guint)sec);
	}
    }

  *timeout = (gint)msec;
  
  return msec == 0;
}

static gboolean 
my_timeout_check (GSource *source)
{
  GTimeVal current_time;
  GTimeoutSource *timeout_source = (GTimeoutSource *)source;
  printf("%s\n", __func__);
  g_source_get_current_time (source, &current_time);
  
  return ((timeout_source->expiration.tv_sec < current_time.tv_sec) ||
	  ((timeout_source->expiration.tv_sec == current_time.tv_sec) &&
	   (timeout_source->expiration.tv_usec <= current_time.tv_usec)));
}

static gboolean
my_timeout_dispatch (GSource     *source,
		    GSourceFunc  callback,
		    gpointer     user_data)
{
  GTimeoutSource *timeout_source = (GTimeoutSource *)source;
  printf("%s\n", __func__);
  if (!callback)
    {
      g_warning ("Timeout source dispatched without callback\n"
		 "You must call g_source_set_callback().");
      return FALSE;
    }
 
  if (callback (user_data))
    {
      GTimeVal current_time;

      g_source_get_current_time (source, &current_time);
      my_timeout_set_expiration (timeout_source, &current_time);

      return TRUE;
    }
  else
    return FALSE;
}

/**
 * my_timeout_source_new:
 * @interval: the timeout interval in milliseconds.
 * 
 * Creates a new timeout source.
 *
 * The source will not initially be associated with any #GMainContext
 * and must be added to one with g_source_attach() before it will be
 * executed.
 * 
 * Return value: the newly-created timeout source
 **/
GSource *
my_timeout_source_new (guint interval)
{
  GSource *source = g_source_new (&my_timeout_funcs, sizeof (GTimeoutSource));
  GTimeoutSource *timeout_source = (GTimeoutSource *)source;
  GTimeVal current_time;

  timeout_source->interval = interval;

  g_get_current_time (&current_time);
  my_timeout_set_expiration (timeout_source, &current_time);
  
  return source;
}

/**
 * my_timeout_source_new_seconds:
 * @interval: the timeout interval in seconds
 *
 * Creates a new timeout source.
 *
 * The source will not initially be associated with any #GMainContext
 * and must be added to one with g_source_attach() before it will be
 * executed.
 *
 * The scheduling granularity/accuracy of this timeout source will be
 * in seconds.
 *
 * Return value: the newly-created timeout source
 *
 * Since: 2.14	
 **/
GSource *
my_timeout_source_new_seconds (guint interval)
{
  GSource *source = g_source_new (&my_timeout_funcs, sizeof (GTimeoutSource));
  GTimeoutSource *timeout_source = (GTimeoutSource *)source;
  GTimeVal current_time;

  timeout_source->interval = 1000*interval;
  timeout_source->granularity = 1000;

  g_get_current_time (&current_time);
  my_timeout_set_expiration (timeout_source, &current_time);

  return source;
}


/**
 * my_timeout_add_full:
 * @priority: the priority of the timeout source. Typically this will be in
 *            the range between #G_PRIORITY_DEFAULT and #G_PRIORITY_HIGH.
 * @interval: the time between calls to the function, in milliseconds
 *             (1/1000ths of a second)
 * @function: function to call
 * @data:     data to pass to @function
 * @notify:   function to call when the timeout is removed, or %NULL
 * 
 * Sets a function to be called at regular intervals, with the given
 * priority.  The function is called repeatedly until it returns
 * %FALSE, at which point the timeout is automatically destroyed and
 * the function will not be called again.  The @notify function is
 * called when the timeout is destroyed.  The first call to the
 * function will be at the end of the first @interval.
 *
 * Note that timeout functions may be delayed, due to the processing of other
 * event sources. Thus they should not be relied on for precise timing.
 * After each call to the timeout function, the time of the next
 * timeout is recalculated based on the current time and the given interval
 * (it does not try to 'catch up' time lost in delays).
 * 
 * Return value: the ID (greater than 0) of the event source.
 **/
guint
my_timeout_add_full (gint           priority,
		    guint          interval,
		    GSourceFunc    function,
		    gpointer       data,
		    GDestroyNotify notify)
{
  GSource *source;
  guint id;
  
  g_return_val_if_fail (function != NULL, 0);

  source = my_timeout_source_new (interval);

  if (priority != G_PRIORITY_DEFAULT)
    g_source_set_priority (source, priority);

  g_source_set_callback (source, function, data, notify);
  id = g_source_attach (source, NULL);
  g_source_unref (source);

  return id;
}

/**
 * my_timeout_add:
 * @interval: the time between calls to the function, in milliseconds
 *             (1/1000ths of a second)
 * @function: function to call
 * @data:     data to pass to @function
 * 
 * Sets a function to be called at regular intervals, with the default
 * priority, #G_PRIORITY_DEFAULT.  The function is called repeatedly
 * until it returns %FALSE, at which point the timeout is automatically
 * destroyed and the function will not be called again.  The first call
 * to the function will be at the end of the first @interval.
 *
 * Note that timeout functions may be delayed, due to the processing of other
 * event sources. Thus they should not be relied on for precise timing.
 * After each call to the timeout function, the time of the next
 * timeout is recalculated based on the current time and the given interval
 * (it does not try to 'catch up' time lost in delays).
 *
 * If you want to have a timer in the "seconds" range and do not care
 * about the exact time of the first call of the timer, use the
 * my_timeout_add_seconds() function; this function allows for more
 * optimizations and more efficient system power usage.
 *
 * Return value: the ID (greater than 0) of the event source.
 **/
guint
my_timeout_add (guint32        interval,
	       GSourceFunc    function,
	       gpointer       data)
{
  return my_timeout_add_full (G_PRIORITY_DEFAULT, 
			     interval, function, data, NULL);
}

/**
 * my_timeout_add_seconds_full:
 * @priority: the priority of the timeout source. Typically this will be in
 *            the range between #G_PRIORITY_DEFAULT and #G_PRIORITY_HIGH.
 * @interval: the time between calls to the function, in seconds
 * @function: function to call
 * @data:     data to pass to @function
 * @notify:   function to call when the timeout is removed, or %NULL
 *
 * Sets a function to be called at regular intervals, with @priority.
 * The function is called repeatedly until it returns %FALSE, at which
 * point the timeout is automatically destroyed and the function will
 * not be called again.
 *
 * Unlike my_timeout_add(), this function operates at whole second granularity.
 * The initial starting point of the timer is determined by the implementation
 * and the implementation is expected to group multiple timers together so that
 * they fire all at the same time.
 * To allow this grouping, the @interval to the first timer is rounded
 * and can deviate up to one second from the specified interval.
 * Subsequent timer iterations will generally run at the specified interval.
 *
 * Note that timeout functions may be delayed, due to the processing of other
 * event sources. Thus they should not be relied on for precise timing.
 * After each call to the timeout function, the time of the next
 * timeout is recalculated based on the current time and the given @interval
 *
 * If you want timing more precise than whole seconds, use my_timeout_add()
 * instead.
 *
 * The grouping of timers to fire at the same time results in a more power
 * and CPU efficient behavior so if your timer is in multiples of seconds
 * and you don't require the first timer exactly one second from now, the
 * use of my_timeout_add_seconds() is preferred over my_timeout_add().
 *
 * Return value: the ID (greater than 0) of the event source.
 *
 * Since: 2.14
 **/
guint
my_timeout_add_seconds_full (gint           priority,
                            guint32        interval,
                            GSourceFunc    function,
                            gpointer       data,
                            GDestroyNotify notify)
{
  GSource *source;
  guint id;

  g_return_val_if_fail (function != NULL, 0);

  source = my_timeout_source_new_seconds (interval);

  if (priority != G_PRIORITY_DEFAULT)
    g_source_set_priority (source, priority);

  g_source_set_callback (source, function, data, notify);
  id = g_source_attach (source, NULL);
  g_source_unref (source);

  return id;
}

/**
 * my_timeout_add_seconds:
 * @interval: the time between calls to the function, in seconds
 * @function: function to call
 * @data: data to pass to @function
 *
 * Sets a function to be called at regular intervals with the default
 * priority, #G_PRIORITY_DEFAULT. The function is called repeatedly until
 * it returns %FALSE, at which point the timeout is automatically destroyed
 * and the function will not be called again.
 *
 * See my_timeout_add_seconds_full() for the differences between
 * my_timeout_add() and my_timeout_add_seconds().
 *
 * Return value: the ID (greater than 0) of the event source.
 *
 * Since: 2.14
 **/
guint
my_timeout_add_seconds (guint       interval,
                       GSourceFunc function,
                       gpointer    data)
{
  g_return_val_if_fail (function != NULL, 0);

  return my_timeout_add_seconds_full (G_PRIORITY_DEFAULT, interval, function, data, NULL);
}

gboolean f(gpointer data)
{
	static int i = 0;
	printf("timer %d\n", i++);
	return TRUE;
}

int main()
{
	GMainLoop *loop;
	loop = g_main_loop_new(NULL, FALSE);
	my_timeout_add_seconds(3, f, NULL);	
//	g_main_loop_run(loop);
	printf("f\n");
	poll(NULL, 0, 3000);
	printf("fg\n");
	return 0;
}
