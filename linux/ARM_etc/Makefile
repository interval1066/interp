# This is a recursive makefile- do not use in production
# convert to canonical make chain when time permits
#
# recursive file search
rfilelist=$(wildcard $1$2) $(foreach d,$(wildcard $1*),$(call rfilelist,$d/,$2))
# the name of program
TARGET				= interp
CC 					= gcc
# C++ compiler flags

LIBS					+= -pthread -lconfig
EXT					= c
# source files
SRC					= ./src
SRCS     			:= $(call rfilelist,$(SRC),*.$(EXT))
INCLUDES				= ./include ./include/utils
CFLAGS				:= -Wall -std=c11 -c
CFLAGS				+= $(addprefix -I,$(INCLUDES))
OBJS 					= $(SRCS:%.$(EXT)=%.o)
DEBUG_HELPERS 		= $(SRCS:%.$(EXT)=%.debug)
OPTIMIZE_HELPERS 	= $(SRCS:%.$(EXT)=%.optim)
OBJDEBOUT			= $(@:%.debug=%.o)
OBJOPTOUT			= $(@:%.optim=%.o)
DEBOUT				= $(@:%.debug=%.$(EXT))
OPTOUT				= $(@:%.optim=%.$(EXT))

# rules for debug build and optimized build
%.debug: %.$(EXT)
	$(CC) $(CFLAGS) -ggdb -D_DEBUG -DDEBUG -o $(OBJDEBOUT) $(DEBOUT)
	rm -f $(@.debug=%.debug)
	touch -f $@

%.optim: %.$(EXT)
	$(CC) $(CFLAGS) -O2 -DNDEBUG -o $(OBJOPTOUT) $(OPTOUT)
	rm -f $(@.optim=%.optim)
	touch -f $@

# rules for object files
%.o: %.$(EXT)
	$(CC) $(CFLAGS) $?

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

# clean rule
clean:
	rm -f $(OBJS) $(DEBUG_HELPERS) $(OPTIMIZE_HELPERS)

