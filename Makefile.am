AUTOMAKE_OPTIONS = foreign
CFLAGS = -Wall -std=c11 -Wno-unused-result -Wno-unused-function -Wno-incompatible-pointer-types \
	-Wno-discarded-qualifiers -Wno-int-conversion -Wno-parentheses
LDFLAGS +=-s

# this lists the binaries to produce, the (non-PHONY, binary) targets in
# the previous manual Makefile
sbin_PROGRAMS = interp help
interp_SOURCES =	src/main.c \
					src/intrinsic.c \
					src/foo1.c \
					src/utils/filesys.c \
					src/utils/huff.c \
					src/utils/config.c

AM_CPPFLAGS = -Wall -std=c11 -O2 -g0 -I$(top_srcdir)/include 
                       
man_MANS = 

EXTRA_DIST = 	include/foo1.h \
	          	include/intrinsic.h \
	         	include/simple_strlib.h \
	         	include/support.h \
					include/utils/filesys.h \
					include/utils/getopt.h \
					include/utils/huff.h \
					include/utils/config.h

help$(EXEEXT):
	@echo "Installing interp help file"
	cp ./extra/interp.hlp ~/.interp.hlp
