#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arbol.h"

int main(void){ 
  Arbol varArbol, varArbol1, varArbol2;

/* Creación arbol ejemplo de las transparencias de recorridos */
  varArbol = creaNodo('A');
  varArbol->izq=creaNodo('B');
  varArbol->der = creaNodo('C');
  varArbol->izq->izq=creaNodo('D');
  varArbol->izq->der=creaNodo('E');
  varArbol->der->izq=creaNodo('F');
  varArbol->der->der=creaNodo('G');

  varArbol1 = creaNodo('A');
  varArbol1->izq=creaNodo('B');
  varArbol1->der = creaNodo('C');
  varArbol1->izq->izq=creaNodo('D');
  varArbol1->izq->der=creaNodo('E');
  varArbol1->der->izq=creaNodo('F');
  varArbol1->der->der=creaNodo('H');

  varArbol2 = creaNodo('1');
  varArbol2->izq=creaNodo('2');
  varArbol2->der = creaNodo('3');
  varArbol2->izq->izq=creaNodo('4');
  varArbol2->izq->der=creaNodo('5');
  varArbol2->der->izq=creaNodo('6');
  varArbol2->der->der=creaNodo('7');

/* Aplicación de recorridos al arbol ejemplo */

  printf("Recorrido en PRE_ORDEN: ");
  preOrden(varArbol);
  printf("\n");
  printf("Recorrido en ORDEN: ");
  enOrden(varArbol);
  printf("\n");
  printf("Recorrido en POST_ORDEN: ");
  postOrden(varArbol);
  printf("\n");
  printf("Recorrido en AMPLITUD: ");
  amplitud(varArbol);
  printf("\n");

/* Comenzar a implementar y probar las funciones del ejercicio 2 ... y segunda parte del ejercicio 3 */
  printf("Altura del arbol: %d\n", altura(varArbol));
  printf("Num nodeos del arbol: %d\n", numNodos(varArbol));
  printf("Numero nodos hoja del arbol: %d\n", numNodosHoja(varArbol));
  printf("Numero nodos internos del arbol: %d\n", numNodosInternos(varArbol));
  printf("Numero hijos unico del arbol: %d\n", numHijoUnico(varArbol));
  printf("Arboles similares: %d\n", similares(varArbol, varArbol1));
  printf("Arboles equivalentes: %d\n", equivalentes(varArbol, varArbol1));
  Arbol resultado=buscarMax(varArbol2);
  printf("Arboles Max: %c\n", resultado->info);
  resultado=buscarMin(varArbol2);
  printf("Arboles min: %c\n", resultado->info);


  return 1;
}

