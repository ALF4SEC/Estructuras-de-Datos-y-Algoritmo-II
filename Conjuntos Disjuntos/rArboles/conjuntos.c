#include "conjuntos.h"
#include <stdio.h>

// Función auxiliar para ver contenido de Partición 
void verParticion(particion P){ 
    int i;
    printf("\n");
    for (i =0;i<MAXIMO;i++) printf("|%2d",P[i]);
    printf("| contenido  vector\n");
    for (i =0;i<MAXIMO;i++) printf("---");
    printf("\n");
    for (i =0;i<MAXIMO;i++) printf(" %2d",i);
    printf("  índices vector\n\n");
}

#ifdef __NO_CRITERIO
    void crea(particion P){
        for(int i; i<MAXIMO; i++){
            P[i]=i;
        }
    }

    tipoConjunto buscar(tipoElemento x, particion P){
        if(P[x]==x){
            return x;
        } else{
            return buscar(P[x], P);
        }
    }

    int unir(tipoConjunto x, tipoConjunto y, particion P){
        if(P[x]=x && P[y]=y){
            P[y]=x;
            return 0;
        } else{
            return -1;
        }
    }
#endif

#ifdef __ALTURA_
    void crea(particion P){
        for(int i=0; i<MAXIMO; i++){
            P[i]=-1;
        }
    }

    tipoConjunto buscar(tipoElemento x, particion P){
        if(P[x]==-1){
            return x;
        } else{
            return buscar(P[x], P);
        }
    }

    int unir(tipoConjunto x, tipoConjunto y, particion P){
        if(P[x]<0 && P[y]<0){
            if(P[x]<P[y]){
                P[y]=x;
            } else if(P[x]>P[y]){
                P[x]=y;
            } else{
                
            }
        } else{
            return -1;
        }
    }
#endif

#ifdef ___TAMANNO_

#endif