########### LINUX MAKEFILE FOR ISA-CLIPS ###########
### FLAGS ###
# COMPILER - sets the compiler to use
# OUTPUT - sets the name of the resulting executable
# CFLAGS - additional cflags to pass to the compiler
####################################################
OUTPUT = adventure-engine 
SUBDIRS = platform clips

.PHONY: clean sub-clean subdirs $(SUBDIRS)

subdirs: $(SUBDIRS)

$(SUBDIRS):
	$(MAKE) -C $@

clean: sub-clean
	rm -f $(OUTPUT) *.o

sub-clean: 
	for d in $(SUBDIRS); do ($(MAKE) -C $$d clean ); done
