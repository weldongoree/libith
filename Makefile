CC=gcc
LIBS=-lm -lith
PICFLAGS=-fPIC
LIBOBJS=pmf.o bits.o load.o chisquare.o entropy.o
DEPS=pmf.h ith.h bits.h load.h chisquare.h
CFLAGS=-g -Wall
LOCALLINK=-L.
SHAREDFLAGS=-shared
LIBNAME=libith.so.0.0
BINNAME=ith

shared: $(LIBOBJS)
	$(CC) $(SHAREDFLAGS) $(CFLAGS) -o $(LIBNAME) $(LIBOBJS)

$(BINNAME): ith.c $(DEPS) shared
	$(CC) $(CFLAGS) $(LOCALLINK) $(LIBS) -o ith ith.c

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS) $(PICFLAGS)

clean:
	rm -f $(LIBOBJS) $(BINTGT) $(LIBNAME) $(BINNAME)
