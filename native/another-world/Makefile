OBJS = AnotherWorldNative.o

.c.o :
	$(CC) -c $(CFLAGS) -std=c99 -Wall -Wundef -Wpointer-arith -Wshadow -Wcast-qual \
	    -Wcast-align -Winline -Wmissing-declarations -Wredundant-decls \
	    -Woverloaded-virtual -Wmissing-prototypes -Wnested-externs \
	    -Wstrict-prototypes -Waggregate-return -Wno-implicit $<

.PHONY: all
all: $(OBJS)

AnotherWorldNative.o: AnotherWorldNative.c AnotherWorldNative.h

.PHONY: clean
clean:
	rm -f *.o
