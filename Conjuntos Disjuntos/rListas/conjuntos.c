#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "conjuntos.h"

/// Incluir aqui las funciones que implementan las tres operaciones básicas 
/// en la representación de CONJUNTOS DISJUNTOS mediante LISTAS
void verParticion(particion P)
{ int i;
   tipoCelda *aux;
    for (i =0;i<MAXIMO;i++) {
         aux = P[i].primero;
         if (aux!=NULL)  printf("\n\nClase equivalencia representante %d: ",i);
        while (aux!=NULL)
        { printf("%d ",aux->elemento);
         aux=aux->sig;
        }
    }
}

void verClaseEquivalencia(tipoElemento x,particion P)
{ int representante;
  tipoCelda *aux;
  
    representante = buscar(x,P);
    printf("\n\nClase de Equivalencia de %d cuyo representante es %d: ", x,representante);
    aux = P[representante].primero;
    while (aux)
        { printf(" %d ",aux->elemento);
          aux=aux->sig;
        }
    printf("\n\n");
}

void crea(particion P){
  
}

tipoConjunto buscar(tipoElemento x, particion P){

}

// Implementación de operación unir con control de representantes:
// Si x e y son los representantes de sus clases de equivalencia las unen y devuelven VERDADERO,
// en otro caso no hace nada y devuelve FALSO
int unir(tipoConjunto x, tipoConjunto y, particion P){

}

// Funciones proporcionadas
void verParticion(particion P){

}

void verClaseEquivalencia(tipoElemento x,particion P){

}