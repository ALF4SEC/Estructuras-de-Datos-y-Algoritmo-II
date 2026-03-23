#include "conjuntos.h"
#include <stdio.h>
/// Incluir aqui las funciones que implementan las tres operaciones básicas 
/// en la representación de CONJUNTOS DISJUNTOS mediante MATRICES

// Función auxiliar para ver contenido de Partición 
void verParticion(particion P)
{ int i;
    printf("\n");
    for (i =0;i<MAXIMO;i++) printf("|%2d",P[i]);
    printf("| contenido  vector\n");
    for (i =0;i<MAXIMO;i++) printf("---");
    printf("\n");
    for (i =0;i<MAXIMO;i++) printf(" %2d",i);
    printf("  índices vector\n\n");
}

// Funciones a implementar
void crea(particion P){
    for(int i=0; i<MAXIMO; i++){
        P[i]=i;
    }
}

tipoConjunto buscar(tipoElemento x, particion P){
    return P[x];
}

// Implementación de operación unir con control de representantes:
// Si x e y son los representantes de sus clases de equivalencia las unen y devuelven VERDADERO,
// en otro caso no hace nada y devuelve FALSO
int unir(tipoConjunto x, tipoConjunto y, particion P){
    if(x=P[x] && y=P[y]){
        for(int i=0; i<MAXIMO; i++){
            if(P[i]=y){
                P[i]=x;
            }
        }
        return 1;
    } else{
        return 0;
    }
}

// Funciones proporcionadas
void verParticion(particion P){
    for(int j=0; j<MAXIMO;j++){
        printf("Conjunto %d: ", j);
        for(int i=0; i<MAXIMO; i++){
            if(P[i]=j){
                printf("%d", j);
            }
        }
        printf ("\n");
    }
}



