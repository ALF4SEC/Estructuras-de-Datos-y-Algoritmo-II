#ifndef __CONJUNTOS_A_H
#define __CONJUNTOS_A_H

#define MAXIMO 16

typedef int particion[MAXIMO];
typedef int tipoConjunto;
typedef int tipoElemento;

#ifndef __NO_CRITERIO
#define __NO_CRITERIO
void crea(particion P);

tipoConjunto buscar(tipoElemento x, particion P);

int unir(tipoConjunto x, tipoConjunto y, particion P);
#endif

//Funicones de union por altura
#ifndef __ALTURA_
#define __ALTURA_
void crea(particion P);

tipoConjunto buscar(tipoElemento x, particion P);

int unir(tipoConjunto x, tipoConjunto y, particion P);

#endif

//Funciones de union por tamanno
#ifndef __TAMANNO_
#define __TAMANNO_
// Funciones a implementar
void crea(particion P);

tipoConjunto buscar(tipoElemento x, particion P);

int unir(tipoConjunto x, tipoConjunto y, particion P);
#endif

#endif

