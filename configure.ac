# -*- Autoconf -*-

AC_INIT([hid-io], [0.0.1], [hidio@gergo.csillger.hu])
AM_INIT_AUTOMAKE([foreign subdir-objects dist-xz no-dist-gzip])

m4_ifdef([AM_SILENT_RULES], [AM_SILENT_RULES([yes])])

AC_CONFIG_SRCDIR([lib/hid-io/packet.c])
AC_CONFIG_HEADERS([lib/hid-io/platform.h])
AC_CONFIG_MACRO_DIR([m4])

# Before making a release, the HIDIO_LT_VERSION string should be modified.
# The string is of the form C:R:A.
# a) If binary compatibility has been broken (eg removed or changed interfaces)
#    change to C+1:0:0. DO NOT DO THIS! Use symbol versioning instead and
#    do b) instead.
# b) If interfaces have been changed or added, but binary compatibility has
#    been preserved, change to C+1:0:A+1
# c) If the interface is the same as the previous version, change to C:R+1:A
HIDIO_LT_VERSION=0:0:0
AC_SUBST(HIDIO_LT_VERSION)

AC_SUBST(MAJOR_VERSION, `echo $PACKAGE_VERSION | sed 's/\(.*\)\..*\..*/\1/g'`)
AC_SUBST(MINOR_VERSION, `echo $PACKAGE_VERSION | sed 's/.*\.\(.*\)\..*/\1/g'`)
AC_SUBST(PATCH_VERSION, [[`echo $PACKAGE_VERSION | sed 's/.*\..*\.\([0-9]*\).*/\1/g'`]])
AC_SUBST(NUMBER_VERSION, `printf "0x%02x%02x%02x" $MAJOR_VERSION $MINOR_VERSION $PATCH_VERSION`)

AC_PROG_CC
AC_PROG_CC_C_O
AC_PROG_CXX

LT_INIT([shared])

AC_CHECK_HEADERS([stdlib.h])
AC_CHECK_FUNCS([memset])
AC_FUNC_MALLOC
AC_FUNC_REALLOC
AC_CHECK_SIZEOF([void *])

AC_TYPE_SIZE_T
AC_TYPE_UINT32_T
AC_TYPE_UINT16_T
AC_TYPE_UINT8_T

# Check for pkg-config-enabled libraries
PKG_PROG_PKG_CONFIG

HAVE_CHECK=yes
PKG_CHECK_MODULES(CHECK, check,,[HAVE_CHECK="no"])

AM_CONDITIONAL([HAVE_CHECK], [test x$HAVE_CHECK != xno])

AC_CONFIG_FILES([
        Makefile
        lib/hid-io/hid-io.h
])
AC_OUTPUT
