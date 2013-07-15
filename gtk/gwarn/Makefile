all: gwarn

gwarn: gwarn.c
	$(CC) -o $@ $^ `pkg-config --cflags --libs glib-2.0`