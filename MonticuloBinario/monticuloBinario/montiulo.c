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
        return 0;
    } else{
        return -1;
    }
}

int eliminarMinimo(Monticulo *m, tipoElemento *minimo){
    if(m->tamanno>0){
        minimo=m->elemento[1];
        m->elemento[1]=m->elemento[m->tamanno];
        m->tamanno--;
        filtradoDescendente(m, 1);
        return 0;
    } else{
        return -1; 
    }
}

void decrementarClave(int pos, tipoClave cantidad, Monticulo *m){
    if(0<pos && pos<=m->tamanno){
        m->elemento[pos].clave-=cantidad;
        filtradoAscendente(m, pos);
        return 0;
    } else{
        return -1;
    }
}

void incrementarClave(int pos, tipoClave cantidad, Monticulo *m){
    if(0<pos && pos<=m->tamanno){
        m->elemento[pos].clave+=cantidad;
        filtradoDescendente(m, pos);
        return 0;
    } else{
        return -1;
    }
}

int esMonticulo(Monticulo m){
    
    for(int i=m->tamanno; i>1; i--){
        if(!(m->elemento[i/2].clave<m->elemento[i].clave)){
            return 0
        }
    }
    return 1;
}

/* Funciones auxiliares que conviene implementar: las dos estrategias de filtrado en las 
   que se basan todos los algoritmos que manejan montículos */
void filtradoDescendente(Monticulo *m, int i);
void filtradoAscendente(Monticulo *m, int i);

/* Operación crearMonticulo la utilizaremos en ejercicio 2 y en tema de grafos */ 

void crearMonticulo(Monticulo *m, int n){
    m->tamanno=n;

}

void heapsort(Monticulo *m){
    for(int i=m->tamanno; i>0; i--){

    }
}