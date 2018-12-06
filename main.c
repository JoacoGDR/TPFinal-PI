#include <stdlib.h>
#include <stdio.h>
#include "aeropADT.h"
#include "movsADT.h"
#include "procesamiento.h"



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
