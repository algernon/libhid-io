# -- Global settings --
AM_MAKEFLAGS                 = --no-print-directory
AM_CFLAGS                    = -I${top_srcdir}/lib -I${top_builddir}/lib
ACLOCAL_AMFLAGS              = -Im4

LDADD                        = lib/libhid-io.la

pkgincludedir                = ${includedir}/riemann

VERSION                      = @VERSION@${SNAPSHOT_VERSION}

# -- Libraries --
lib_LTLIBRARIES			          = lib/libhid-io.la

lib_libhid_io_la_CFLAGS       = ${AM_CFLAGS}
lib_libhid_io_la_LDFLAGS      = -version-info ${HIDIO_LT_VERSION}

pkginclude_HEADERS		        = \
  lib/hid-io/command.h          \
  lib/hid-io/guards.h           \
  lib/hid-io/io.h               \
  lib/hid-io/packet.h           \
  lib/hid-io/hid-io.h
lib_libhid_io_la_SOURCES      = \
  lib/hid-io/command.c          \
  lib/hid-io/packet.c

# -- Testcases --
if HAVE_CHECK
UNIT_TESTS                    = tests/check_libhid-io
TESTS                         = ${UNIT_TESTS}

AM_TESTS_ENVIRONMENT          = CK_FORK=no; export CK_FORK;
TESTS_ENVIRONMENT            ?= ${AM_TESTS_ENVIRONMENT}

tests/check_%: CFLAGS  += ${CHECK_CFLAGS}
tests/check_%: LDADD   += ${CHECK_LIBS} -ldl
tests/check_%: LDFLAGS += -no-install

check_PROGRAMS			= ${TESTS}
endif

check_libhid_io_srcs		= \
  tests/check_command.c   \
  tests/check_io.c        \
  tests/check_packet.c    \
  tests/tests.c           \
  tests/check_libhid-io.c

# -- Extra files to distribute --
EXTRA_DIST                    = \
  COPYING                       \
  README.md                     \
  ${check_libhid_io_srcs}
