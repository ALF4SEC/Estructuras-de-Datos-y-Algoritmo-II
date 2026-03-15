#include "dispersion.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// Crea un fichero hash inicialmente vacio seg�n los criterios especificados en la pr�ctica
// Primera tarea a realizar para  crear un fichero organizado mediante DISPERSI�N
void creaHvacio(char *fichHash)
{ FILE *fHash;
  tipoCubo cubo;
  int j;
  int numCubos =CUBOS+CUBOSDESBORDE;

  memset(&cubo,0,sizeof(cubo));

  fHash = fopen(fichHash,"wb");
  for (j=0;j<numCubos;j++) fwrite(&cubo,sizeof(cubo),1,fHash);
  fclose(fHash);
}

// Lee el contenido del fichero hash organizado mediante el m�todo de DISPERSI�N seg�n los criterios
// especificados en la pr�ctica. Se leen todos los cubos completos tengan registros asignados o no. La
// salida que produce esta funci�n permite visualizar el m�todo de DISPERSI�N
int leeHash(char *fichHash)
{ FILE *f;
  tipoCubo cubo;
  int j,i=0;
  size_t numLee;

   f = fopen(fichHash,"rb");
   rewind(f);
   fread(&cubo,sizeof(cubo),1,f);
   while (!feof(f)){
	for (j=0;j<C;j++) {
        if (j==0)    	printf("Cubo %2d (%2d reg. ASIGNADOS)",i,cubo.numRegAsignados);
        else  	printf("\t\t\t");
	if (j < cubo.numRegAsignados) 
		    printf("\t%s %s %s %s %s\n",
	    		cubo.reg[j].dni,
			cubo.reg[j].nombre,
			cubo.reg[j].ape1,
		  	cubo.reg[j].ape2,
  	                cubo.reg[j].provincia);
	else printf ("\n");
        }
       i++;
       fread(&cubo,sizeof(cubo),1,f);
   }
   fclose(f);
   return i;
}

