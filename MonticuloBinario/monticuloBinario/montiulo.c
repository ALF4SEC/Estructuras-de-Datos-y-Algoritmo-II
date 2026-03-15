#include <stdio.h>
#include "monticulo.h"

/* Ejercicio 1 */

void iniciaMonticulo(Monticulo *m){
    m->tamanno=0;
}

int vacioMonticulo(Monticulo m){
    if(m->tamanno=0){
        return 1;
    } else{
        return 0;
    }

}


int insertar(tipoElemento x, Monticulo *m){
    if(m->tamanno<MAXIMO){
        m->tamanno++;
        m->elemento[m->tamanno]=x; 
        filtradoAscendente(m, m->tamanno);
    } else{
        return -1;
    }
}

int eliminarMinimo(Monticulo *m, tipoElemento *minimo){
    if(m->tamanno>0){
        m->elemento[1]=m->elemento[m->tamanno];
        m->tamanno--;
        
    } else{
        return -1; 
    }
}

void decrementarClave(int pos, tipoClave cantidad, Monticulo *m){

}

void incrementarClave(int pos, tipoClave cantidad, Monticulo *m){

}

int esMonticulo(Monticulo m){

}

/* Funciones auxiliares que conviene implementar: las dos estrategias de filtrado en las 
   que se basan todos los algoritmos que manejan montículos */

void filtradoDescendente(Monticulo *m, int i);
void filtradoAscendente(Monticulo *m, int i);

/* Operación crearMonticulo la utilizaremos en ejercicio 2 y en tema de grafos */ 

void crearMonticulo(Monticulo *m);

void heapsort(Monticulo *m);