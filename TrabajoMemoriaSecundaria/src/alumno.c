#include <stdio.h>
#include <string.h>
#include <alumno.h>
#include <dispersion.h>

int funcionHash(tAlumno *reg, int nCubos){
    return atoi(reg->dni%nCubos);
}

void mostrarReg(tAlumno *reg){
    fprintf(stdout, "DNI: %s\n", reg->dni);
    fprintf(stdout, "Num. Expediente: %d\n", reg->expediente);
    fprintf(stdout, "Nombre: %s\n", reg->nombre);
    fprintf(stdout, "Primer Apellido: %s\n", reg->ape1);
    fprintf(stdout, "Segundo Apellido: %s\n", reg->ape2);
    fprintf(stdout, "Provincia: %s\n", reg->provincia);
}

int cmpClave(tAlumno *reg1, tAlumno *reg2){
    return (!strcmp(reg1->dni, reg2->dni)); 
}

int buscar(char *fichero, char *dni){
    FILE *ficheroEntrada;
    tPosicion pos;
    tipoReg reg;
    int resultado;

    if((ficheroEntrada=fopen(fichero, "rb"))==NULL){
        fprintf(stderr, "Error: No se ha podido abrir de manera correcta el del fichero %s\n", fichero);
        return -1;
    }

    strcpy(reg->dni, dni);

    if(resultado=(busquedaHash(fichEntrada, &reg, &pos))==0){
        mostrarReg(&reg);
    }

    fclose(fichEntrada);
    return resultado;
}

int modificar(char *fichero, char *dni, char *provincia){
    FILE *ficheroEntrada;
    tPosicion pos;
    tipoReg reg;
    int resultado;

    if((ficheroEntrada=fopen(fichero, "rb+"))==NULL){
        fprintf(stderr, "Error: No se ha podido abrir de manera correcta el del fichero %s\n", fichero);
        return -1;
    }

    strcpy(reg->dni, dni);
    strcpy(reg->provincia, provincia);

    if(resultado=(modificarReg(fichEntrada, &reg, &pos))==0){
        mostrarReg(&reg);
    }

    fclose(fichEntrada);
    return resultado;
}

void pedirDatos(tAlumno *reg){
    //Lectura del DNI
    fprintf(stdout, "Introduzca el DNI del alumno: ");
    scanf("%8s", reg->dni);
    puts("");

    //Lectura del numero de expediente
    fprintf(stdout, "Introduzca el numero de experdiente del alumno: ");
    scanf("%d", &reg->expediente);
    puts("");

    //Lectura del nombre
    fprintf(stdout, "Introduzca el nombre del alumno: ");
    scanf("%19s", reg->nombre);
    puts("");

    //Lectura del apellido1
    fprintf(stdout, "Introduzca el primer apellido del alumno: ");
    scanf("%18s", reg->ape1);
    puts("");

    //Lectura del apellido2
    fprintf(stdout, "Introduzca el segundo apellido del alumno: ");
    scanf("%18s", reg->ape2);
    puts("");

    //Lectura de la provincia
    fprintf(stdout, "Introduzca la provincia del alumno: ");
    scanf("%10s", reg->provincia);
    puts("");

}
