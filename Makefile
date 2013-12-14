CC=gcc
LIBS=-lm
BINOBJS=entropy.o pmf.o bits.o load.o
BINTGT=entropy
DEPS=pmf.h entropy.h bits.h load.h
CFLAGS=-g -Wall

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(BINTGT): $(BINOBJS)
	$(CC) $(CFLAGS) ${LIBS} -o entropy $(BINOBJS)

clean:
	rm -f $(BINOBJS) $(BINTGT)
