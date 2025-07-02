include config.mk

SRC = libhpd.c
OBJ = ${SRC:.c=.o}
SO = ${SRC:.c=.so}
all: libhpd

.c.o:
	${CC} -c -fPIC ${CFLAGS} $<

${OBJ}: config.mk

config.h:
	cp config.def.h $@

libhpd: ${OBJ}
	${CC} -shared -o ${SO} ${OBJ} ${LDFLAGS}

clean:
	rm -f libhpd.so ${OBJ} libhpd-${VERSION}.tar.gz ;

dist: clean
	mkdir -p libhpd-${VERSION}
	cp -R LICENSE Makefile README config.mk\
		libhpd.1 ${SRC} libhpd-${VERSION}
	tar -cf libhpd-${VERSION}.tar libhpd-${VERSION}
	gzip libhpd-${VERSION}.tar
	rm -rf libhpd-${VERSION}

install: all
	mkdir -p ${DESTDIR}${PREFIX}/bin
	cp -f libhpd ${DESTDIR}${PREFIX}/bin
	chmod 755 ${DESTDIR}${PREFIX}/bin/libhpd
	mkdir -p ${DESTDIR}${MANPREFIX}/man1
	sed "s/VERSION/${VERSION}/g" < libhpd.1 > ${DESTDIR}${MANPREFIX}/man1/libhpd.1
	chmod 644 ${DESTDIR}${MANPREFIX}/man1/libhpd.1

uninstall:
	rm -f ${DESTDIR}${PREFIX}/bin/libhpd\
		${DESTDIR}${MANPREFIX}/man1/libhpd.1

.PHONY: all clean dist install uninstall
