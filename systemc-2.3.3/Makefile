# This is the SystemC Makefile to compile a general SystemC code
#
SYSTEMC= $put_your_systemC_dir_here 
SYSTEMC_ARCH=linux64

LIB_DIRS=$(SYSTEMC)/lib-$(SYSTEMC_ARCH)

#Include directories.
INCLUDE_DIRS = -I. -I$(SYSTEMC)/include

#header files used, for dependency checking
HEADERS = input.h output.h process.h toplevel.h

#source files used, for dependency checking
SOURCES = main.cpp 

DEPENDENCIES = \
	Makefile \
	$(HEADERS) \
	$(SOURCES)

LIBS = -lsystemc -lstdc++ -lm

TESTS = main

all: $(TESTS)
	./$(TESTS)
	@make main

$(TESTS): $(DEPENDENCIES)
	gcc -g -o $@ $(SOURCES) $(INCLUDE_DIRS) -L$(LIB_DIRS) $(LIBS)

clean:
	rm -f $(TESTS)  
