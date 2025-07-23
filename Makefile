include config.mk

SRC = libhpd.c
OBJ = ${SRC:.c=.o}
SO = ${SRC:.c=.so}
h = ${SRC:.c=.h}
all: libhpd

.c.o:
	${CC} -c -fPIC ${CFLAGS} $<

${OBJ}: config.mk

config.h:
	cp config.def.h $@

libhpd: ${OBJ}
	${CC} -shared -Wl,-soname,libhpd.so.${MVERSION} -o ${SO} ${OBJ} ${LDFLAGS}

clean:
	rm -f libhpd.so ${OBJ} libhpd-${VERSION}.tar.gz ;
test: ${OBJ}
	${CC} -o $@ ${OBJ} -pedantic -Wall -Wno-deprecated-declarations -O0 -g ${LDFLAGS}
	
dist: clean
	mkdir -p libhpd-${VERSION}
	cp -R LICENSE Makefile README.md config.mk\
		 ${SRC} ${h} libhpd-${VERSION}
	tar -cf libhpd-${VERSION}.tar libhpd-${VERSION}
	gzip libhpd-${VERSION}.tar
	rm -rf libhpd-${VERSION}

install: all
	mkdir -p ${DESTDIR}${PREFIX}/lib
	cp -f libhpd.so ${DESTDIR}${PREFIX}/lib/libhpd.so.${VERSION}
	link ${DESTDIR}${PREFIX}/lib/libhpd.so.${VERSION} ${DESTDIR}${PREFIX}/lib/libhpd.so
	link ${DESTDIR}${PREFIX}/lib/libhpd.so.${VERSION} ${DESTDIR}${PREFIX}/lib/libhpd.so.${MVERSION}

uninstall:
	rm -f ${DESTDIR}${PREFIX}/lib/libhpd.so.${VERSION}

.PHONY: all clean dist install uninstall
