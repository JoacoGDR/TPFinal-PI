#include <stdlib.h>
#include <stdio.h>
#include "aeropADT.h"
#include "movsADT.h"
#include "procesamiento.h"


void query1(aeropADT lista){   // Recibe la lista ordenada por movimientos
   
   FILE * destino;
   destino = fopen("a.csv", "wt");   // Va a crear este archivo y va a poner todo ahi
   
   fprintf(destino, "OACI;Denominacion;Cantidad de Movimientos\n");

   printList(lista, destino);
   freeListaOrdenada(lista);
   
   fclose(destino);
}

void query2(tMovsADT h){
	FILE * destino;
	destino = fopen("dia_semana.csv","wt");
		
	fprintf(destino, "Dia;Cabotaje;Internacionales;Total\n");
	printPorSemana(h, destino);
	
	fclose(destino);

}

void query3(tMovsADT l){
	FILE * destino;
	destino = fopen("composicion.csv","wt");
	
	
	fprintf(destino, "Clasificacion de Vuelo;Clase de Vuelo;Movimientos\n");
	printPorVuelo (l, destino);
	free (l);
	
    fclose(destino);

}

int main(int argc, char *argv[]){
	
	//Se verifica que se pase la cantidad de archivos correcta
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
	aeropADT * aeroLista = nuevaLista();
	
	procesarAerops(file1, aeroLista);
	procesarMovs(file2, aeroLista, movis);
	
	aeropADT lista = ordenaCantMovs(aeroLista);
	query1(lista);
	freeListaOrdenada(lista);//aca deberiamos hacerle free a la lista
	query2(movis);
	query3(movis);
	free(movis);
	
	return 0;
}
