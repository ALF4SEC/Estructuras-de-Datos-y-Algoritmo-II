#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "pila.h"



int pilaCreaVacia(Pila *p)
{
    if (p == NULL){
        return -1;
    }
    
    *p = NULL;

    return 0;
}

int pilaVacia(Pila *p)
{
    if (p == NULL) {
        return -1;
    } else if (*p == NULL) {
        return 1; //Pila vacía
    } else {
        return 0; //Pila no vacía
    } 
}

int pilaInserta(Pila *p,tipoElemento elemento)
{

    tipoCelda *nuevo;

    if(p == NULL){
        return -1;
    }else if(NULL == (nuevo = (tipoCelda*)malloc(sizeof(tipoCelda)))){
        return -2;
    }else{
        nuevo->elemento = elemento;
        nuevo->sig = *p;
        *p = nuevo;
        return 0;
    }
        
}

tipoElemento pilaSuprime(Pila *p)
{
    tipoCelda * aBorrar;
    tipoElemento elementoABorrar;

    if (p == NULL)
    {
        return NULL;
    }else if (*p == NULL)
    {
        return NULL;
    }else{
        aBorrar = *p;
        elementoABorrar = aBorrar->elemento;
        *p = aBorrar->sig;
        
        free(aBorrar);
        
        return elementoABorrar;
    }
    
    


   
}
