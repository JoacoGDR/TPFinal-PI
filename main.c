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
	fprintf(destino, "lunes;%d;%d;%d\n",header->semana[1].cabotaje,header->semana[1].internacional,header->semana[1].cabotaje+header->semana[1].internacional);
	fprintf(destino, "martes;%d;%d;%d\n",header->semana[2].cabotaje,header->semana[2].internacional,header->semana[2].cabotaje+header->semana[2].internacional);
	fprintf(destino, "miercoles;%d;%d;%d\n",header->semana[3].cabotaje,header->semana[3].internacional,header->semana[3].cabotaje+header->semana[3].internacional);
	fprintf(destino, "jueves;%d;%d;%d\n",header->semana[4].cabotaje,header->semana[4].internacional,header->semana[4].cabotaje+header->semana[4].internacional);
	fprintf(destino, "viernes;%d;%d;%d\n",header->semana[5].cabotaje,header->semana[5].internacional,header->semana[5].cabotaje+header->semana[5].internacional);
	fprintf(destino, "sabado;%d;%d;%d\n",header->semana[6].cabotaje,header->semana[6].internacional,header->semana[6].cabotaje+header->semana[6].internacional);
	fprintf(destino, "domingo;%d;%d;%d\n",header->semana[0].cabotaje,header->semana[0].internacional,header->semana[0].cabotaje+header->semana[0].internacional);
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
