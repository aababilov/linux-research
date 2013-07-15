CFLAGS += `pkg-config --cflags gtk+-2.0`
LDFLAGS += `pkg-config --libs gtk+-2.0`

all: tray

tray: tray.o
	$(CC) -o $@ $^ $(LDFLAGS)
