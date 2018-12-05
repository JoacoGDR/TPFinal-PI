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