// funciones a codificar
int creaHash(char *fichEntrada,char *fichHash){
	FILE *ficheroEntrada, *ficheroHash;
	int funcionHash;
	int i=0;
	int numeroRegDesbordados=0;
	tipoAlumno alumno; 
	tipoCubo cubo;

	creaHvacio(fichHash);

	if((ficheroEntrada=fopen(fichEntrada, "rb"))==NULL){
		fprintf(stderr, "Error: No se ha podido abrir el fichero %s\n", fichEntrada);
		return -1;
	}

	if((ficheroHash=fopen(fichHash, "rb+"))==NULL){
		fprintf(stderr, "Error; No se ha podido abrir el fichero %s\n", fichHash);
		return -1;
	}

	if((fseek(ficheroEntrada, 0, SEEK_SET))!=0){
		fprintf(stderr, "Error: No se ha podido llevar el puntero al inicio del fichero %s\n", fichEntrada);
		fclose(ficheroEntrada);
		fclose(ficheroHash);
		return -2;
	}

	if((fseek(ficheroHash, 0, SEEK_SET))!=0){
		fprintf(stderr, "Error: No se ha podido llevar el puntero al inicio del fichero %s\n", fichHash);
		fclose(ficheroEntrada);
		fclose(ficheroHash);
		return -2;
	}

	fread(&alumno, sizeof(tipoAlumno), 1, ficheroEntrada);

	while(!feof(ficheroEntrada)){
		funcionHash=atoi(alumno.dni)%CUBOS;

		if((fseek(ficheroHash, funcionHash*sizeof(tipoCubo), SEEK_SET))!=0){
			fprintf(stderr, "Error: No se ha podido llevar el puntero a la posicion el fichero %s\n", fichEntrada);
			fclose(ficheroEntrada);
			fclose(ficheroHash);
			return -2;
		}

		fread(&cubo, sizeof(tipoCubo), 1, ficheroHash);

		if(cubo.numRegAsignados<C){
			cubo.reg[cubo.numRegAsignados++]=alumno;

			if((fseek(ficheroHash, funcionHash*sizeof(tipoCubo), SEEK_SET))!=0){
				fprintf(stderr, "Error: No se ha podido llevar el puntero a la posicion el fichero %s\n", fichHash);
				fclose(ficheroEntrada);
				fclose(ficheroHash);
				return -2;
			}

			if((fwrite(&cubo, sizeof(tipoCubo), 1, ficheroHash))!=1){
				fprintf(stderr, "Error: Problemas en la escritura del fichero %s\n", fichHash);
				fclose(ficheroEntrada);
				fclose(ficheroHash);
				return -3;
			}

		} else{
			cubo.numRegAsignados++;
			numeroRegDesbordados++;

			if((fseek(ficheroHash, funcionHash*sizeof(tipoCubo), SEEK_SET))!=0){
				fprintf(stderr, "Error: No se ha podido llevar el puntero a la posicion el fichero %s\n", fichHash);
				fclose(ficheroEntrada);
				fclose(ficheroHash);
				return -2;
			}

			if((fwrite(&cubo, sizeof(tipoCubo), 1, ficheroHash))!=1){
				fprintf(stderr, "Error: Problemas en la escritura del fichero %s\n", fichHash);
				fclose(ficheroEntrada);
				fclose(ficheroHash);
				return -3;
			}

			for(i=CUBOS; i<(CUBOS+CUBOSDESBORDE); i++){

				if((fseek(ficheroHash, i*sizeof(tipoCubo), SEEK_SET))!=0){
						fprintf(stderr, "Error: No se ha podido llevar el puntero a la posicion el fichero %s\n", fichHash);
						fclose(ficheroEntrada);
						fclose(ficheroHash);
						return -2;
				}

				fread(&cubo, sizeof(tipoCubo), 1, ficheroHash);

				if(cubo.numRegAsignados<C){
					cubo.reg[cubo.numRegAsignados++]=alumno;

					if((fseek(ficheroHash, i*sizeof(tipoCubo), SEEK_SET))!=0){
						fprintf(stderr, "Error: No se ha podido llevar el puntero a la posicion el fichero %s\n", fichHash);
						fclose(ficheroEntrada);
						fclose(ficheroHash);
						return -2;
					}

					if((fwrite(&cubo, sizeof(tipoCubo), 1, ficheroHash))!=1){
						fprintf(stderr, "Error: Problemas en la escritura del fichero %s\n", fichHash);
						fclose(ficheroEntrada);
						fclose(ficheroHash);
						return -3;
					}

					break;
				} else{
					cubo.numRegAsignados++;
					numeroRegDesbordados++;

					if((fseek(ficheroHash, i*sizeof(tipoCubo), SEEK_SET))!=0){
						fprintf(stderr, "Error: No se ha podido llevar el puntero a la posicion el fichero %s\n", fichHash);
						fclose(ficheroEntrada);
						fclose(ficheroHash);
						return -2;
					}

					if((fwrite(&cubo, sizeof(tipoCubo), 1, ficheroHash))!=1){
						fprintf(stderr, "Error: Problemas en la escritura del fichero %s\n", fichHash);
						fclose(ficheroEntrada	);
						fclose(ficheroHash);
						return -3;
					}
				}
			}

		}

		fread(&alumno, sizeof(tipoAlumno), 1, ficheroEntrada);
	}

	fclose(ficheroEntrada);
	fclose(ficheroHash);
	return numeroRegDesbordados;
}

