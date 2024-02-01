#!/bin/sh
# Clean autotools config, run in top directory
#
rm -rf autom4te.cache # 2>&1 /dev/null
rm aclocal.m4 compile config.h config.h.in config.log\
	config.status configure depcomp install-sh Makefile.in\
	missing stamp-h1 Makefile
