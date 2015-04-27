all: tem
.PHONY : all

CFLAGS := $(shell pkg-config --cflags vte-2.91 gtk+-3.0)
LDFLAGS := $(shell pkg-config --libs vte-2.91 gtk+-3.0)

tem: tem.c
	$(CC) $< $(CFLAGS) $(LDFLAGS) -o $@


clean:
	rm tem

