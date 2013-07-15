SUBDIRS := 1 2 3 4 5 6 7

all:
	for i in $(SUBDIRS); do \
		$(MAKE) -C $$i all; \
	done

clean:
	for i in $(SUBDIRS); do \
		$(MAKE) -C $$i clean; \
	done

.PHONY: all clean