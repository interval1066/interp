AUTOMAKE_OPTIONS = foreign
CFLAGS = -Wall -std=c11 -Wno-unused-result -Wno-unused-function -I../include
LDFLAGS =

# this lists the binaries to produce, the (non-PHONY, binary) targets in
# the previous manual Makefile
sbin_PROGRAMS = interp
interp_SOURCES =	src/main.c \
						src/intrinsic.c \
						src/foo1.c \
						src/threadpool.c \
						src/utils/filesys.c \
						src/utils/huff.c


AM_CPPFLAGS = -Wall -std=c11 -Wno-unused-result -Wno-unused-function \
                        -I$(top_srcdir)/include
man_MANS = 
EXTRA_DIST = include/foo1.h \
	                    include/intrinsic.h \
	                    include/simple_strlib.h \
	                    include/support.h \
	                    include/threadpool.h \
	                    include/utils/filesys.h \
	                    include/utils/huff.h \
	                    include/utils/getopt.h \
	                    include/utils/xgetopt.h

