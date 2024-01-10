CC=cc
CFLAGS=-s -w

ALL:
	$(CC) cores.c $(CFLAGS) -o coreset

install:
	cp coreset /usr/local/bin/coreset

clean:
	rm -f coreset
	
