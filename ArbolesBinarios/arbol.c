#include <stdlib.h>
#include <stdio.h>
#include "arbol.h"
#include "cola.h"

// Reserva de memoria para un nuevo nodo de árbol binario
Arbol creaNodo(tipoInfo info)
{ tipoNodo * nuevo;

  //   nuevo =(tipoNodo *)calloc(1, sizeof(tipoNodo));
  if ((nuevo =(tipoNodo *)malloc(sizeof(tipoNodo)))==NULL)
	return NULL;
  else
  { 	nuevo->info=info;
	nuevo->izq=NULL;
	nuevo->der=NULL;
	return nuevo;
   }
}


// Recorrido en amplitud o por niveles: necesita una cola de punteros a nodos de árbol binario!!!
void amplitud(Arbol raiz)
{ Cola c;
  tipoNodo *nodo;
  colaCreaVacia(&c);
  nodo = raiz;
  if (raiz!=NULL) colaInserta(&c,nodo);
  while (!colaVacia(&c))
  { nodo = (Arbol) colaSuprime(&c);
    printf(" %c ", nodo->info);
    if (nodo->izq!=NULL) colaInserta(&c,nodo->izq);
    if (nodo->der!=NULL) colaInserta(&c,nodo->der);
  }
}

// Recorridos en profundidad "recursivos"
void preOrden(Arbol raiz)
{ if (raiz!=NULL)
  { printf("%c ",raiz->info);
    preOrden(raiz->izq);
    preOrden(raiz->der);
  }
}

void enOrden(Arbol raiz)
{ if (raiz!=NULL)
  { enOrden(raiz->izq);
    printf("%c ",raiz->info);
    enOrden(raiz->der);
  }
}

void postOrden(Arbol raiz)
{ if (raiz!=NULL)
  { postOrden(raiz->izq);
    postOrden(raiz->der);
    printf("%c ",raiz->info);
  }
}

int altura(Arbol raiz){ 
  int altIzq, altDer;

  if(raiz==NULL){
    return -1;
  } else{
    altIzq = altura(raiz->izq);
    altDer = altura(raiz->der);
    
    if (altIzq < altDer) {
        return altDer + 1;
    } else {
        return altIzq + 1;
    }
  }
}

int numNodos(Arbol raiz){
  if(raiz==NULL){
    return 0;
  } else{
    return (numNodos(raiz->izq)+numNodos(raiz->der)+1);
  }
}

Arbol anula(Arbol raiz){
  Arbol anulaIzq, anulaDer;

  if(raiz==NULL){
    return NULL;
  } else{
    anulaIzq=anula(raiz->izq);
    anulaDer=anula(raiz->der);

    free(raiz);
    return NULL;
  }
}

int sustituye(Arbol raiz, tipoInfo x, tipoInfo y){
  int izq, der;

  if(raiz==NULL){
    return 0;
  } else{
    izq=sustituye(raiz->izq, x, y);
    der=sustituye(raiz->der, x, y);

    if(raiz->info==x){
      raiz->info=y;
      return 1;
    } else{
      return (izq+der);
    }

  }
}

int numNodosHoja(Arbol raiz){
  int izq, der;

  if(raiz==NULL){
	return -1;
  } else{
	izq=numNodosHoja(raiz->izq);
	der=numNodosHoja(raiz->der);

	if(izq==-1 && der==-1){
		return 1; 
	} else{
		return izq+der;
	}

  }
}

int numNodosInternos(Arbol raiz){
	int izq, der;

	if(raiz==NULL){
		return -1;
	} else{
		izq=numNodosInternos(raiz->izq);
		der=numNodosInternos(raiz->der);

		if(izq==-1 && der==-1){
			return 0; 
		} else{
			return izq+der+1;
		}
		
	}
}

int numHijoUnico(Arbol raiz){
	int izq, der;

	if(raiz==NULL){
		return -1;
	} else{
		izq=numHijoUnico(raiz->izq);
		der=numHijoUnico(raiz->der);

		if((izq==-1 && der!=-1) || (izq!=-1 && der==-1)){
			return 1;
		} else if(izq==-1 && der==-1){
			return 0;
		} else{
			return izq+der;
		}
	}
}

Arbol buscarMax(Arbol raiz){
  Arbol nodo;
  Arbol izq=NULL, der=NULL;

  if(raiz==NULL){
    return raiz;
  } else{
    izq=buscarMax(raiz->izq);
    der=buscarMax(raiz->der);
    nodo=raiz;
    
    if(izq!=NULL && (izq->info - '0')>(nodo->info - '0')){
      nodo=izq;
    } 
    
    if(der!=NULL && (der->info - '0')>(nodo->info - '0')){
      nodo=der;
    } 
      
    return nodo;
  }
}

Arbol buscarMin(Arbol raiz){
  Arbol nodo=NULL;
  Arbol izq=NULL, der=NULL;

  if(raiz==NULL){
    return raiz;
  } else{
    izq=buscarMin(raiz->izq);
    der=buscarMin(raiz->der);
    nodo=raiz;
    
    if(izq!=NULL && (izq->info - '0')<(nodo->info - '0')){
      nodo=izq;
    } 
    
    if(der!=NULL && (der->info - '0')<(nodo->info - '0')){
      nodo=der;
    } 
      
    return nodo;
  }
}

int similares(Arbol r1,Arbol r2){
  int izq, der;

  if(r1==NULL && r2==NULL){
    return 1;
  } else if(r1==NULL || r2==NULL){
    return 0;
  } else{
    izq=similares(r1->izq, r2->izq);
    der=similares(r2->der, r2->der);

    return izq*der;
  }
}

int equivalentes(Arbol r1,Arbol r2){
  int izq, der;

  if(r1==NULL && r2==NULL){
    return 1;
  } else if(r1==NULL || r2==NULL){
    return 0;
  } else{
    izq=equivalentes(r1->izq, r2->izq);
    der=equivalentes(r1->der, r2->der);

    if(r1->info!=r2->info){
      return 0;
    } else{
      return izq*der;
    }
  }
}

Arbol especular(Arbol raiz){
	Arbol izq, der, arbol;

	if(raiz==NULL){
		return NULL;
	} else{
		arbol=creaNodo(raiz->info);
		izq=especular(raiz->izq);
		der=especular(raiz->der);

		arbol=der;
		arbol=izq;
		return arbol;
	}
}

int evaluar(Arbol raiz){
  int izq, der;

  if(raiz==NULL){
   return 0;
  } else{
    izq=evaluar(raiz->izq);
    der=evaluar(raiz->der);

    if(der<=0 && izq<=0){
      return(raiz->info-'0');
    } else{
      switch(raiz->info){
      case '+':
        return(evaluar(raiz->izq)+evaluar(raiz->der));
        break;
      case '-':
        return(evaluar(raiz->izq)-evaluar(raiz->der));
        break;
      case '*':
        return(evaluar(raiz->izq)*evaluar(raiz->der));
        break;
      }
    }
  } 
}
