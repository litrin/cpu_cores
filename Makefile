CC=cc
AR=ar
CFLAGS=

ALL:
	$(CC) -c coreset.c -o coreset.o -o libcoreset.o
	$(AR) rcs libcoreset.a libcoreset.o

	$(CC) cores.c libcoreset.a $(CFLAGS) -o coreset

install:
	cp coreset /usr/local/bin/coreset

clean:
	rm -f lib*
	rm -rf coreset

	
