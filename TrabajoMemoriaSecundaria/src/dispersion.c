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
   tipoReg registro;
   tipoCubo cubo;
   int salida;

   if(regC->nCubos<8 || regC->nCubosDes<4){
		fprintf(stderr, "Error: Los parametros de configuracion nCubos o nCubosDes no son correctos");
      	return -5;
   }

   if((creaHvacio(fichHash, regC))!=0){
      fprintf(stderr, "Error: No se ha podido crear de forma correcta el fichero hash vacio");
      return -2;
   }

   if((ficheroEntrada=fopen(fichEntrada, "rb"))==NULL){
      fprintf(stderr, "Error: No se ha podido abrir de manera correcta el del ficheroEntrada\n");
      return -1;
   }

   if((ficheroHash=fopen(fichHash, "rb+"))==NULL){
      fprintf(stderr, "Error: No se ha podido abrir de manera correcta el del fichero %s\n", fichHash);
      fclose(ficheroEntrada);
      return -2;
   }
   
	fread(&registro, sizeof(tipoReg), 1, ficheroEntrada);

	while(!feof(ficheroEntrada)){
		if((salida=insertar(ficheroHash, &registro, regC))!=0){
			fclose(ficheroEntrada);
			fclose(ficheroHash);
			return salida;
		}

      	fread(&registro, sizeof(tipoReg), 1, ficheroEntrada);
  	}

	int densidad = (regC->numReg * 100) / (regC->nCubos * C);
    if (densidad > regC->densidadMax) {
        fclose(ficheroEntrada);
        fclose(ficheroHash);
        return -3;
    }
    if (densidad < regC->densidadMin) {
        fclose(ficheroEntrada);
        fclose(ficheroHash);
        return -4;
    }

    // Escribir regConfig actualizado al principio del fichero
    if((fseek(ficheroHash, 0, SEEK_SET))!=0){
		fprintf(stderr, "Error: No se ha podido llevar el puntero a la posicion el fichero hash\n");
		fclose(ficheroEntrada);
		fclose(ficheroHash);
		return -1;
	}
	
    if((fwrite(&cubo, sizeof(regC), 1, ficheroHash))!=1){
		fprintf(stderr, "Error: Problemas en la escritura del fichero hash\n");
		fclose(ficheroEntrada);
		fclose(ficheroHash);
		return -2;
	}

    fclose(ficheroEntrada);
    fclose(ficheroHash);
    return 0;

}

int creaHvacio(char *fichHash, regConfig *reg){
   FILE *ficheroHash;
   tipoCubo cubo;
   int j;
   int nCubos =reg->nCubos+reg->nCubosDes;

   	reg->numReg = 0;
    reg->numRegDes = 0;
    reg->nCuboDesAct = reg->nCubos;

   memset(&cubo, 0, sizeof(cubo));

   if((ficheroHash=fopen(fichHash, "wb"))==NULL){
      fprintf(stderr, "Error: No se ha podido abrir de manera correcta el archivo");
      return -2;
   }

   if (fwrite(reg, sizeof(regConfig), 1, ficheroHash) !=1) {
        fclose(ficheroHash);
        return -2;
    }

   for (j=0; j<nCubos; j++){
      if((fwrite(&cubo, sizeof(tipoCubo), 1, ficheroHash))!=1){
			fprintf(stderr, "Error: Problemas en la escritura del fichero %s\n", fichHash);
			fclose(ficheroHash);
			return -2;
		}
   }

   fclose(ficheroHash);
   return 0;
}

