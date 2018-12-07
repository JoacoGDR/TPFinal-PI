#include <stdlib.h>
#include <stdio.h>
#include "aeropADT.h"
#include "movsADT.h"
#include "procesamiento.h"



int main (int argc, char *argv[])
{
	//Se verifica que se pase la cantidad de archivos correcta
	if(argc > 3)
	{
		fprintf(stderr, "Error: Demasiados argumentos\n");
		return 1;
	}
	else if(argc < 3)
	{
		fprintf(stderr, "Error: Faltan argumentos\n");
		return 2;
	}
	
	char * file1 = "aeropuertos.csv";
	char * file2 = "movimientos.csv";
	
	
	tMovsADT movis = newMov();
	aeropADT * aeroLista = nuevoVecLis();
	
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
