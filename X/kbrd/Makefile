OBJECTS := kbrd.o  keys_management.o
CFLAGS := -Wall `pkg-config --cflags gtk+-2.0`
LDFLAGS := `pkg-config --libs gtk+-2.0`

all: kbrd

clean:
	$(RM) *.o *~

kbrd: $(OBJECTS)
	$(CC) -o $@ $^ $(LDFLAGS)