#include <stdio.h>
#include <string.h>
#include "../include/alumno.h"
#include "../include/dispersion.h"

<<<<<<< HEAD
int funcionHash(tAlumno *reg, int nCubos){
    return atoi(reg->dni)%nCubos;
=======
int funcionHash(tAlumno *reg, int nCubos) {
    return atoi(reg->dni) % nCubos;
>>>>>>> 26917ba03998ba32cb53411e8e8a03009aeb91ae
}

void mostrarReg(tAlumno *reg) {
    fprintf(stdout, "DNI: %s\n", reg->dni);
    fprintf(stdout, "Num. Expediente: %d\n", reg->expediente);
    fprintf(stdout, "Nombre: %s\n", reg->nombre);
    fprintf(stdout, "Primer Apellido: %s\n", reg->ape1);
    fprintf(stdout, "Segundo Apellido: %s\n", reg->ape2);
    fprintf(stdout, "Provincia: %s\n", reg->provincia);
}

int cmpClave(tAlumno *reg1, tAlumno *reg2) {
    return (!strcmp(reg1->dni, reg2->dni));
}

int buscar(char *fichero, char *dni) {
    FILE *ficheroEntrada;
    tPosicion pos;
    tipoReg reg;
    int resultado;

    if ((ficheroEntrada = fopen(fichero, "rb")) == NULL) {
        return -2;
    }

    strcpy(reg.dni, dni);
<<<<<<< HEAD

    if(resultado=(busquedaHash(ficheroEntrada, &reg, &pos))==0){
=======
    
    if ((resultado = busquedaHash(ficheroEntrada, &reg, &pos)) == 0) {
>>>>>>> 26917ba03998ba32cb53411e8e8a03009aeb91ae
        mostrarReg(&reg);
    }

    fclose(ficheroEntrada);
    return resultado;
}

int modificar(char *fichero, char *dni, char *provincia) {
    FILE *ficheroEntrada;
    tPosicion pos;
    tipoReg reg;
    int resultado;

    if ((ficheroEntrada = fopen(fichero, "rb+")) == NULL) {
        return -2;
    }

    strcpy(reg.dni, dni);
<<<<<<< HEAD
    strcpy(reg.provincia, provincia);
=======
>>>>>>> 26917ba03998ba32cb53411e8e8a03009aeb91ae

    if ((resultado = busquedaHash(ficheroEntrada, &reg, &pos)) == 0) {
        strcpy(reg.provincia, provincia);
        resultado = modificarReg(ficheroEntrada, &reg, &pos);
    }

    fclose(ficheroEntrada);
    return resultado;
}

void pedirDatos(tAlumno *reg) {
    fprintf(stdout, "Introduzca el DNI del alumno: ");
    scanf("%8s", reg->dni);

    fprintf(stdout, "Introduzca el numero de expediente del alumno: ");
    scanf("%d", &reg->expediente);

    fprintf(stdout, "Introduzca el nombre del alumno: ");
    scanf("%18s", reg->nombre); 

    fprintf(stdout, "Introduzca el primer apellido del alumno: ");
    scanf("%18s", reg->ape1);

    fprintf(stdout, "Introduzca el segundo apellido del alumno: ");
    scanf("%18s", reg->ape2);

    fprintf(stdout, "Introduzca la provincia del alumno: ");
    scanf("%10s", reg->provincia);
}