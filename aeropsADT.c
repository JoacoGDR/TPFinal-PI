#include <stdio.h>
#include <stdlib.h>
#include "aeropADT.h"

#define REG 0
#define NO_REG 1
#define PRIV 2
#define LETRAS 'z'-'a' + 1



typedef struct aeropCDT {
   char oaci[5];
   char denom[70];
   long int cantMov;
   struct aeropCDT * next;
} aeropCDT;


//La lista es un vector de aeropuertos (ordenados alfabeticamente)
aeropADT * nuevaLista (){
	aeropADT resp[LETRAS];
	for(int i = 0; i++; i < LETRAS)
		resp[i]=calloc(1, sizeof(struct aeropCDT));
	return resp;
}


void addAerop(aeropADT lista[LETRAS], char * oaci, char * denom){
   lista[oaci[0] - 'A'] = addAeropRec(lista[oaci[0] - 'A'], oaci, denom);
   return;
}


static aeropADT addAeropRec(aeropADT first, char * oaci, char * denom){
   int c;
   if(first == NULL || (c = strcmp(oaci, first->oaci)) < 0){
      aeropCDT aux = malloc(sizeof(aeropCDT));
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

int perteneceOaci(aeropADT list[LETRAS], char oaci[5]){
	aeropADT aux = list[oaci[0]-'A'];
	int c;
	while(aux != NULL && (c=strcmp(aux->oaci,oaci)) <= 0){
		if(c==0)
			return 1;
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

//LO AGREGUE RECIEEENNN   CHEQUEEENLO!!!!!!!!!!!!1
//!!!!!!!!!!!!!!!!!!!
aeropADT * ordenaCantMovs(aeropADT  lista){   //quiza tenga que ser void nose. preguntar..
   int i;
   aeropADT * listOrdenadaAerops = NULL;

   while(i < LETRAS){  //cambiar por LETRAS.

   //recorro el vector y veo si es NULL esa letra.
      for(i = 0; lista[i] == NULL; i++);         //tecnicamente habiamos hecho un calloc por cada letra
                                                 //tendria que liberarlos si estan en NULL??

      if(i < LETRAS){
         aeropADT aux = malloc(sizeof(aeropADT));
         aux = lista[i];
         lista[i] = lista[i]->next;

         listOrdenadaAerops = addOrdenadoRec(listOrdenadaAerops, aux);
         free(aux);  //libero el que saque de mi vector
      
      }        
   }

   free(lista);  //ya libere cada coso del vector [][][][] ahora libero el vector en si

   return listOrdenadaAerops;
}

aeropADT addOrdenadoRec(aeropADT first, aeropADT nuevo){
   if(first == NULL || first->cantMov < nuevo->cantMov){
      aeropADT aux = malloc(sizeof(aeropADT));
      strcpy(aux->oaci, nuevo->oaci);
      strcpy(aux->denom, nuevo->denom);
      aux->cantMov = nuevo->cantMov;
      aux->next = first;
      return aux;
   }
   if(first->cantMov > nuevo->cantMov)
      first->next = addOrdenadoRec(first->next, nuevo);
   return first;
} 
//////////////////////////////

//podria tener una funcion que busque si el OACI pertenece a mi lista



//LOS FREE SUPER IMPORTANTES!!!!!!!!!!!!

