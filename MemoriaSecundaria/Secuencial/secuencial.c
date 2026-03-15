#include <stdio.h>
#include <string.h>
#include "secuencial.h"

int leeSecuencial(char *fichero){
    FILE *f;
    tipoAlumno alumno;
    int i=0;

    if((f=fopen(fichero, "rb"))==NULL){
        fprintf(stderr, "Error: No se pudo abrir el archivo %s \n", fichero);
        return -1;
    }

    if((fseek(f, 0, SEEK_SET))!=0){
        fprintf(stderr, "Error: No se pudo a llevar el puntero al inicio del archivo \n");
        return -2;
    }

    fread(&alumno, sizeof(tipoAlumno), 1,f);
    
    while(feof(f)==0){
        printf("%d %s %s %s %s %s \n", i, alumno.dni, alumno.ape1, alumno.ape2, alumno.nombre, alumno.provincia);

        fread(&alumno, sizeof(tipoAlumno), 1,f);
            
        i++;
    }

    int tamanoFichero=ftell(f);
    int numeroRegistros=tamanoFichero/sizeof(tipoAlumno);

    fclose(f);

    return numeroRegistros;

}

int buscaReg(FILE *fSecuencial, tipoAlumno *reg, char *dni){
    int i=0;

    if((fseek(fSecuencial, 0, SEEK_SET))!=0){
        fprintf(stderr, "Error: No se pudo a llevar el puntero al inicio del archivo");
        return -2;
    }

    fread(reg, sizeof(tipoAlumno), 1, fSecuencial);

    while(feof(fSecuencial)==0){
        if(!strcmp(reg->dni, dni)){
            return i;
        } 
        i++;

        fread(reg, sizeof(tipoAlumno), 1, fSecuencial);
    }
    
    return -1;
}

int insertaReg(char *fSecuencial, tipoAlumno *reg){
    FILE *f;

    if((f=fopen(fSecuencial, "r+b"))==NULL){
        fprintf(stderr, "Error: No se pudo abrir el archivo %s \n", fSecuencial);
        return -1;
    }

    if((fseek(f, 0, SEEK_END))!=0){
        fprintf(stderr, "Error: No se pudo a llevar el puntero al inicio del archivo");
        return -2;
    }

    if((fwrite(reg, sizeof(tipoAlumno), 1, f))!=1){
        fprintf(stderr, "Error: Problemas en la escritura del fichero");
        return -3;
    }

    int tamanoFichero=ftell(f);
    int numeroRegistros=tamanoFichero/sizeof(tipoAlumno);
    
    return numeroRegistros;
}