int buscaReg(FILE *fHash, tipoAlumno *reg,char *dni){
	tipoCubo cubo;
	int funcionHash;

	funcionHash=atoi(dni)%CUBOS;

	if((fseek(fHash, funcionHash*sizeof(tipoCubo), SEEK_SET))!=0){
		fprintf(stderr, "Error: No se ha podido llevar el puntero al inicio del fichero \n");
		return -2;
	}
	
	fread(&cubo, sizeof(tipoCubo), 1, fHash);
	
	if(cubo.numRegAsignados<C){
		for(int i=0; i<C; i++){
			if(!strcmp(cubo.reg[i].dni, dni)){
				*reg = cubo.reg[i];
				return funcionHash;
			}
		}
	} else{
		for(int i=0; i<(CUBOS+CUBOSDESBORDE); i++){
			if((fseek(fHash, i*sizeof(tipoCubo), SEEK_SET))!=0){
				fprintf(stderr, "Error: No se ha podido llevar el puntero al inicio del fichero \n");
				return -2;
			}

			fread(&cubo, sizeof(tipoCubo), 1, fHash);

			for(int j=0; j<C; j++){
				if(!strcmp(cubo.reg[j].dni, dni)){
					*reg = cubo.reg[j];
					return i;
				}
			}
		}
	}

	return -1;
}


int insertarReg(FILE *fHash, tipoAlumno *reg){
	tipoCubo cubo;
	int funcionHash;

	funcionHash=atoi(reg->dni)%CUBOS;

	if((fseek(fHash, funcionHash*sizeof(tipoCubo), SEEK_SET))!=0){
		fprintf(stderr, "Error: No se ha podido llevar el puntero al inicio del fichero \n");
		return -2;
	}

	fread(&cubo, sizeof(tipoCubo), 1, fHash);

	if(cubo.numRegAsignados<C){
		cubo.reg[cubo.numRegAsignados++]=*reg;

		if((fseek(fHash, funcionHash*sizeof(tipoCubo), SEEK_SET))!=0){
			fprintf(stderr, "Error: No se ha podido llevar el puntero al inicio del fichero \n");
			return -2;
		}

		if((fwrite(&cubo, sizeof(tipoCubo), 1, fHash))!=1){
			fprintf(stderr, "Error: Problemas en la escritura del fichero\n");
			return -3;
		}

		return funcionHash;

	} else{
		cubo.numRegAsignados++;

		if((fseek(fHash, funcionHash*sizeof(tipoCubo), SEEK_SET))!=0){
			fprintf(stderr, "Error: No se ha podido llevar el puntero al inicio del fichero \n");
			return -2;
		}

		if((fwrite(&cubo, sizeof(tipoCubo), 1, fHash))!=1){
			fprintf(stderr, "Error: Problemas en la escritura del fichero\n");
			return -3;
		}

		for(int i=CUBOS; i<(CUBOS+CUBOSDESBORDE); i++){

			if((fseek(fHash, i*sizeof(tipoCubo), SEEK_SET))!=0){
				fprintf(stderr, "Error: No se ha podido llevar el puntero al inicio del fichero \n");
				return -2;
			}

			fread(&cubo, sizeof(tipoCubo), 1, fHash);

			if(cubo.numRegAsignados<C){
				cubo.reg[cubo.numRegAsignados++]=*reg;

				if((fseek(fHash, i*sizeof(tipoCubo), SEEK_SET))!=0){
					fprintf(stderr, "Error: No se ha podido llevar el puntero al inicio del fichero \n");
					return -2;
				}

				if((fwrite(&cubo, sizeof(tipoCubo), 1, fHash))!=1){
					fprintf(stderr, "Error: Problemas en la escritura del fichero\n");
					return -3;
				}

				return -1;
			} else{
				cubo.numRegAsignados++;

				if((fseek(fHash, i*sizeof(tipoCubo), SEEK_SET))!=0){
					fprintf(stderr, "Error: No se ha podido llevar el puntero al inicio del fichero \n");
					return -2;
				}

				if((fwrite(&cubo, sizeof(tipoCubo), 1, fHash))!=1){
					fprintf(stderr, "Error: Problemas en la escritura del fichero\n");
					return -3;
				}
			}
		}
	}
}

