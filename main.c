#include <stdlib.h>
#include <stdio.h>
#include "aeropADT.h"
#include "movsADT.h"
#include "procesamiento.h"

void query1(aeropADT lista){   // Recibe la lista ordenada por movimientos
	
	FILE * destino;
	destino = fopen("movimientos_aeropuerto.csv", "wt");   // Va a crear este archivo y va a poner todo ahi

	aeropADT aux = lista;

	while(aux != NULL){
		fprintf(destino, "%s | %s | %ld \n", aux->oaci, aux->denom, aux->cantMov);
		aux = aux->next;
	}

	fclose(destino);
}

void query2(tMovsCDT * header){
	FILE * destino;
	destino = fopen("dia_semana.csv","wt");
	int i;
	char * dias[7] = {"Domingo", "Lunes", "Martes", "Miercoles", "Jueves", "Viernes", "Sabado"};
	
	fprintf(destino, "Dia;Cantidad de vuelos de cabotaje;Cantidad de vuelos Internacionales;Cantidad total\n");
	
	for(i = 1; i < 7; i++){
		fprintf(destino, "%s;%d;%d;%d\n", header->semana[i].cabotaje, header->semana[i].internacional, header->semana[i].cabotaje + header->semana[i].internacional);
	}
	fprintf(destino, "%s;%d;%d;%d\n", header->semana[0].cabotaje, header->semana[0].internacional, header->semana[0].cabotaje + header->semana[0].internacional);
	fclose(destino);

}

void query3(tMovsCDT * l){
	FILE * destino;
	destino = fopen("composicion.csv","wt");
	fprintf(destino, "Cabotaje;Regular;%d\n",l->cabotaje[0]);
	fprintf(destino, "Cabotaje;No Regular;%d\n",l->cabotaje[1]);
	fprintf(destino, "Cabotaje;Vuelo Privado;%d\n",l->cabotaje[2]);
	fprintf(destino, "Internacional;Regular;%d\n",l->internacional[0]);
	fprintf(destino, "Internacional;No Regular;%d\n",l->internacional[1]);
	fprintf(destino, "Internacional;Vuelo Privado;%d\n",l->internacional[2]);
    fclose(destino);

}

int main(void){

	putchar('b');

	
	aeropADT ult = malloc(sizeof(aeropADT));
	strcpy(ult->oaci, "ABCD");
	strcpy(ult->denom, "alpargatas");
	ult->cantMov = 200;
	ult->next = NULL;

	aeropADT ult1 = malloc(sizeof(aeropADT));
	strcpy(ult1->oaci, "QWER");
	strcpy(ult1->denom, "alpaatas");
	ult1->cantMov = 300;
	ult1->next = ult;

	aeropADT ult2 = malloc(sizeof(aeropADT));
	strcpy(ult2->oaci, "JKLD");
	strcpy(ult2->denom, "alptas");
	ult2->cantMov = 400;
	ult2->next = ult1;

	aeropADT ult3 = malloc(sizeof(aeropADT));
	strcpy(ult3->oaci, "VBNM");
	strcpy(ult3->denom, "patas");
	ult3->cantMov = 4600;
	ult3->next = ult2;

	aeropADT l = ult3;
	query1(l);

	return 0;
}
