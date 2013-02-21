########### LINUX MAKEFILE FOR ISA-CLIPS ###########
### FLAGS ###
# CFLAGS - additional cflags to pass to the compiler
####################################################
INCLUDES = -I../include
OBJS = ArchitectureDetection.o OSDetection.o \
		 HardwareDetection.o Platform.o

.c.o :
	$(CC) -c $(CFLAGS) $(INCLUDES) -DLINUX -DALLOW_ENVIRONMENT_GLOBALS=0 -std=c99 -Wall -Wundef -Wpointer-arith -Wshadow -Wcast-qual \
	    -Wcast-align -Winline -Wmissing-declarations -Wredundant-decls \
	    -Woverloaded-virtual -Wmissing-prototypes -Wnested-externs \
	    -Wstrict-prototypes -Waggregate-return -Wno-implicit $<

.PHONY: all
all: $(OBJS)
	$(AR) $(ARFLAGS) adventure-engine-platform.a $(OBJS)

ArchitectureDetection.o: ArchitectureDetection.c 

OSDetection.o: OSDetection.c 

HardwareDetection.o: HardwareDetection.c 

Platform.o: Platform.c 

.PHONY: clean
clean:
	rm -f *.o adventure-engine-platform.a
