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
	long int cabotaje;
	long int internacional;  
} Tdia;



typedef struct tMovsCDT {
   //los dias iran de domingo=0 a sabado=6
   Tdia semana [7];                                      //MOVIMIENTOS
   long int cabotaje [3];         //{REG, NO_REG, PRIV}  //MOVIMIENTOS
   long int internacional [3];    //{REG, NO_REG, PRIV}  //MOVIMIENTOS
} tMovsCDT; 

tMovsCDT * nuevoMov(){
	return calloc(1,sizeof(tMovsCDT));
}

//funcion para sumar a cierto dia si es cabot o internacional
void aumentaDia(tMovsCDT * movs, int clase, int dia){
	if(clase == CABOT){
		movs->semana[dia].cabotaje++;
	}else if(clase == INTER){
		movs->semana[dia].internacional++;
	}
}

//funcion para sumar si es regular, noRegular o privado  HACERLA
void aumentaClasifVuelo(tMovsCDT * movs, int clase, int clasif){
	if(clase == CABOT){
		movs->cabotaje.[clasif]++;
	}else if(clase == INTER){
		movs->internacional.[clasif]++;
	}
}
