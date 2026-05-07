#include "../include/indice.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int busquedaBinIdx(int expediente, char *dni, FILE *f){
    long numeroRegistros, posicion;
    tIndice indice;

    if((fseek(f, 0, SEEK_END))!=0){
		fprintf(stderr, "Error: No se ha podido llevar el puntero a la posicion el fichero hash\n");
		return -2;
	}

    numeroRegistros=ftell(f)/sizeof(tIndice);

    int inicio=0, fin=numeroRegistros-1, medio;

    while(inicio<=fin){
        medio=(inicio+fin)/2;
        if((fseek(f, medio*sizeof(tIndice), SEEK_END))!=0){
            fprintf(stderr, "Error: No se ha podido llevar el puntero a la posicion el fichero hash\n");
            return -6;
        }
        
        fread(&indice, sizeof(tIndice), 1, f);

        if(indice.expediente==expediente){
            strcpy(dni, indice.dni);
            return 0;
        } else if(expediente < indice.expediente){
            fin=medio-1;
        } else{
            inicio=medio+1;
        }
    }

    return -1;
}

int busquedaIdx(int expediente, char *ficheroHash, char *ficheroIndice, tAlumno *reg){
    FILE *ficheroEntradaIndice, *fHash;
    char dni[9];
    tPosicion pos;
    int resultado;

    if ((ficheroEntradaIndice=fopen(ficheroIndice, "rb"))==NULL){
        return -6;
    }
    
    resultado = busquedaBinIdx(expediente, dni, ficheroEntradaIndice);
    fclose(ficheroEntradaIndice);

    if (resultado!=0){
        return resultado;
    }

    if ((fHash = fopen(ficheroHash, "rb"))==NULL){
        return -2;
    }

    strcpy(reg->dni, dni);
    resultado = busquedaHash(fHash, reg, &pos);
    
    fclose(fHash);

    return resultado;
}
