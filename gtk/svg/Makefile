CC := gcc

all: svg

svg: svg.c
	$(CC) -o $@ $^ `pkg-config --libs --cflags gtk+-2.0`