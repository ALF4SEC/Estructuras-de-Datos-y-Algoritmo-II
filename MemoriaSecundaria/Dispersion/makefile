CC = gcc
CFLAGS = -Wall -g

pruebaDispersion: pruebaDispersion.o dispersion.o
	$(CC) $(CFLAGS) pruebaDispersion.o dispersion.o -o pruebaDispersion

pruebaDispersion.o: pruebaDispersion.c dispersion.h
	$(CC) $(CFLAGS) -c pruebaDispersion.c

dispersion.o: dispersion.c dispersion.h
	$(CC) $(CFLAGS) -c dispersion.c

clean:
	rm -f *.o programa