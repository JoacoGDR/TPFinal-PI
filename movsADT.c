#include <stdio.h>
#include <stdlib.h>
#include "movsADT.h"

#define REG 0
#define NO_REG 1
#define PRIV 2

#define CABOT 20
#define INTER 21
#define NA 22


typedef struct dia {
	long int cabot;
	long int inter;  
} Tdia;



typedef struct tMovsCDT {
   //los dias iran de domingo=0 a sabado=6
   Tdia semana [9];                                      //MOVIMIENTOS
   long int cabot [3];         //{REG, NO_REG, PRIV}  //MOVIMIENTOS
   long int inter [3];    //{REG, NO_REG, PRIV}  //MOVIMIENTOS
} tMovsCDT; 

tMovsADT newMov(){
	return calloc(1,sizeof(tMovsCDT));
}

//funcion para sumar a cierto dia si es cabot o internacional
void aumentaDia(tMovsADT movs, int clasif, int dia){
	if(clasif == CABOT){
		movs->semana[dia].cabot++;
	}else if(clasif == INTER){
		movs->semana[dia].inter++;
	}
}

//funcion para sumar si es regular, noRegular o privado  HACERLA
void aumentaClasifVuelo(tMovsADT movs, int clase, int clasif){
	if(clase == NA)
		return;
	if(clasif == CABOT){
		movs->cabot[clase]++;
	}else if(clasif == INTER){
		movs->inter[clase]++;
	}
}

void printPorSemana (tMovsADT h, FILE * destino){
	int i;
	char * dias[7] = {"Domingo", "Lunes", "Martes", "Miercoles", "Jueves", "Viernes", "Sabado"};

	for(i = 1; i < 7; i++){
		fprintf(destino, "%s;%ld;%ld;%ld\n", dias[i], h->semana[i].cabot, h->semana[i].inter, h->semana[i].cabot + h->semana[i].inter);
	}
	fprintf(destino, "%s;%ld;%ld;%ld\n", dias[0], h->semana[0].cabot, h->semana[0].inter, h->semana[0].cabot + h->semana[0].inter);
}



void printPorVuelo (tMovsADT l , FILE * destino){
	char * clasifsV[3] = {"Regular", "No Regular", "Vuelo Privado"}; //clasificacion de los vuelos
	
	int i;
	for(i = 0; i < 3; i++){
		fprintf(destino, "Cabotaje;%s;%ld\n", clasifsV[i], l->cabot[i]);
	}
	
	for(i = 0; i < 3; i++){
		fprintf(destino, "Internacional;%s;%ld\n", clasifsV[i], l->inter[i]);
	}
	
}