int insertar(FILE *fHash, tipoReg *reg, regConfig *regC){
	int funcionHash;
	tipoCubo cubo;
	#ifdef ALUM
		funcionHash=atoi(reg->dni)%regC->nCubos;
	#endif

	#ifdef ASIG
		funcionHash=reg->codigo%regC->nCubos;
	#endif

	if((fseek(fHash, 0, SEEK_SET))!=0){
		fprintf(stderr, "Error: No se ha podido llevar el puntero a la posicion el ficheroHash\n");
		fclose(fHash);
		return -2;
	}

	long posCubo=sizeof(regConfig)+funcionHash*sizeof(tipoCubo);

	if((fseek(fHash, posCubo, SEEK_SET))!=0){
		fprintf(stderr, "Error: No se ha podido llevar el puntero a la posicion el ficheroHash\n");
		fclose(fHash);
		return -2;
	}

	fread(&cubo, sizeof(tipoCubo), 1, fHash);

	if (cubo.numRegAsignados == C){
        cubo.desbordado = 1;

        if((fseek(fHash, posCubo, SEEK_SET))!=0){
			fprintf(stderr, "Error: No se ha podido llevar el puntero a la posicion el ficheroHash\n");
			fclose(fHash);
			return -2;
		}

        if((fwrite(&cubo, sizeof(tipoCubo), 1, fHash))!=1){
			fprintf(stderr, "Error: Problemas en la escritura del fichero hash\n");
			fclose(fHash);
			return -2;
		}

        return desborde(fHash, reg, regC);
    } else{
        cubo.reg[cubo.numRegAsignados] = *reg;
        cubo.numRegAsignados++;

        if((fseek(fHash, posCubo, SEEK_SET))!=0){
			fprintf(stderr, "Error: No se ha podido llevar el puntero a la posicion el ficheroHash\n");
			fclose(fHash);
			return -2;
		}

       	if((fwrite(&cubo, sizeof(tipoCubo), 1, fHash))!=1){
			fprintf(stderr, "Error: Problemas en la escritura del fichero hash\n");
			fclose(fHash);
			return -2;
		}

		regC->numReg++;
    }
    
	return 0;
}

int desborde(FILE *fHash, tipoReg *reg, regConfig *regC){
	tipoCubo cubo;
	long posCubo=sizeof(regConfig)+sizeof(tipoCubo)*(regC->nCubos+regC->nCuboDesAct);

	if((fseek(fHash, 0, SEEK_SET))!=0){
		fprintf(stderr, "Error: No se ha podido llevar el puntero a la posicion el ficheroHash\n");
		fclose(fHash);
		return -2;
	}

	if((fseek(fHash, posCubo, SEEK_SET))!=0){
		fprintf(stderr, "Error: No se ha podido llevar el puntero a la posicion el ficheroHash\n");
		fclose(fHash);
		return -2;
	}

	fread(&cubo, sizeof(tipoCubo), 1, ficheroHash);

	cubo.reg[cubo.numRegAsignados++]=*reg;

	if(cubo.numRegAsignados==C){
		if(regC->nCuboDesAct==(regC->nCubos+regC->nCubosDes-1)){
			tipoCubo cuboVacio;
            memset(&cuboVacio, 0, sizeof(tipoCubo));

           if((fseek(fHash, 0, SEEK_END))!=0){
				fprintf(stderr, "Error: No se ha podido llevar el puntero a la posicion el ficheroHash\n");
				fclose(fHash);
				return -1;
			}

            if (fwrite(&cuboVacio, sizeof(tipoCubo), 1, fHash) != 1) return -2;

            regC->nCubosDes++;
		}

		regC->nCuboDesAct++;

	}

	if((fseek(fHash, posCubo, SEEK_SET))!=0){
		fprintf(stderr, "Error: No se ha podido llevar el puntero a la posicion el ficheroHash\n");
		fclose(fHash);
		return -2;
	}

	if((fwrite(&cubo, sizeof(tipoCubo), 1, fHash))!=1){
		fprintf(stderr, "Error: Problemas en la escritura del fichero hash\n");
		fclose(fHash);
		return -2;
	}

	reg->numReg++;
	regC->numRegDes++;
	return 0;
}

