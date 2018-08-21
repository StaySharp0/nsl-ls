#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([project_SN], [1.0], [StaySharp0@gmail.com])
AC_CONFIG_SRCDIR([config.h.in])
AC_CONFIG_HEADERS([config.h])
# AC_CONFIG_MACRO_DIR([m4])

# Checks for programs.
AC_PROG_CXX
AC_PROG_AWK
AC_PROG_CC
AC_PROG_CPP
AC_PROG_INSTALL
AC_PROG_LN_S
AC_PROG_MAKE_SET
AC_PROG_RANLIB

AM_INIT_AUTOMAKE( [foreign -Wall] )
m4_ifdef([AM_PROG_AR], [AM_PROG_AR])
LT_INIT

# Checks for libraries.
# FIXME: Replace `main' with a function in `-lGateway':
AC_CHECK_LIB([Gateway], [cmd_arg_gateway], [init_gateway])

# Checks for header files.
AC_CHECK_HEADERS([arpa/inet.h netinet/in.h stdlib.h string.h sys/socket.h unistd.h])

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.
AC_FUNC_FORK
AC_FUNC_MALLOC
AC_CHECK_FUNCS([bzero inet_ntoa select socket strerror])

AC_CONFIG_FILES([Makefile
                 lib/Makefile
                 lib/gateway/Makefile
                 src/Makefile])
AC_CONFIG_SUBDIRS([lib/json-c])
AC_OUTPUT
