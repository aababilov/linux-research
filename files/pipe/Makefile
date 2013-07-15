CC=gcc

all: par chi
clean: 
	-rm -f *.o *~

par: par.o
	$(CC) -o $@ $<

chi: chi.o
	$(CC) -o $@ $<