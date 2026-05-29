#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "cola.h"



int colaCreaVacia(Cola *c)
{
     if (c == NULL){
        return -2;
     }
    
    c->frente = c->fondo = NULL;
    
    return 0;
}

int colaVacia(Cola *c)
{
    if (c == NULL){
        return -1;
    }else if(c->frente == NULL){
        return 1; //Cola vacía
    }else{
        return 0; //Cola no vacía
    }
    
    
    
}

int colaInserta(Cola *c,tipoElemento elemento)
{
    tipoCelda *nuevo;

    if(c == NULL){
        return -1;
    }else if(NULL == (nuevo = (tipoCelda*)malloc(sizeof(tipoCelda)))){
        return -2;
    }else{
        nuevo->elemento = elemento;
        nuevo->sig = NULL;
        if (c->frente == NULL) {
            c->frente = nuevo;
            c->fondo = nuevo;
        } else {
            c->fondo->sig = nuevo;
            c->fondo = nuevo;
        }
        return 0;
    }
    
    
    
}

tipoElemento colaSuprime(Cola *c)
{
    tipoCelda *aBorrar;
    tipoElemento elementoABorrar;

     if(c == NULL){
        return NULL;
    }else if(c->frente == NULL){
        return NULL;
    }else{
        aBorrar = c->frente;
        elementoABorrar = aBorrar->elemento;
        c->frente = aBorrar->sig;
        
        if(c->frente == NULL){
        	c->fondo = NULL;
        }
        
        free(aBorrar);
        return elementoABorrar;

    }
    
    
}
