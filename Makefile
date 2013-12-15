CC=gcc
LIBS=-lm -lith
PICFLAGS=-fPIC
LIBOBJS=pmf.o bits.o load.o chisquare.o entropy.o kldiv.o
DEPS=pmf.h ith.h bits.h load.h chisquare.h kldiv.h
CFLAGS=-g -Wall
LOCALLINK=-L.
SHAREDFLAGS=-shared
LIBNAME=libith.so.0.0
BINNAME=ith
PREFIX=/usr/local
LIBDIR=lib
BINDIR=bin
INCLUDEDIR=include
MANDIR=man
MANSUBDIR=man1
LIBMAJORNAME=libith.so.0
LIBBASENAME=libith.so
LOCALHEADERDIR=include
INCLUDEFILE=ith.h
MANPAGE=ith.1

all: $(BINNAME) 

shared: $(LIBOBJS)
	$(CC) $(SHAREDFLAGS) $(CFLAGS) -o $(LIBNAME) $(LIBOBJS)
	rm -f $(LIBBASENAME)
	ln -s $(LIBNAME) $(LIBBASENAME)
$(BINNAME): ith.c $(DEPS) shared
	$(CC) $(CFLAGS) $(LOCALLINK) $(LIBS) -o ith ith.c
	rm -f $(LIBBASENAME)
%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS) $(PICFLAGS)

clean:
	rm -f $(LIBOBJS) $(BINTGT) $(LIBNAME) $(BINNAME)

install:
	install -m 755 $(BINNAME) $(DESTDIR)/$(PREFIX)/$(BINDIR)
	install -m 755 $(LIBNAME) $(DESTDIR)/$(PREFIX)/$(LIBDIR)
	ln -s $(LIBNAME) $(DESTDIR)/$(PREFIX)/$(LIBDIR)/$(LIBMAJORNAME)
	ln -s $(LIBNAME) $(DESTDIR)/$(PREFIX)/$(LIBDIR)/$(LIBBASENAME)

header-install:
	install -m 644 $(LOCALHEADERDIR)/$(INCLUDEFILE) $(DESTDIR)/$(PREFIX)/$(INCLUDEDIR)

man-install:
	install -m 644 $(MANPAGE) $(DESTDIR)/$(PREFIX)/$(MANDIR)
	gzip -9 $(DESTDIR)/$(PREFIX)/$(MANDIR)/$(MANPAGE)
