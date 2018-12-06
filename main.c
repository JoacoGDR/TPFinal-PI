#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "aeropADT.h"
#include "movsADT.h"
#include "procesamiento.h"



int main(int argc, char *argv[]){
	
	//Se verifica que se pase la cantidad de archivos correcta

	//if(strcmp(argv[1], "aeropuertos.csv") != 0 || strcmp(argv[2], "movimientos.csv") != 0){
	//	printf("Error: Se espera que el primer archivo sea aeropuertos.csv, y el segundo movimientos.csv\n");
	//	return 3;	
	//}
	

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
	vec aeroLista = nuevaLista();
	
	procesarAerops(file1, aeroLista);
	procesarMovs(file2, aeroLista, movis);
	
	aeropADT lista = ordenaCantMovs(aeroLista);
	
	query1(lista);

	freeListaOrdenada(lista);

	query2(movis);
	query3(movis);
	free(movis);
	
	return 0;
}
