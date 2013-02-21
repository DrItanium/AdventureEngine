########### LINUX MAKEFILE FOR ISA-CLIPS ###########
### FLAGS ###
# COMPILER - sets the compiler to use
# OUTPUT - sets the name of the resulting executable
# CFLAGS - additional cflags to pass to the compiler
####################################################
OUTPUT = adventure-engine 
OBJS = main.o userfunctions.o
ARCHIVES = platform/adventure-engine-platform.a clips/clips.a
SUBDIRS = platform clips
INCLUDES = -Iinclude/

.c.o :
	$(CC) -c $(CFLAGS) $(INCLUDES) -DLINUX -DALLOW_ENVIRONMENT_GLOBALS=0 -std=c99 -Wall -Wundef -Wpointer-arith -Wshadow -Wcast-qual \
	    -Wcast-align -Winline -Wmissing-declarations -Wredundant-decls \
	    -Woverloaded-virtual -Wmissing-prototypes -Wnested-externs \
	    -Wstrict-prototypes -Waggregate-return -Wno-implicit $<

program: subdirs $(OBJS)
	$(CC) $(CFLAGS) -o $(OUTPUT) $(OBJS) $(ARCHIVES) -lm -lncurses

.PHONY: clean sub-clean subdirs $(SUBDIRS)



subdirs: $(SUBDIRS)

$(SUBDIRS):
	$(MAKE) -C $@

clean: sub-clean
	rm -f $(OUTPUT) *.o

sub-clean: 
	for d in $(SUBDIRS); do ($(MAKE) -C $$d clean ); done
