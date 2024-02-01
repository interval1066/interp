AC_PREREQ([2.71])
AC_INIT([interp],[1.0],[interval1066@gmail.com])
AM_INIT_AUTOMAKE([subdir-objects])
AC_CONFIG_FILES([Makefile])
AC_OUTPUT
AC_CONFIG_SRCDIR([src/main.c])
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CXX
AC_PROG_CC
AC_LANG(C)
AC_LANG_PUSH([C])
AC_COMPILE_IFELSE([AC_LANG_PROGRAM([],[])],[],[AC_MSG_ERROR([No C compiler found])])
AC_LANG_POP([C])

AC_SEARCH_LIBS([config_init], [config], [], [
	AC_MSG_ERROR([required library libconfig not found])
])

# Checks for typedefs, structures, and compiler characteristics.
AC_CHECK_HEADER_STDBOOL
AC_C_INLINE

# Checks for library functions.

AC_OUTPUT
