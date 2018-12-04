#include <stdio.h>
#include <stdlib.h>
#include "aeropADT.h"

#define REG 0
#define NO_REG 1
#define PRIV 2

typedef struct aeropCDT * aeropADT; 


typedef struct aeropCDT {
   char oaci[5];
   char * denom;
   long int cantMov;
   struct aeropCDT * next;
} aeropCDT;



typedef struct listaCDT {
   struct aeropCDT * aerops['Z' - 'A' + 1];  //un vector de listas (ordenadas alfabeticamente)  
} listaCDT;                                  // de aeropueros ordenados alfabeticamente 


listaADT nuevaLista (){
	return calloc (1, sizeof(listaCDT));
}


listaADT addAerop(listaADT lista, char * oaci, char * denom){ //si no recibo el oaci, entonces no se en que letra ponerlo
   /*if(lista->aerops[oaci[0] - 'A'] == NULL){
      aeropADT aux = malloc(sizeof(aeropADT));

      strcpy(lista->aerops[oaci[0] - 'A']->oaci, oaci);
      lista->aerops[oaci[0] - 'A']->denom = denom;

   
   }else{*/
      lista->aerops[oaci[0] - 'A'] = addAeropRec(lista->aerops[oaci[0] - 'A'], oaci, denom);
   
   return listaADT;
}


static aeropCDT * addAeropRec(aeropADT * first, char * oaci, char * denom){
   int c;
   if(first == NULL || c = (strcmp(oaci, first->oaci)) < 0){
      aeropCDT * aux = malloc(sizeof(aeropCDT));
      strcpy(aux->oaci, oaci);
      aux->denom = denom;
      aux->cantMov = 0;
      aux->next = first;
      return aux;
   }
   else if(c > 0){
      first->next = addAeropRec(first->next, oaci, denom);
   }
      return first;  //si son iguales, entonces ya lo puse (no deberia pasar igual).   
}



//funcion que ordena por cantidad de movimientos de cada aeropuerto.
// y alfabeticamente (en caso de ser iguales)
//retorna una lista con los aeropuertos ordenados

aeropCDT * ordenaCantMovs() 
{}

//podria tener una funcion que busque si el OACI pertenece a mi lista



LOS FREE SUPER IMPORTANTES!!!!!!!!!!!!

