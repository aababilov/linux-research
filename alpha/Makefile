CFLAGS = -Wall `pkg-config --cflags gdk-2.0`
LDFLAGS = `pkg-config --libs gdk-2.0`

all: alpha

clean:
	$(RM) *.o *~

alpha: main.o
	$(CC) -o $@ $^ $(LDFLAGS)