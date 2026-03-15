CC = gcc
CFLAGS = -Wall -g

pruebaSecuencial: pruebaSecuencial.o secuencial.o
	$(CC) $(CFLAGS) pruebaSecuencial.o secuencial.o -o pruebaSecuencial

pruebaSecuencial.o: pruebaSecuencial.c secuencial.h
	$(CC) $(CFLAGS) -c pruebaSecuencial.c

secuencial.o: secuencial.c secuencial.h
	$(CC) $(CFLAGS) -c secuencial.c

clean:
	rm -f *.o programa