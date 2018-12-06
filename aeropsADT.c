#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "aeropADT.h"
#include "procesamiento.h"
#include "movsADT.h"

#define REG 0
#define NO_REG 1
#define PRIV 2



typedef struct aeropCDT {
   char oaci[5];
   char denom[70];
   long int cantMov;
   struct aeropCDT * next;
} aeropCDT;

typedef struct vecList{
	aeropCDT * vecAeros[27];  //aca ya tengo un vector de pteros a aeropCDT
}vecList;


//La lista es un vector de aeropuertos (ordenados alfabeticamente)
vec nuevaLista (){
	vec new = calloc(1, sizeof(vecList));
	
int i;
	for(i = 0; i<27; i++)
		new->vecAeros[i] = calloc(1,sizeof(aeropCDT));
	return new;
}

static aeropADT addAeropRec(aeropADT first, char oaci[5], char denom[70]){
   int c;
   if(first == NULL || (c = strcmp(oaci, first->oaci)) < 0){
      aeropADT aux = malloc(sizeof(aeropCDT));
      strcpy(aux->oaci, oaci);
      strcpy(aux->denom, denom);
      aux->cantMov = 0;
      aux->next = first;
      return aux;
   }
   else if(c > 0)
      first->next = addAeropRec(first->next, oaci, denom);
   return first;  //si son iguales, entonces ya lo puse (no deberia pasar igual).   
}

void addAerop(vec lista, char oaci[5], char denom[70]){
   lista->vecAeros[oaci[0] - 'A'] = addAeropRec(lista->vecAeros[oaci[0] - 'A'], oaci, denom);
   return;
}




//Función que busca un aeropuerto y si existe en la lista entonces le agrega un movimiento
int agregarMov(vec list, char oaci[5]){
	aeropADT aux = list->vecAeros[oaci[0]-'A'];
	int c;
	while(aux != NULL && (c=strcmp(aux->oaci,oaci)) <= 0){
		if(c==0){
			aux->cantMov += 1;
			return 1;
		}
		aux = aux->next;
	}
	return 0;
}

//funcion que ordena por cantidad de movimientos de cada aeropuerto.
// y alfabeticamente (en caso de ser iguales)
//retorna una lista con los aeropuertos ordenados

//funcion que ordena por cantidad de movimientos de cada aeropuerto.
// y alfabeticamente (en caso de ser iguales)
//retorna una lista con los aeropuertos ordenados

static aeropADT addOrdenadoRec(aeropADT first, aeropADT nuevo){
   int c;
   if(first == NULL || (c=(first->cantMov - nuevo->cantMov))< 0){
      aeropADT aux = malloc(sizeof(aeropCDT));
      strcpy(aux->oaci, nuevo->oaci);
      strcpy(aux->denom, nuevo->denom);
      aux->cantMov = nuevo->cantMov;
      aux->next = first;
      return aux;
   }
   if(c >= 0)
      first->next = addOrdenadoRec(first->next, nuevo);
   return first;
} 

aeropADT ordenaCantMovs(vec lista){   
   int i = 0;
   aeropADT resp = NULL;
   aeropADT aux;
   while(i < LETRAS){
      for(;i < LETRAS && lista->vecAeros[i] == NULL ; i++)
     	 free(lista->vecAeros[i]);// Si es NULL entonces libero(porque habia hecho calloc) y me muevo al siguiente.                                     
      if(i < LETRAS){
	aux = lista->vecAeros[i];
	resp = addOrdenadoRec(resp, aux);
 	
	lista->vecAeros[i] = lista->vecAeros[i]->next;
	
         free(aux);  //libero el que saque de mi vector
      }
              
   }

   free(lista->vecAeros);  //ya libere cada coso del vector [][][][] ahora libero el vector en si
  // free(lista); valg
   return resp;
}
void freeListaOrdenada(aeropADT first){
   if(first == NULL)
      return;
   freeListaOrdenada(first->next);
   free(first);
	return;
}

void query1(aeropADT lista){   // Recibe la lista ordenada por movimientos
   
   FILE * destino;
   destino = fopen("a.csv", "wt");   // Va a crear este archivo y va a poner todo ahi

   aeropADT aux = lista;
   
   fprintf(destino, "OACI;Denominacion;Cantidad de Movimientos\n");

   while(aux != NULL){
      fprintf(destino, "%s;%s;%ld \n", aux->oaci, aux->denom, aux->cantMov);
      aux = aux->next;
   }

   fclose(destino);
}
//////////////////////////////

//podria tener una funcion que busque si el OACI pertenece a mi lista



//LOS FREE SUPER IMPORTANTES!!!!!!!!!!!!
