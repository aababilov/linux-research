LDFLAGS += `pkg-config --libs dbus-1 dbus-glib-1 hal gtk+-2.0`
CFLAGS += -Wall `pkg-config --cflags dbus-1 dbus-glib-1 hal gtk+-2.0` 

all: haltest

haltest: hal.o
	$(CC) -o $@ $^ $(LDFLAGS)