// Parte 2. Funciones gen�rcias para el acceso a los ficheros
int busquedaHash(FILE *fHash, tipoReg *reg, tPosicion *posicion){
	int funcionHash;
	tipoCubo cubo;
	regConfig regC;

	if((fseek(fHash, 0, SEEK_SET))!=0){
		fprintf(stderr, "Error: No se ha podido llevar el puntero a la posicion el ficheroHash\n");
		fclose(fHash);
		return -2;
	}

	fread(&regC, sizeof(regConfig), 1, fHash);
	

	#ifdef ALUM
		funcionHash=atoi(reg->dni)%regC.nCubos;
	#endif

	#ifdef ASIG
		funcionHash=reg->codigo%regC.nCubos;
	#endif

	if((fseek(fHash, 0, SEEK_SET))!=0){
		fprintf(stderr, "Error: No se ha podido llevar el puntero a la posicion el ficheroHash\n");
		return -2;
	}

	long posCubo=sizeof(regConfig)+sizeof(tipoCubo)*funcionHash;

	if((fseek(fHash, posCubo, SEEK_SET))!=0){
		fprintf(stderr, "Error: No se ha podido llevar el puntero a la posicion el ficheroHash\n");
		return -2;
	}

	fread(&cubo, sizeof(tipoCubo), 1, fHash);

	for(int i=0; i<C; i++){
		#ifdef ALUM
			if(!strcmp(cubo.reg[i].dni, reg->dni)){
				*reg = cubo.reg[i];
				posicion->cubo=funcionHash;
				posicion->cuboDes=-1;
				posicion->posReg=i;
				return 0;
			}
		#endif

		#ifdef ASIG
			if(cubo.reg[i].codigo==reg->codigo){
				*reg = cubo.reg[i];
				posicion->cubo=funcionHash;
				posicion->cuboDes=-1;
				posicion->posReg=i;
				return 0;
			}
		#endif
	}

	if((fseek(fHash, 0, SEEK_SET))!=0){
		fprintf(stderr, "Error: No se ha podido llevar el puntero a la posicion el ficheroHash\n");
		return -2;
	}

	posCubo=sizeof(regConfig)+sizeof(tipoCubo)*(regC.nCubos);

	if((fseek(fHash, posCubo, SEEK_SET))!=0){
		fprintf(stderr, "Error: No se ha podido llevar el puntero a la posicion el ficheroHash\n");
		return -2;
	}

	fread(&cubo, sizeof(tipoCubo), 1, fHash);

	for(int j=regC.nCubos; j<regC.nCubos+regC.nCubosDes; j++){
		posCubo = sizeof(regConfig)+sizeof(tipoCubo)*j;

		if((fseek(fHash, 0, SEEK_SET))!=0){
			fprintf(stderr, "Error: No se ha podido llevar el puntero a la posicion el ficheroHash\n");
			return -2;
		}

		if((fseek(fHash, posCubo, SEEK_SET))!=0){
			fprintf(stderr, "Error: No se ha podido llevar el puntero a la posicion el ficheroHash\n");
			return -2;
		}

		fread(&cubo, sizeof(tipoCubo), 1, fHash);

		for(i=0; i<cubo.numRegAsignados; i++){
			#ifdef ALUM
				if(!strcmp(cubo.reg[i].dni, reg->dni)){
					*reg = cubo.reg[i];
					posicion->cubo=funcionHash;
					posicion->cuboDes=posCubo;
					posicion->posReg=i;
					return 0;
				}
			#endif

			#ifdef ASIG
				if(cubo.reg[i].codigo==reg->codigo){
					*reg = cubo.reg[i];
					posicion->cubo=funcionHash;
					posicion->cuboDes=posCubo;
					posicion->posReg=i;
					return 0;
				} 
			#endif
		}
	}

	return -1
}

int modificarReg(FILE *fHash, tipoReg *reg, tPosicion *posicion){
	long posCubo;
	tipoCubo cubo;
	
	if(posicion->cuboDes!=-1){
		posCubo=sizeof(regConfig)+sizeof(tipoCubo)*(posicion->cubo+posicion->cuboDes);
	} else{
		posCubo=sizeof(regConfig)+sizeof(tipoCubo)*(posicion->cubo);
	}

	if((fseek(fHash, posCubo, SEEK_SET))!=0){
			fprintf(stderr, "Error: No se ha podido llevar el puntero a la posicion el ficheroHash\n");
			return -2;
	}

	fread(&cubo, sizeof(tipoCubo), 1, fHash);

	cubo.reg[posicion->posReg]=*reg;

	if((fseek(fHash, posCubo, SEEK_SET))!=0){
			fprintf(stderr, "Error: No se ha podido llevar el puntero a la posicion el ficheroHash\n");
			return -2;
	}

	if((fwrite(&cubo, sizeof(tipoCubo), 1, fHash))!=1){
		fprintf(stderr, "Error: Problemas en la escritura del fichero hash\n");
		return -2;
	}

	return 0;
} 