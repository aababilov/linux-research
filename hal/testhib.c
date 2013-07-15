#include <glib.h>
#include <dbus/dbus.h>
#include <dbus/dbus-glib.h>
#include <stdio.h>
#include <stdlib.h>
DBusError error;
DBusMessage *message, *result;

DBusConnection *conn;

gboolean f()
{
	printf("hibernate...\n");
	dbus_error_init(&error);
	message = dbus_message_new_method_call("org.freedesktop.Hal",
					       "/org/freedesktop/Hal/devices/computer",
					       "org.freedesktop.Hal.Device.SystemPowerManagement",
					       "Hibernate");		
	
	result = dbus_connection_send_with_reply_and_block(conn, message, -1, &error);
	if (dbus_error_is_set(&error)) {
		printf("Couldn't send dbus message: %s\n",
			    error.message);
		dbus_error_free(&error);
	} else {
		dbus_message_unref(result);
	}
	dbus_message_unref(message);
	exit(0);
	return FALSE;
}

int main()
{
	GMainLoop *loop;	
	conn = dbus_bus_get(DBUS_BUS_SYSTEM, NULL);	
	dbus_connection_setup_with_g_main(conn, NULL);
	loop = g_main_loop_new (NULL, FALSE);
	g_timeout_add_seconds(3, (GSourceFunc)f, NULL);
        g_main_loop_run (loop);

	return 0;
}
