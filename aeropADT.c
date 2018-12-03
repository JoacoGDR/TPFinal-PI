#include "aeropuertos.h"
/* Los nodos serían los aeropuertos. En cada aeropuerto, se guardarian su oaci, 
 * su denominación y la cantidad de despegues y aterrizajes que ocurren en el aeropuerto.
 */
typedef struct aerop * Taerop;
struct aerop{
	char oaci[5];
	char * denom;
	int movs;
	Taerop tail;
};
/* habria que ver si hay que definir struct dia en el .h
 * (osea si hay una funcion que tenga que devolver un dia) no creo igual
 */
struct dia{
	int nacional;
	int internacional;
};
struct censoCDT{
	dia semana[7];
	int nacional[3];
	int internacional[3];
};
