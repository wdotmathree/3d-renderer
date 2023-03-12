CC=gcc
CFLAGS=-Wall -Wextra -Wno-comment -lm -lSDL2 -L/usr/lib/x86_64-linux-gnu -I/usr/include/SDL2 -g
FILES=main.o mat.o transform.o triangle.o vec.o

debug: $(FILES)
	$(CC) $(FILES) $(CFLAGS)

release: $(FILES)
	$(CC) $(FILES) $(CFLAGS) -O3
	strip -s a.out

clean:
	rm -f *.o
