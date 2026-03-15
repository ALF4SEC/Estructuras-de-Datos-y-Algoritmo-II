#include <stdio.h>
#include <string.h>
#ifndef __INDICE_H
#define __INDICE_H
#include "alumno.h"

typedef struct {
	int expediente;
	char dni[9];
	int desborde; // valor 0 por defecto
}tIndice;

int busquedaBinIdx(int expediente, char *dni, FILE *f);
int busquedaIdx(int expediente, char *ficheroHash, char *ficheroIndice, tAlumno *reg);

#endif
