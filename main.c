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
		fprintf(destino, "%s;%ld;%ld;%ld\n", dias[i], header->semana[i].cabotaje, header->semana[i].internacional, header->semana[i].cabotaje + header->semana[i].internacional);
	}
	fprintf(destino, "%s;%ld;%ld;%ld\n", dias[0], header->semana[0].cabotaje, header->semana[0].internacional, header->semana[0].cabotaje + header->semana[0].internacional);
	fclose(destino);

}

void query3(tMovsCDT * l){
	FILE * destino;
	destino = fopen("composicion.csv","wt");
	fprintf(destino, "Cabotaje;Regular;%ld\n",l->cabotaje[0]);
	fprintf(destino, "Cabotaje;No Regular;%ld\n",l->cabotaje[1]);
	fprintf(destino, "Cabotaje;Vuelo Privado;%ld\n",l->cabotaje[2]);
	fprintf(destino, "Internacional;Regular;%ld\n",l->internacional[0]);
	fprintf(destino, "Internacional;No Regular;%ld\n",l->internacional[1]);
	fprintf(destino, "Internacional;Vuelo Privado;%ld\n",l->internacional[2]);
    fclose(destino);

}

int main(int argc, char *argv[]){
	
	if(argc > 3){
		printf("Error: Demasiados argumentos\n");
		return 1;
	}else if(argc < 3){
		printf("Error: Faltan argumentos\n");
		return 2;
	}
	
	char * file1 = argv[1];
	char * file2 = argv[2];
	
	
	tMovsADT movis = newMov();
	aeropADT aeroLista[LETRAS] = nuevaLista();
	
	procesarAerops(file1, aeroLista);
	procesarMovs(file2, aeroLista, movis);
	
	aeropADT lista = ordenaCantMovs(l);
	
	//aca deberiamos hacerle free a la lista
	query1(lista);
	query2(movis);
	query3(movis);
	
	free(movis);
	
	return 0;
}
