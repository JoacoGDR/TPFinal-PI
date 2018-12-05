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
		fprintf(destino, "%s;%s;%ld \n", aux->oaci, aux->denom, aux->cantMov);
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
		fprintf(destino, "%s;%d;%d;%d\n", dias[i], header->semana[i].cabotaje, header->semana[i].internacional, header->semana[i].cabotaje + header->semana[i].internacional);
	}
	fprintf(destino, "%s;%d;%d;%d\n", dias[0], header->semana[0].cabotaje, header->semana[0].internacional, header->semana[0].cabotaje + header->semana[0].internacional);
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
	tMovsADT movis = calloc(sizeof(tMovsCDT));
	aeropADT aeroLista[LETRAS] = nuevaLista();
	procesarAerops("aeropuertos.csv",aeroLista);
	procesarMovs("movimientos.csv",aeroLista,movis);
	aeropADT l = ordenaCantMovs(l);
	query1(l);
	query2(l);
	query3(l);
	return 0;
}
