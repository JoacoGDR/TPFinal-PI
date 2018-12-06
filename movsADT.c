#include <stdio.h>
#include <stdlib.h>
#include "movsADT.h"
#include "aeropADT.h"
#include "procesamiento.h"

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
   Tdia semana [9];                                      //MOVIMIENTOS
   long int cabotaje [3];         //{REG, NO_REG, PRIV}  //MOVIMIENTOS
   long int internacional [3];    //{REG, NO_REG, PRIV}  //MOVIMIENTOS
} tMovsCDT; 

tMovsCDT * newMov(){
	return calloc(1,sizeof(tMovsCDT));
}

//funcion para sumar a cierto dia si es cabot o internacional
void aumentaDia(tMovsADT movs, int clasif, int dia){
	if(clasif == CABOT){
		movs->semana[dia].cabotaje++;
	}else if(clasif == INTER){
		movs->semana[dia].internacional++;
	}
}

//funcion para sumar si es regular, noRegular o privado  HACERLA
void aumentaClasifVuelo(tMovsADT movs, int clase, int clasif){
	if(clase == NA)
		return;
	if(clasif == CABOT){
		movs->cabotaje[clase]++;
	}else if(clasif == INTER){
		movs->internacional[clase]++;
	}
}

void query2(tMovsADT header){
	FILE * destino;
	destino = fopen("dia_semana.csv","wt");
	int i;
	char * dias[7] = {"Domingo", "Lunes", "Martes", "Miercoles", "Jueves", "Viernes", "Sabado"};
	
	fprintf(destino, "Dia;Cantidad de vuelos de cabotaje;Cantidad de vuelos Internacionales;Cantidad total\n");
	
	for(i = 1; i < 7; i++){
		fprintf(destino, "%s;%ld;%ld;%ld\n", dias[i], header->semana[i].cabotaje, header->semana[i].internacional, header->semana[i].cabotaje + header->semana[i].internacional);
	}
	fprintf(destino, "%s;%ld;%ld;%ld\n", dias[0], header->semana[0].cabotaje, header->semana[0].internacional, header->semana[0].cabotaje + header->semana[0].internacional);
	fclose(destino);

}

void query3(tMovsADT l){
	FILE * destino;
	destino = fopen("composicion.csv","wt");
	
	
	char * clasifsV[3] = {"Regular", "No Regular", "Vuelo Privado"}; //clasificacion de los vuelos
	
	int j;
	
	fprintf(destino, "Clase de vuelo;Clasificacion de vuelo;Cantidad de vuelos con esa composicion\n");
	
	for(j = 0; j < 3; j++){
		fprintf(destino, "Cabotaje;%s;%ld\n", clasifsV[j], l->cabotaje[j]);
	}
	
	for(j = 0; j < 3; j++){
		fprintf(destino, "Internacional;%s;%ld\n", clasifsV[j], l->internacional[j]);
	}
	//O BIEN PODRIAMOS HACER UNA FUNCION QUE HAGA ESO...
	//PARA NO REPETIR EL FOR...
	
    fclose(destino);

}
