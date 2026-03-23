#include "../include/dispersion.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// Lee el contenido del fichero hash organizado mediante el método de DISPERSIÓN según los criterios
// especificados en la práctica. Se leen todos los cubos completos tengan registros asignados o no. La
// salida que produce esta función permite visualizar el método de DISPERSIÓN
int leeHash(char *fichHash){ 
	FILE *f;
	tipoCubo cubo;
	regConfig regC;
	int j, nCubo=0, densidadOcupacion;
	
	if ((f = fopen(fichHash,"rb"))==NULL) return -2;
	fread(&regC,sizeof(regConfig),1,f);
	fread(&cubo,sizeof(cubo),1,f); 
	while (!feof(f)){
		for (j=0;j<C;j++) {
			if (j==0){
				printf("Cubo %2d (%2d reg. ASIGNADOS)",nCubo,cubo.numRegAsignados);
			} else if ((j==1) && cubo.desbordado){
				printf("DESBORDADO\t\t");
			} else{
				printf("\t\t\t");
			}

				if (j < cubo.numRegAsignados){
				mostrarReg(&(cubo.reg[j]));
			} else{
				printf ("\n");
			}
		}
		nCubo++;
		fread(&cubo,sizeof(cubo),1,f);
	}

	fclose(f);
	
	printf("ORGANIZACIÓN MÉTODO DISPERSIÓN:\n\t %d CUBOS y %d CUBOS DESBORDE con capacidad %d\n",
			regC.nCubos,regC.nCubosDes, C);   
	
	printf("Cubo de Desborde Actual: %d\n", regC.nCuboDesAct);  

	printf("\t Contiene %d registros de los cuales se han desbordado %d:\n",regC.numReg,regC.numRegDes);
			
	densidadOcupacion = 100*regC.numReg/((regC.nCubos+regC.nCubosDes)*C);
	printf("Densidad ACTUAL de ocupación: %d \n\t(MÍNIMA permitida %f  MÁXIMA permitida %f)\n",
			densidadOcupacion,regC.densidadMin,regC.densidadMax);
	
   if (densidadOcupacion>regC.densidadMax) {
   	printf("No se respeta la densidad máxima de ocupacion\n");
   }	

   if (densidadOcupacion<regC.densidadMin) {
   	printf("No se respeta la densidad mínima de ocupacion\n");
   }	

   return 0;	
}

// Funciones a codificar
// Parte 1. Funciones gen�ricas para la creaci�n de ficheros
int creaHash(char *fichEntrada, char *fichHash, regConfig *regC){
   FILE *ficheroEntrada, *ficheroHash;
   int i;
   tipoAlumno alumno;
   tipoCubo cubo;

   if((i=creaHvacio(ficheroHash, regC))!=0){
      fprintf(stderr, "Error: No se ha podido crear de forma correcta el fichero hash vacio");
      return -2;
   }

   if((ficheroHash=fopen(fichEntrada, "rb"))==NULL){
      fprintf(stderr, "Error: No se ha podido abrir de manera correcta el del fichero %s\n", fichEntrada);
      return -1;
   }

   if((ficheroHash=fopen(fichEntrada, "rb+"))==NULL){
      fprintf(stderr, "Error: No se ha podido abrir de manera correcta el del fichero %s\n", fichEntrada);
      fclose(ficheroHash);
      return -2;
   }

   if((fseek(ficheroHash, 0, SEEK_SET))!=0){
		fprintf(stderr, "Error: No se ha podido llevar el puntero a la posicion el fichero %s\n", fichHash);
		fclose(ficheroEntrada);
		fclose(ficheroHash);
		return -1;
	}

	if((fseek(ficheroHash, 0, SEEK_SET))!=0){
		fprintf(stderr, "Error: No se ha podido llevar el puntero a la posicion el fichero %s\n", fichHash);
		fclose(ficheroEntrada);
		fclose(ficheroHash);
		return -2;
	}

   fread(&alumno, sizeof(tipoAlumno), 1, ficheroEntrada);

	while(!feof(ficheroEntrada)){


      fread(&alumno, sizeof(tipoAlumno), 1, ficheroEntrada);
   }

}

int creaHvacio(char *fichHash, regConfig *reg){
   FILE *ficheroHash;
   tipoCubo cubo;
   int j;
   int numCubos =reg->nCubos+reg->numCubosDes;

   memset(&cubo, 0, sizeof(cubo));

   if((ficheroHash=fopen(fichHash, "wb"))==NULL){
      fprintf(stderr, "Error: No se ha podido abrir de manera correcta el archivo");
      return -2;
   }

   for (j=0; j<numCubos; j++){
      if((fwrite(&cubo, sizeof(tipoCubo), 1, ficheroHash))!=1){
			fprintf(stderr, "Error: Problemas en la escritura del fichero %s\n", fichHash);
			fclose(ficheroHash);
			return -3;
		}
   }

   fclose(ficheroHash);
   return 0;
}

int insertar(FILE *fHash, tipoReg *reg, regConfig *regC){
   
}

int desborde(FILE *fHash, tipoReg *reg, regConfig *regC){

}

// Parte 2. Funciones gen�rcias para el acceso a los ficheros
int busquedaHash(FILE *fHash, tipoReg *reg, tPosicion *posicion){

}

int modificarReg(FILE *fHash, tipoReg *reg, tPosicion *posicion){

} 