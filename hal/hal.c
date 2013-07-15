#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <getopt.h>
#include <time.h>
#include <sys/time.h>

#include <dbus/dbus-glib-lowlevel.h>
#include <dbus/dbus-glib.h>
#include <libhal.h>
#include <gtk/gtk.h>
#include <glib.h>

LibHalContext *hal_ctx;
DBusConnection *conn;

static char *
get_time (void)
{
	struct timeval tnow;
	struct tm *tlocaltime;
	struct timezone tzone;
	static char tbuf[256];
	static char buf[256];
	GTimeVal t;

	gettimeofday (&tnow, &tzone);
	tlocaltime = localtime ((time_t *) &tnow.tv_sec);
	strftime (tbuf, sizeof (tbuf), "%H:%M:%S", tlocaltime);

	g_get_current_time (&t);
	g_snprintf (buf, sizeof(buf), "%s.%03d", tbuf, (int) (t.tv_usec / 1000));
	return buf;
}

static void
print_property (const char *udi, const char *key)
{
	int type;
	char *str;
	DBusError error;

	dbus_error_init (&error);

	type = libhal_device_get_property_type (hal_ctx, udi, key, &error);

	switch (type) {
	case LIBHAL_PROPERTY_TYPE_STRING:
		str = libhal_device_get_property_string (hal_ctx, udi, key, &error);
		printf("*** new value: '%s'  (string)\n", str);
		libhal_free_string (str);
		break;
	case LIBHAL_PROPERTY_TYPE_INT32:
		{
			dbus_int32_t value = libhal_device_get_property_int (hal_ctx, udi, key, &error);
			printf ("*** new value: %d (0x%x)  (int)\n",
				 value, value);
		}
		break;
	case LIBHAL_PROPERTY_TYPE_UINT64:
		{
			dbus_uint64_t value = libhal_device_get_property_uint64 (hal_ctx, udi, key, &error);
			printf ("*** new value: %llu (0x%llx)  (uint64)\n",
				(long long unsigned int) value, (long long unsigned int) value);
		}
		break;
	case LIBHAL_PROPERTY_TYPE_DOUBLE:
		printf ("*** new value: %g  (double)\n",
			libhal_device_get_property_double (hal_ctx, udi, key, &error));
		break;
	case LIBHAL_PROPERTY_TYPE_BOOLEAN:
		printf ("*** new value: %s  (bool)\n",
			libhal_device_get_property_bool (hal_ctx, udi, key, &error) ? "true" : "false");
		break;
	case LIBHAL_PROPERTY_TYPE_STRLIST:
	{
		unsigned int i;
		char **strlist;

		printf ("*** new value: {");

		strlist = libhal_device_get_property_strlist (hal_ctx, udi, key, &error);
                /* may be NULL because property may have been removed */
                if (strlist != NULL) {
                        for (i = 0; strlist[i] != NULL; i++) {
                                printf ("'%s'", strlist[i]);
                                if (strlist[i+1] != NULL)
                                        printf (", ");
                        }
			printf ("}  (string list)\n");
			libhal_free_string_array (strlist);
                }
		break;
	}

	default:
		fprintf (stderr, "Unknown type %d='%c'\n", type, type);
		break;
	}

	if (dbus_error_is_set (&error))
		dbus_error_free (&error);
}

static gboolean aft_prop(gpointer data)
{
	printf("aft prop: %s\n", (char*)data);
	return FALSE;
}

static void
property_modified (LibHalContext *ctx,
		   const char *udi,
		   const char *key,
		   dbus_bool_t is_removed,
		   dbus_bool_t is_added)
{
	printf ("*** %s: lshal: property_modified, udi=%s, key=%s\n",
		get_time (), udi, key);
	printf ("           is_removed=%s, is_added=%s\n",
		is_removed ? "true" : "false",
		is_added ? "true" : "false");
	if (!is_removed)
		print_property(udi, key);
	printf ("\n");
	g_timeout_add_seconds(5, aft_prop, g_strdup(key));
}

static void
device_condition (LibHalContext *ctx,
		  const char *udi,
		  const char *condition_name,
		  const char *condition_details)
{
	DBusMessage    *message, *result;
	DBusError error; int wake_up = 0;

	printf ("*** %s: lshal: device_condition, udi=%s\n", get_time (), udi);
	printf ("           condition_name=%s\n", condition_name);
	printf ("           condition_details=%s\n", condition_details);
	printf ("\n");
	if (strcmp(condition_details, "sleep") &&
	    strcmp(condition_details, "lid"))
		return;
	printf("try suspend...\n");
	dbus_error_init (&error);

	message = dbus_message_new_method_call ("org.freedesktop.Hal",
						"/org/freedesktop/Hal/devices/computer",
						"org.freedesktop.Hal.Device.SystemPowerManagement",
						"Suspend");
	dbus_message_append_args (message, DBUS_TYPE_INT32, &wake_up, DBUS_TYPE_INVALID);

	result = dbus_connection_send_with_reply_and_block (conn, message, 2000, &error);
	dbus_message_unref(message);
}

int main(int argc, char *argv[])
{
	DBusError error;
	GMainLoop *loop;
	dbus_error_init (&error);
	conn = dbus_bus_get (DBUS_BUS_SYSTEM, &error);
	if (conn == NULL) {
		fprintf (stderr, "error: dbus_bus_get: %s: %s\n",
			 error.name, error.message);
		LIBHAL_FREE_DBUS_ERROR (&error);
		return 1;
	}
	dbus_connection_setup_with_g_main (conn, NULL);
	if ((hal_ctx = libhal_ctx_new ()) == NULL) {
		fprintf (stderr, "error: libhal_ctx_new\n");
		return 1;
	}
	if (!libhal_ctx_set_dbus_connection (hal_ctx, conn)) {
		fprintf (stderr, "error: libhal_ctx_set_dbus_connection: %s: %s\n",
			 error.name, error.message);
		return 1;
	}
	if (!libhal_ctx_init (hal_ctx, &error)) {
		if (dbus_error_is_set(&error)) {
			fprintf (stderr, "error: libhal_ctx_init: %s: %s\n", error.name, error.message);
			dbus_error_free (&error);
		}
		fprintf (stderr, "Could not initialise connection to hald.\n"
			 "Normally this means the HAL daemon (hald) is not running or not ready.\n");
		return 1;
	}
	libhal_ctx_set_device_property_modified (hal_ctx, property_modified);
	libhal_ctx_set_device_condition(hal_ctx, device_condition);
	
	if ( libhal_device_property_watch_all (hal_ctx, &error) == FALSE) {
		fprintf (stderr, "error: monitoring devicelist - libhal_device_property_watch_all: %s: %s\n",
			 error.name, error.message);
		LIBHAL_FREE_DBUS_ERROR (&error);
		return 1;
	}
	printf ("\nStart monitoring devicelist:\n"
		"-------------------------------------------------\n");
	loop = g_main_loop_new (NULL, FALSE);
	g_main_loop_run (loop);
/*	gtk_init(&argc, &argv);
//gtk_main();*/
	if ( libhal_ctx_shutdown (hal_ctx, &error) == FALSE)
		LIBHAL_FREE_DBUS_ERROR (&error);
	libhal_ctx_free (hal_ctx);

	dbus_connection_unref (conn);
	return 0;
}
