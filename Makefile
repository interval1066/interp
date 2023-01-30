# This is a recursive makefile- do not use in production
# convert to canonical make chain when time permits
#
# recursive file search
rfilelist=$(wildcard $1$2) $(foreach d,$(wildcard $1*),$(call rfilelist,$d/,$2))
# the name of program
TARGET				= interp
CC 					= gcc
# C++ compiler flags
CFLAGS				+= -Wall -c -std=c11 #-DBANNER
CMNFLAGS				+= -Wno-unused-result -Wno-unused-function
LIBS					+= -pthread -lconfig
CEXT					= c
CXXEXT				= cc
# source files
SRC					= ./src
CSRCS     			:= $(call rfilelist,$(SRC),*.$(CEXT))
CXXSRCS     		:= $(call rfilelist,$(SRC),*.$(CXXEXT))
INCLUDES				= ./include ./include/utils
CFLAGS				+= $(addprefix -I,$(INCLUDES))
OBJS 					= $(CSRCS:%.$(CEXT)=%.o)
DEBUG_HELPERS 		= $(CSRCS:%.$(CEXT)=%.debug)
OPTIMIZE_HELPERS 	= $(CSRCS:%.$(CEXT)=%.optim)
OBJDEBOUT			= $(@:%.debug=%.o)
OBJOPTOUT			= $(@:%.optim=%.o)
DEBOUT				= $(@:%.debug=%.$(CEXT))
OPTOUT				= $(@:%.optim=%.$(CEXT))

# rules for debug build and optimized build
%.debug: %.$(CEXT)
	$(CC) $(CFLAGS) $(CMNFLAGS) -ggdb -D_DEBUG -DDEBUG -o $(OBJDEBOUT) $(DEBOUT)
	rm -f $(@.debug=%.debug)
	touch -f $@

%.optim: %.$(CEXT)
	$(CC) $(CFLAGS) $(CMNFLAGS) -O2 -DNDEBUG -o $(OBJOPTOUT) $(OPTOUT)
	rm -f $(@.optim=%.optim)
	touch -f $@

# rules for object files
%.o: %.$(CEXT)
	$(CC) $(CFLAGS) $(CMNFLAGS) $?

# default build
all: debug

# debug build
debug: $(DEBUG_HELPERS)
	test -s $@ || mkdir $@
	$(CC) $(OBJS) -o debug/$(TARGET) $(LIBS)
	rm -f $(DEBUG_HELPERS)

# optimized build
optim: $(OPTIMIZE_HELPERS)
	test -s $@ || mkdir $@
	$(CC) $(OBJS) -o optim/$(TARGET) $(LIBS)
	rm -f $(OPTIMIZE_HELPERS)
	strip optim/$(TARGET)

docs:
	doxygen interp.dox

# clean rule
clean:
	rm -f $(OBJS) $(DEBUG_HELPERS) $(OPTIMIZE_HELPERS)

