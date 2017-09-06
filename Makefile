# -- Global settings --
all: lib/libhid-io.a
check: tests/check_libhid-io
	tests/check_libhid-io

CFLAGS = -Ilib -ggdb3 -O0

HEADERS		                    = \
	lib/hid-io/command.h          \
	lib/hid-io/guards.h           \
	lib/hid-io/io.h               \
	lib/hid-io/packet.h           \
	lib/hid-io/hid-io.h

SOURCES                       = \
	lib/hid-io/command.c          \
	lib/hid-io/packet.c

OBJECTS = ${SOURCES:.c=.o}

${OBJECTS}: ${SOURCES} ${HEADERS}
${SOURCES}: ${HEADERS}

lib/libhid-io.a:
lib/libhid-io.a: ${OBJECTS}
	${AR} cru $@ $^

tests/check_libhid-io: tests/check_libhid-io.c lib/libhid-io.a
	${CC} ${CFLAGS} $(shell pkg-config --cflags check) -o $@ $^ $(shell pkg-config --libs check)

clean:
	rm -f ${OBJECTS} lib/libhid-io.a tests/check_libhid-io

.PHONY: all check clean
