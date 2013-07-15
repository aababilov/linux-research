LDFLAGS += `pkg-config --libs glib-2.0`
CFLAGS += -Wall `pkg-config --cflags glib-2.0` 

all: ml

ml: ml.o
	$(CC) -o $@ $^ $(LDFLAGS)