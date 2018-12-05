#include "movsADT.h"
#include "aeropADT.h"

#ifndef _PROCESAMIENTO_ADT_
#define _PROCESAMIENTO_ADT_


// Delimitador:
#define DELIMIT ';'

//Posiciones de los campos dentro de cada linea del archivo:

//Para aeropuertos.csv
#define OACI_AEROP 2
#define DENOM 5

//Para movimientos.csv
#define OACI_ORIGEN 6
#define OACI_DESTINO 7
#define FECHA 1
#define CLASE 3
#define CLASIFICACION 4 

/*
** Recorre la linea hasta el campo deseado, y luego lo copia en 'destino'.
** Cada campo esta delimitado por un delimitador 'delim'.
*/

void obtenerCampo(char * linea, int campo, char delim, char * destino);

/*
** Dada una fecha, deja en cada parametro (m, d, a) el mes, el dia y el anio respectivamente
*/

void obtenerFecha(char * fecha, int * d, int * m, int * a);

/*
** Dada una fecha, retorna un numero del 0 al 6 que representa el dia de la semana
** en la que cayo esa fecha.
** 
** El 0 indica que es el dia Domingo, el 1 Lunes, el 2 Martes...
**
** Esto se logra con el metodo de Sakamoto (Fuente: https://en.wikipedia.org/wiki/Determination_of_the_day_of_the_week#Sakamoto's_methods)
*/

int queDiaEs(char * fecha);


/*
** Recibe un string que contiene el nombre del archivo del cual tomara la informacion
** y un vector de estructuras de aeropuertos. El vector esta ordenado alfabeticamente
** (cada posicion corresponde a la primer letra de cada OACI de cada aeropuerto).
** 
** Sirve para procesar la informacion del archivo de aeropuertos.
** 
** Agrega al vector de aeropuertos cada aeropuerto uno de los aeropuertos que aparecen en el
** archivo de aeropuertos (agrega solo aquellos que tienen un codigo OACI, ya que en el archivo
** de movimientos, solo aparecen los movimientos de aquellos aeropuertos que tienen un codigo OACI).
*/

int procesarAerops(char * file, aeropADT aerops[LETRAS]);


/*
** Una vez obtenido el campo correspondiente a la clase de vuelo ('claseVuelo'), deja en el parametro E/S 'clase'
** un valor que representa dicha clase.
*/

void queClase(int * clase, char * claseVuelo);

/*
** Una vez obtenido el campo correspondiente a la clasificacion del vuelo ('clasifVuelo'), deja en el parametro E/S
** 'casificacion' un valor que representa dicha clasificacion.
*/

void queClasificacion(int * clasificacion, char * clasifVuelo);

/*
** Recibe un string que contiene el nombre del archivo del cual tomara la informacion,
** un vector de estructuras de aeropuertos y un puntero a una estructura de tipo Movimiento.
** 
** Sirve para procesar la informacion del archivo de movimientos.
**
** Obtiene del archivo aquellos campos que son de utilidad para luego agregar los movimientos,
** ya sea al vector de aeropuertos o a la estructura de tipos de movimientos.
*/

int procesarMovs(char * file, aeropADT aerops[LETRAS], tMovsADT movimientos);




#endif
