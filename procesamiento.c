#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "aeropADT.h"
#include "movsADT.h"
#include "procesamiento.h"

#define REG 0
#define NO_REG 1
#define PRIV 2

//podriamos tener un: 
#define DELIMIT ';'
#define COTA 400
//clases de vuelos:
#define CABOT 20
#define INTER 21
#define NA 22  //se usa para todo aquella informacion que no tomamos en cuenta. 
			   //no solo para vuelos N/A.







/*
** lo que hace es a partir de la linea que sacamos del archivo, va hasta el campo n y lo que esta ahi
** lo copia en el string destino.
** va a avanzar en funcion del delimitador de campo (delim), el cual en este caso es ';' 
** file: indica de que archivo se esta obteniendo el campo (aeropuertos.csv o movimientos.csv)
*/

void obtenerCampo(char * linea, int n, char delim, char * file, char  destino[]){  //n es el numero de campo

/* Se supone que es un archivo oficial, y que las estructuras de cada campo coinciden con la
** reglamentaria (por ejemplo, los codigos OACI del archivo de movimientos tienen 4 caracteres).
** Sin embargo, luego de varias pruebas, notamos que hay casos en los que no se cumple.
** Ya que son datos oficiales, y "respetan las reglas" tomamos cada campo con su respectiva cantidad maxima de caracteres
** si tiene mas, se corta y se toman los primeros m (m = cantidad de caracteres segun reglamento).
**
** stop indica cuantos caracteres tiene el campo.
*/
	int stop;

if (n == OACI_ORIGEN || n == OACI_DESTINO || n == OACI_AEROP) 
	 stop = CARS_OACI;  
else if(n == FECHA)
	 stop = CARS_FECHA;  
else if(n == CLASE)
	 stop = CARS_CLASE;  
else if(n == CLASIFICACION)
	 stop = CARS_CLASIF;   
else if(n == TDM && strcmp(file, "movimientos.csv") == 0)  //esto es porque TDM y DENOM tienen el mismo numero de campo
	 stop = CARS_TDM;   
else if(n == DENOM)
	stop = CARS_DENOM;  



	



//////////////////////////
	int i, j, cantDelim = 0;
	n -= 1; //porque no empieza con ';'

	for(i = 0; linea[i] != 0 && cantDelim < n; i++){
		if(linea[i] == delim){
			cantDelim++;
		}
	}
	for(j = 0; linea[i] != 0 && linea[i] != delim && j < stop; i++, j++){
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
	
	sscanf(fecha, "%2d/%2d/%4d", d, m, a);
}


int queDiaEs(char * fecha){                     //metodo de Sakamoto   
	int d, m, a;
	obtenerFecha(fecha, &d, &m, &a);
	 int t[] = {0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4};  //Codigo de los meses
        a -= m < 3;
        return (a + a/4 - a/100 + a/400 + t[m-1] + d) % 7;
}

//------------------------Procesamos aeropuertos----------------

int procesarAerops(char * file, aeropADT aerops[LETRAS]){ //inicialmente estara vacio. BASICAMENTE, LLENA LA LISTA DE AEROPS. (PROBARLA)

//podriamos ver que onda los errores
//--------------abrimos el archivo: aeropuertos.csv------------------

	FILE * fAerops;

	fAerops = fopen(file, "r");
		if(fAerops == NULL){//algo fallo a la hora de abrir el archivo
			printf("No se pudo abrir el archivo\n");
			return 1;
		}


//------------funciones para procesar aeropuertos-------
//osea todo lo que es agregar movimientos, comparar OACI, etc
	
	char linea[COTA];
	char oaci[5];		//dimension: cantidad de caracteres posible + el 0
	char denomin[71];


	fgets(linea, COTA, fAerops); //ignoro la primer linea (porque me dice como esta ordenado nomas)

	while(fgets(linea, COTA, fAerops)){
		obtenerCampo(linea, OACI_AEROP, DELIMIT, file,oaci); //me deja en oaci[], el oaci
		obtenerCampo(linea, DENOM, DELIMIT, file, denomin); //me deja en denomin, la denominacion del aeropuerto
	
		if(isalpha(oaci[0])){
		
		addAerop(aerops, oaci, denomin); //esta funcion ya me lo agrega ordenado.
		}
	}
	fclose(fAerops);
	return 0;
}


/*
** Funcion para que una vez obtenida la clase, nos diga cual es.
*/

int queClase( char * claseVuelo){         
	if(strcmp(claseVuelo, "Cabotaje") == 0){
		return CABOT;
	}else if(strcmp(claseVuelo, "Internacional") == 0){
		return INTER;
	}else{
		return NA;
	}
}

/*
** Funcion que una vez obtenida la clasificacon, nos diga cual es.
*/

int queClasificacion( char * clasifVuelo){
	if(strcmp(clasifVuelo, "Regular") == 0){
		return REG;
	}else if(strcmp(clasifVuelo, "No Regular") == 0){
		return NO_REG;
	}else if(strncmp(clasifVuelo, "Vuelo Privado", 13) == 0){
		return PRIV;
	}else{ 								//por si alguno no tiene nada o algo que no nos sirve:
		return NA; //siendo NA un sinonimo de basura.
	}
}




//---------------Procesamos movimientos---------------------

int procesarMovs(char * file, aeropADT aerops[LETRAS], tMovsADT movimientos){

//----------------------abrimos el archivo: movimientos.csv------------

	FILE * fMovs;

	fMovs = fopen(file, "r");   
		if(fMovs == NULL){//algo fallo a la hora de abrir el archivo
			printf("No se pudo abrir el archivo\n");
			return 1;
		}

//----------------Funciones para procesar movimientos-----------
//todo lo que es agregar fechas, cabotajes regulares, etc...

	char  linea[COTA];     
	char  oaciOrig[5];	//dimensiones: representan la cantidad maxima de caracteres que pueden poseer + el 0 final
	char  oaciDest[5];	
	char  fecha[11];
	char  claseVuelo[40];
	char  clasifVuelo[15];
	char tipoDeMovimiento[12];
	int dia, clase, clasificacion;

	fgets(linea, COTA, fMovs); //descarto la primer linea

	while(fgets(linea, COTA, fMovs)){
		obtenerCampo(linea, OACI_ORIGEN,DELIMIT, file, oaciOrig);
		obtenerCampo(linea, OACI_DESTINO,DELIMIT,  file, oaciDest);
		obtenerCampo(linea, FECHA, DELIMIT, file, fecha);
		obtenerCampo(linea, CLASE, DELIMIT, file, claseVuelo);
		obtenerCampo(linea, CLASIFICACION, DELIMIT, file, clasifVuelo);
		obtenerCampo(linea, TDM, DELIMIT, file,tipoDeMovimiento);
		
		
	



	if(isalpha(oaciOrig[0]) && isalpha(oaciDest[0]) && isalpha(claseVuelo[0]) && isalpha(clasifVuelo[0])){

	//Agrega los movimientos a los OACI que estén en el vector
	
	if(strcmp(tipoDeMovimiento,"Aterrizaje") == 0)
			agregarMov(aerops,oaciDest);
		else if(strcmp(tipoDeMovimiento,"Despegue") == 0)
			agregarMov(aerops,oaciOrig);
	}
		dia = queDiaEs(fecha);  //supuestamente va del 0 al 6...

		clasificacion = queClase(clasifVuelo);     //los switchee            
		clase = queClasificacion(claseVuelo);	   //CAMBIAR NOMBRES URGENTE!
		
		aumentaClasifVuelo(movimientos, clase, clasificacion); 
		aumentaDia(movimientos, clasificacion, dia);  
	}
	fclose(fMovs);
	return 0;

}
