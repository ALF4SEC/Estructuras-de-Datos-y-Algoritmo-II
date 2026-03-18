#include <stdio.h>
#include <string.h>
#include <../include/asignatura.h>
#include <../include/dispersion.h>

int funcionHash(tAsignatura *reg, int nCubos){
    return (atoi(reg->codigo)%nCubo)
}

void mostrarReg(tAsignatura *reg){
    fprintf(stdout, "Codigo de Asig.: %d\n", reg->codigo);
    fprintf(stdout, "Nombre de Asig.: %s\n", reg->nombre);
    fprintf(stdout, "Curso: %c\n", reg->curso);
    fprintf(stdout, "Creditos de Teoria: %f\n", reg->creditosT);
    fprintf(stdout, "Creditos de Practicas: %f\n", reg->creditosP);
    fprintf(stdout, "Tipo de Asig.: %c\n", reg->tipo);
    fprintf(stdout, "Cuatrimestre: %c\n", reg->cuatrimestre);
    fprintf(stdout, "Num. creditos de Teoria: %d\n", reg->numGrT);
    fprintf(stdout, "Num. creditos de Practicas: %d\n", reg->numGrP);
}

int cmpClave(tAsignatura *reg1, tAsignatura *reg2){
    return(!(strcmp(reg1->codigo, reg2->codigo)))
}

int buscar(char *fichero, int codigo){
    FILE *fichEntrada;
    tipoReg reg;
    tPosicion pos;

    if((ficheroEntrada=fopen(fichero, "rb"))==NULL){
        fprintf(stderr, "Error: No se ha podido abrir de manera correcta el del fichero %s\n", fichero);
        return -1;
    }

    reg->codigo=codigo;

    if(resultado=(busquedaHash(ficheroEntrada, &reg, &pos))==0){
        mostrarReg(&reg);
    }

    fclose(ficheroEntrada);
    return resultado;
}

int modificar(char *fichero, int codigo, float creditosT, float creditosP){
    FILE *ficheroEntrada;
    tPosicion pos;
    tipoReg reg;
    int resultado;

    if((ficheroEntrada=fopen(fichero, "rb+"))==NULL){
        fprintf(stderr, "Error: No se ha podido abrir de manera correcta el del fichero %s\n", fichero);
        return -1;
    }

    reg->codigo=codigo;
    reg->creditosT=creditosT;
    reg->creditosP=creditosP;

    if(resultado=(modificarReg(ficheroEntrada, &reg, &pos))==0){
        mostrarReg(&reg);
    }

    fclose(ficheroEntrada);
    return resultado;
}

void pedirDatos(tAsignatura *reg){
    //Lectura del codigo
    fprintf(stdout, "Introduzca el codigo de la asig.: ");
    scanf("%d", &reg->codigo);
    puts("");

    //Lectura del nombre
    fprintf(stdout, "Introduzca el nombre de la asig.: ");
    scanf("%59s", reg->nombre);
    puts("");

    //Lectura del curso
    fprintf(stdout, "Introduzca el curso de la asig.: ");
    scanf("%c", %reg->curso);
    puts("");

    //Lectura del creditosT
    fprintf(stdout, "Introduzca los creditos de la parte de teoria: ");
    scanf("%f", &reg->creditosT);
    puts("");

    //Lectura del creditosP
    fprintf(stdout, "Introduzca los creditos de la parte de practicas: ");
    scanf("%f", &reg->creditosP);
    puts("");

    //Lectura de la tipo
    fprintf(stdout, "Introduzca el tipo de la asig.: ");
    scanf("%c", reg->tipo);
    puts("");

    //Lectura de la cuatrimestre
    fprintf(stdout, "Introduzca el cuatrimestre de la asig.: ");
    scanf("%c", reg->cuatrimestre);
    puts("");

    //Lectura de la numGrT
    fprintf(stdout, "Introduzca el grupo de teoria: ");
    scanf("%d", &reg->numGrT);
    puts("");

    //Lectura de la numGrP
    fprintf(stdout, "Introduzca el grupo de practicas: ");
    scanf("%d", &reg->numGrP);
    puts("");
}

