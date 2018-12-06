#ifndef _AEROPUERTOS_ADT_
#define _AEROPUERTOS_ADT_
#define LETRAS 'Z'-'A' + 1


typedef struct aeropCDT * aeropADT;
typedef struct vecList * vec;   


/* Crea un vector de 27 listas inicializadas en NULL
 * de aeropuertos. Hay 27 letras en el abecedario inglés
 */
vec  nuevaLista(void);

/* Agrega un aeropuerto al vector de listas
 * respetando su orden alfabético. 
 */
void addAerop(vec lista, char * oaci, char* denom);

/* Verifica si existe el aeropuerto
 * en el caso de que exista, le suma un movimiento.
 */
int agregarMov(vec list, char oaci[5]);

/* Retorna una lista con los aeropuertos ordenados
 * con sus movimientos descendientemente. 
 */
aeropADT ordenaCantMovs(vec lista);

void freeListaOrdenada(aeropADT first);

void query1(aeropADT lista);


#endif
