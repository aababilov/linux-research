PROGNAME := f$(shell basename $(shell pwd))
ASFLAGS += -g

all: $(PROGNAME)

clean:
	$(RM) *.o *~*

.PHONY: all clean

$(PROGNAME): $(PROGNAME).o util.o
	$(CC) -o $@ $^ 