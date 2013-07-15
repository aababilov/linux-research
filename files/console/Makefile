#LDFLAGS += `pkg-config --libs dbus-1 dbus-glib-1 hal glib-2.0 gtk+-2.0`
CFLAGS += -Wall
#`pkg-config --cflags dbus-1 dbus-glib-1 hal glib-2.0 gtk+-2.0 hal` 
CXXFLAGS := $(CFLAGS)

OBJECTS := main.o getfd.o
PROGNAME := cons

all: $(PROGNAME)

clean:
	$(RM) *.o *~*

.PHONY: all clean

$(PROGNAME): $(OBJECTS)
	$(CC) -o $@ $^ $(LDFLAGS)

