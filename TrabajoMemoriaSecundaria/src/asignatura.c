#include <stdio.h>
#include <string.h>
#include "../include/asignatura.h"
#include "../include/dispersion.h"

int funcionHash(tAsignatura *reg, int nCubos) {
    return reg->codigo % nCubos;
}

void mostrarReg(tAsignatura *reg) {
    fprintf(stdout, "Codigo de Asig.: %d\n", reg->codigo);
    fprintf(stdout, "Nombre de Asig.: %s\n", reg->nombre);
    fprintf(stdout, "Curso: %c\n", reg->curso);
    fprintf(stdout, "Creditos de Teoria: %f\n", reg->creditosT);
    fprintf(stdout, "Creditos de Practicas: %f\n", reg->creditosP);
    fprintf(stdout, "Tipo de Asig.: %c\n", reg->tipo);
    fprintf(stdout, "Cuatrimestre: %c\n", reg->cuatrimestre);
    fprintf(stdout, "Num. grupos de Teoria: %d\n", reg->numGrT);
    fprintf(stdout, "Num. grupos de Practicas: %d\n", reg->numGrP);
}

int cmpClave(tAsignatura *reg1, tAsignatura *reg2) {
    return (reg1->codigo == reg2->codigo);
}

int buscar(char *fichero, int codigo) {
    FILE *ficheroEntrada;
    tipoReg reg;
    tPosicion pos;
    int resultado;

    if ((ficheroEntrada = fopen(fichero, "rb")) == NULL) {
        return -2;
    }

    reg.codigo = codigo;

    if ((resultado = busquedaHash(ficheroEntrada, &reg, &pos)) == 0) {
        mostrarReg(&reg);
    }

    fclose(ficheroEntrada);
    return resultado;
}

int modificar(char *fichero, int codigo, float creditosT, float creditosP) {
    FILE *ficheroEntrada;
    tPosicion pos;
    tipoReg reg;
    int resultado;

    if ((ficheroEntrada = fopen(fichero, "rb+")) == NULL) {
        return -2;
    }

    reg.codigo = codigo;

    if ((resultado = busquedaHash(ficheroEntrada, &reg, &pos)) == 0) {
        reg.creditosT = creditosT;
        reg.creditosP = creditosP;
        resultado = modificarReg(ficheroEntrada, &reg, &pos);
    }

    fclose(ficheroEntrada);
    return resultado;
}

void pedirDatos(tAsignatura *reg) {
    fprintf(stdout, "Introduzca el codigo de la asig.: ");
    scanf("%d", &reg->codigo);

    fprintf(stdout, "Introduzca el nombre de la asig.: ");
    scanf("%59s", reg->nombre);

    fprintf(stdout, "Introduzca el curso de la asig.: ");
    scanf(" %c", &reg->curso);

    fprintf(stdout, "Introduzca los creditos de teoria: ");
    scanf("%f", &reg->creditosT);

    fprintf(stdout, "Introduzca los creditos de practicas: ");
    scanf("%f", &reg->creditosP);

    fprintf(stdout, "Introduzca el tipo de la asig.: ");
    scanf(" %c", &reg->tipo);

    fprintf(stdout, "Introduzca el cuatrimestre de la asig.: ");
    scanf(" %c", &reg->cuatrimestre);

    fprintf(stdout, "Introduzca el grupo de teoria: ");
    scanf("%d", &reg->numGrT);

    fprintf(stdout, "Introduzca el grupo de practicas: ");
    scanf("%d", &reg->numGrP);
}