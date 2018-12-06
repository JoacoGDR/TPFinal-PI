#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "aeropADT.h"
#include "movsADT.h"
#include "procesamiento.h"

#define REG 0
#define NO_REG 1
#define PRIV 2

//podriamos tener un: 
#define DELIMIT ';'
#define COTA 300
//clases de vuelos:
#define CABOT 20
#define INTER 21
#define NA 22  //se usa para todo aquella informacion que no tomamos en cuenta. 
			   //no solo para vuelos N/A.

//clasificacion de vuelos estan en el mov adt.h


// para aeropuertos
#define OACI_AEROP 2
#define DENOM 5

//para movimientos
#define OACI_ORIGEN 6
#define OACI_DESTINO 7                 //indican la posicion del respectivo campo en la linea.
#define FECHA 1
#define CLASE 3
#define CLASIFICACION 4 
#define TDM 5

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
	
	sscanf(fecha, "%2d/%2d/%2d", m, d, a);
}


int queDiaEs(char * fecha){                     //metodo de Sakamoto   
	int d, m, y;
	obtenerFecha(fecha, &d, &m, &y);
	static int t[] = {0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4};
        y -= m < 3;
        return (y + y/4 - y/100 + y/400 + t[m-1] + d) % 7;
}

//------------------------Procesamos aeropuertos----------------//

int procesarAerops(char * file, aeropADT aerops[LETRAS]){ //inicialmente estara vacio. BASICAMENTE, LLENA LA LISTA DE AEROPS. (PROBARLA)

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
	
	char linea[COTA];
	char oaci[5];
	char denomin[70];

	fgets(linea, COTA, fAerops); //ignoro la primer linea (porque me dice como esta ordenado nomas)

	while(fgets(linea, COTA, fAerops)){
		obtenerCampo(linea, OACI_AEROP, DELIMIT, oaci); //me deja en oaci[], el oaci
		obtenerCampo(linea, DENOM, DELIMIT, denomin); //me deja en denomin, la denominacion del aeropuerto

		addAerop(aerops, oaci, denomin); //esta funcion ya me lo agrega ordenado.
	}
	fclose(fAerops);
	return 0;
}


/*
** Funcion para que una vez obtenida la clase, nos diga cual es.
*/

void queClase(int * clase, char * claseVuelo){         
	if(strcmp(claseVuelo, "Cabotaje") == 0){
		*clase = CABOT;
	}else if(strcmp(claseVuelo, "Internacional") == 0){
		*clase = INTER;
	}else{
		*clase = NA;
	}
}

/*
** Funcion que una vez obtenida la clasificacon, nos diga cual es.
*/

void queClasificacion(int * clasificacion, char * clasifVuelo){
	if(strcmp(clasifVuelo, "Regular") == 0){
		*clasificacion = REG;
	}else if(strcmp(clasifVuelo, "No Regular") == 0){
		*clasificacion = NO_REG;
	}else if(strcmp(clasifVuelo, "Vuelo Privado con Matrícula Nacional") == 0 || strcmp(clasifVuelo, "Vuelo Privado con Matrícula Extranjera") == 0){
		*clasificacion = PRIV;
	}else{ //por si alguno no tiene nada o algo que no nos sirve:
		*clasificacion = NA; //siendo NA un sinonimo de basura.
	}
}




//---------------Procesamos movimientos---------------------//

int procesarMovs(char * file, aeropADT aerops[LETRAS], tMovsADT movimientos){

//----------------------abrimos el archivo: movimientos.csv------------//

	FILE * fMovs;

	fMovs = fopen(file, "r");   
		if(fMovs == NULL){//algo fallo a la hora de abrir el archivo
			printf("No se pudo abrir el archivo\n");
			return 1;
		}

//----------------Funciones para procesar movimientos-----------//
//todo lo que es agregar fechas, cabotajes regulares, etc...

	char  linea[COTA];     //o bien se podrian hacer tipoOaci, tipoFecha etc. y guardarlos en un .h
	char  oaciOrig[5];
	char  oaciDest[5];
	char  fecha[11];
	char  claseVuelo[15];
	char  clasifVuelo[11];
	char tipoDeMovimiento[11];
	int dia, clase, clasificacion;

	fgets(linea, COTA, fMovs); //descarto la primer linea

	while(fgets(linea, COTA, fMovs)){
		obtenerCampo(linea, OACI_ORIGEN, DELIMIT, oaciOrig);
		obtenerCampo(linea, OACI_DESTINO, DELIMIT, oaciDest);
		obtenerCampo(linea, FECHA, DELIMIT, fecha);
		obtenerCampo(linea, CLASE, DELIMIT, claseVuelo);
		obtenerCampo(linea, CLASIFICACION, DELIMIT, clasifVuelo);
		obtenerCampo(linea, TDM, DELIMIT, tipoDeMovimiento);
		//Agrega los movimientos a los OACI que estén en el vector
		if(strcmp(tipoDeMovimiento,"Aterrizaje"))
			agregarMov(aerops,oaciDest);
		else if(strcmp(tipoDeMovimiento,"Despegue"))
			agregarMov(aerops,oaciOrig);

		dia = queDiaEs(fecha);

		queClase(&clase, claseVuelo);                
		queClasificacion(&clasificacion, clasifVuelo);

		aumentaClasifVuelo(movimientos, clase, clasificacion); 
		aumentaDia(movimientos, clase, dia);  //estas dos son fcs de movsADT
	}
	fclose(fMovs);
	return 0;

}
