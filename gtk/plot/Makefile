CC := gcc

all: plot

plot: plot.c
	$(CC) -o $@ $^ `pkg-config --libs --cflags gtk+-2.0 gtkextra-2.0`