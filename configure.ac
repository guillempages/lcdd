#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ(2.59)
AC_INIT([Guillem lcd daemon], 0.4.1, guillempages@hotmail.com,lcdd)
AM_INIT_AUTOMAKE#(lcd, 0.4.1)

AM_CONFIG_HEADER(include/defines.h)
AC_LANG_C
AC_LANG_CPLUSPLUS
AM_PROG_LIBTOOL

AC_CONFIG_SRCDIR([src/])
#AC_CONFIG_HEADERS([include/defines.h])

AC_ARG_ENABLE([debug],[AS_HELP_STRING([--enable-debug],[Enable verbose output])],[],[enable_debug=no])

# Checks for programs.
AC_PROG_CXX
AC_PROG_LIBTOOL

# Checks for libraries.

# Checks for header files.
AC_HEADER_STDC
AC_HEADER_SYS_WAIT
AC_CHECK_HEADERS([arpa/inet.h fcntl.h netdb.h netinet/in.h sys/ioctl.h sys/socket.h sys/time.h unistd.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_HEADER_STDBOOL
AC_C_CONST
AC_C_INLINE
AC_HEADER_TIME

# Checks for library functions.
AC_FUNC_FORK
#AC_PROG_GCC_TRADITIONAL
AC_FUNC_SELECT_ARGTYPES
AC_TYPE_SIGNAL
AC_FUNC_STAT
AC_FUNC_WAIT3
AC_CHECK_FUNCS([atexit gethostbyname select socket])

AC_CONFIG_FILES([Makefile src/Makefile include/Makefile])
AC_OUTPUT

