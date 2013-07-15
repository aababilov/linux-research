CC=gcc
CFLAGS+= -g
LDFLAGS=-lglut
EXECNAME=mountain

all: $(EXECNAME)

clean:
	-rm -f *.o *.a *~
	
$(EXECNAME): main.o
	$(CC) -o $@ $^ $(LDFLAGS) 