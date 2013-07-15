#include <stdio.h>
#include <stdlib.h>
#include <glib.h>
#include <sys/time.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <linux/input.h>

typedef struct _InputData InputData;
struct _InputData
{
	struct input_event event;
	gsize offset;
	gboolean button_has_state;
	gboolean button_state;
	int id;
};

static void
destroy_data (InputData *data)
{
	g_free (data);
}

gboolean
event_callback(GIOChannel *channel, GIOCondition condition, gpointer data)
{
	struct timeval tnow;	
	struct tm *tloc;
	InputData  *input_data = (InputData*)data;
	gsize read_bytes;

	if (condition & (G_IO_HUP | G_IO_ERR | G_IO_NVAL)) {
		return FALSE;
	}

	/** tbh, we can probably assume every time we read we have a whole
	 * event availiable, but hey..*/
	while (g_io_channel_read_chars (
		       channel,
		       ((gchar*)&input_data->event) + input_data->offset,
		       sizeof(struct input_event) - input_data->offset,
		       &read_bytes, NULL) == G_IO_STATUS_NORMAL) {
		if (input_data->offset + read_bytes < sizeof (struct input_event)) {
			input_data->offset = input_data->offset + read_bytes;
			return TRUE;
		} else {
			input_data->offset = 0;
		}
	}

	gettimeofday(&tnow, NULL);
        tloc = localtime((time_t *) &tnow.tv_sec);
        printf("%02d:%02d:%02d: ", tloc->tm_hour, tloc->tm_min, tloc->tm_sec);
	printf("input on %d\n", input_data->id);
	return TRUE;
}

gboolean add_listener(const char *filename, int num)
{
	GIOChannel *chan;
	InputData *data;

	chan = g_io_channel_new_file(filename, "r", NULL);
	if (!chan) {
		printf("not opened %s\n", filename);
		return FALSE;
	}
	printf("opened %s\n", filename);

	data = (InputData*)g_malloc(sizeof (InputData));
	memset(data, 0, sizeof (InputData));
	data->id = num;
	g_io_add_watch_full(
		chan,
		G_PRIORITY_DEFAULT,
		G_IO_IN | G_IO_ERR | G_IO_HUP | G_IO_NVAL,
		event_callback, data,
		(GDestroyNotify)destroy_data);
	return TRUE;
}

int
main()
{
	GMainLoop *loop;
	char filename[] = "/dev/input/event0";
	int i;
	for (i = 0; i < 20; ++i) {
		filename[sizeof(filename) - 2] = i + '0';
		if (!add_listener(filename, i))
			break;
	}
	add_listener("/dev/input/mouse0", 100);
	printf("opened %d files\n", i);
	loop = g_main_loop_new(NULL, FALSE);
        g_main_loop_run(loop);
	return 0;
}
