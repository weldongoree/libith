CC=gcc
LIBS=-lm
BINOBJS=entropy.o alphabet.o
BINTGT=entropy
DEPS=alphabet.h entropy.h
CFLAGS=-g -Wall

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(BINTGT): $(BINOBJS)
	$(CC) $(CFLAGS) ${LIBS} -o entropy $(BINOBJS)


clean:
	rm $(BINOBJS) $(BINTGT)
