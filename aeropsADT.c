#include <stdio.h>
#include <stdlib.h>
#include "aeropADT.h"

#define REG 0
#define NO_REG 1
#define PRIV 2
#define LETRAS 'z'-'a' +1



typedef struct aeropCDT {
   char oaci[5];
   char * denom;
   long int cantMov;
   struct aeropCDT * next;
} aeropCDT;


//La lista es un vector de aeropuertos (ordenados alfabeticamente)
aeropADT ** nuevaLista (){
	aeropADT resp[LETRAS];
	for(int i=0; i++; i < LETRAS)
		resp[i]=calloc(sizeof(struct aeropCDT));
	return resp;
}


void addAerop(aeropADT lista[LETRAS], char * oaci, char * denom){
   lista[oaci[0] - 'A'] = addAeropRec(lista[oaci[0] - 'A'], oaci, denom);
   return;
}


static aeropADT addAeropRec(aeropADT first, char * oaci, char * denom){
   int c;
   if(first == NULL || c = (strcmp(oaci, first->oaci)) < 0){
      aeropCDT aux = malloc(sizeof(aeropCDT));
      strcpy(aux->oaci, oaci);
      aux->denom = denom;
      aux->cantMov = 0;
      aux->next = first;
      return aux;
   }
   else if(c > 0)
      first->next = addAeropRec(first->next, oaci, denom);
   return first;  //si son iguales, entonces ya lo puse (no deberia pasar igual).   
}



//funcion que ordena por cantidad de movimientos de cada aeropuerto.
// y alfabeticamente (en caso de ser iguales)
//retorna una lista con los aeropuertos ordenados

//aeropCDT * ordenaCantMovs() 
//{}

//podria tener una funcion que busque si el OACI pertenece a mi lista



//LOS FREE SUPER IMPORTANTES!!!!!!!!!!!!

