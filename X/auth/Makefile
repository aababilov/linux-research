CFLAGS := -Wall `pkg-config --cflags x11 xcb xau`
LDFLAGS := -Wall `pkg-config --libs x11 xcb xau`

all: auth

auth: auth.o
	$(CC) -o $@ $^ $(LDFLAGS)