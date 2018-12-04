#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "aeropADT.h"
#include "movsADT.h"


//podriamos tener un: 
#define DELIMIT ';'

// para aeropuertos.csv
#define OACI_AEROP 2
#define DENOM 5

//para movimientos.csv
#define OACI_ORIGEN 6
#define OACI_DESTINO 7                 //indican la posicion del respectivo campo en la linea.
#define FECHA 1
#define CLASE 3
#define CLASIFICACION 4 

//o bien hacer un enum ya que tenemos 1,2,3,4,5,6,7


/*
** lo que hace es a partir de la linea que sacamos del archivo, va hasta el campo n y lo que esta ahi
** lo copia en el string destino.
** va a avanzar en funcion del delimitador de campo (delim), el cual en este caso es ';' 
*/

void obtenerCampo(char * linea, int n, char delim, char * destino){  //n seria alguno de esos #defines
	int i, j, cantDelim = 0;
	n -= 1; //porque no empieza con ';'

	for(i = 0; linea[i] != 0 && cantDelim < n; i++){
		if(linea[i] == delim){
			cantDelim++;
		}
	}
	for(j = 0; linea[i] != 0 && linea[i] != delim; i++, j++){
		destino[j] = linea[i];
	}
	destino[j] = 0;
	return;
}	

//ahora bien. Se que estan todos seguidos basicamente, entonces no esta muy bueno que si yo pido el oaci, 
//y despues pido denominacion tenga que volver a recorrer la linea desde el principio.
//podria agregarle de alguna forma, un lugar desde el cual empezar, tipo el ultimo ';' en el que quedo por asi decirlo



/*
** funcion para obtener el dia de la semana en el que cae la fecha dada
*/
void obtenerFecha(char * fecha, int * d, int * m, int * a){
	
	sscanf(fecha, "%2d/%2d/%2d", &d, %m, %a);
}


int queDiaEs(char * fecha){                     //metodo de Sakamoto   
	int d, m, a;
	obtenerFecha(fecha, &d, &m, &a);
	static int t[] = {0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4};
        y -= m < 3;
        return (y + y/4 - y/100 + y/400 + t[m-1] + d) % 7;
}

//------------------------Procesamos aeropuertos----------------//

int procesarAerops(char * file, listADT * aerops){ //inicialmente estara vacio. BASICAMENTE, LLENA LA LISTA DE AEROPS.

//podriamos ver que onda los errores
//--------------abrimos el archivo: aeropuertos.csv------------------//

FILE * fAerops;

fAerops = fopen(file, "r");
	if(fAerops == NULL){//algo fallo a la hora de abrir el archivo
		printf("No se pudo abrir el archivo\n");
		return 1;
	}


//------------funciones para procesar aeropuertos-------//
//osea todo lo que es agregar movimientos, comparar OACI, etc
	
	char * linea;
	char * oaci;
	char * denomin;

	fgets(linea, 300, fAerops); //ignoro la primer linea (porque me dice como esta ordenado nomas)

	while(fgets(linea, 300, fAerops)){
		obtenerCampo(linea, OACI_AEROP, DELIMIT, oaci); //me deja en oaci[], el oaci
		obtenerCampo(linea, DENOM, DELIMIT, denomin); //me deja en denomin, la denominacion del aeropuerto

		addAerop(aerops, oaci, denomin); //esta funcion ya me lo agrega ordenado.
	}
	fclose(fAerops);
	return 0;
}




//---------------Procesamos movimientos---------------------//

int procesarMovs(char * file,vecAerops aerops, tMovsCDT movimientos){

//----------------------abrimos el archivo: movimientos.csv------------//

FILE * fMovs;

fMovs = fopen(file, "r");   //NOSE SI PUEDO PONER LO DE argv aca...mmmm...
	if(fMovs == NULL){//algo fallo a la hora de abrir el archivo
		printf("No se pudo abrir el archivo\n");
		return 1;
	}

//----------------Funciones para procesar movimientos-----------//
//todo lo que es agregar fechas, cabotajes regulares, etc...

	char * linea;
	char * oaciOrig;
	char * oaciDest;
	char * fecha;
	char * claseVuelo;
	char * clasifVuelo;
	int dia, clase;

	fgets(linea, 300, fMovs); //descarto la primer linea

	while(fgets(linea, 300, fMovs)){
		obtenerCampo(linea, OACI_ORIGEN, DELIMIT, oaciOrig);
		obtenerCampo(linea, OACI_DESTINO, DELIMIT, oaciDest);
		obtenerCampo(linea, FECHA, DELIMIT, fecha);
		obtenerCampo(linea, CLASE, DELIMIT, claseVuelo);
		obtenerCampo(linea, CLASIFICACION, DELIMIT, clasifVuelo);

		dia = queDiaEs(fecha);

		queClase(&clase);                 //HACER FUNCION, HACE STRCMP CON "cabotaje" y con "internacional"
										  //Y LE DA EL VALOR CORRESPONDIENTE A *clase.

		aumentaClasifVuelo(clase, clasificacionVuelo(clasifVuelo)); //clasificacionVuelo() retorna un string
		aumentaDia(movimientos, clase, dia);
	}

}
