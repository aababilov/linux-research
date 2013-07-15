CFLAGS := -Wall `pkg-config --cflags glib-2.0`
LDFLAGS := `pkg-config --libs glib-2.0`

all: idle

idle: idle.o
	$(CC) -o $@ $^ $(LDFLAGS)
