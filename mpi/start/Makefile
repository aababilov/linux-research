PROGNAME := start
EXENAME := $(PROGNAME)
CC := mpicc

all: $(EXENAME)

$(EXENAME): start.o
	$(CC) -o $@ $^

clean:
	$(RM) *.o
