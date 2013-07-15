PROGNAME := f$(shell basename $(shell pwd))
ASFLAGS += -g

all: $(PROGNAME)

clean:
	$(RM) *.o *~*

.PHONY: all clean

$(PROGNAME): $(PROGNAME).o
	grep -q main $(PROGNAME).[sS] && $(CC) -o $@ $^ || $(LD) -o $@ $^