#ifndef _AEROPUERTOS_ADT_
#define _AEROPUERTOS_ADT_
#define LETRAS 'Z'-'A' + 1


typedef struct aeropCDT * aeropADT;


/* Crea un vector de 27 listas inicializadas en NULL
 * de aeropuertos. Hay 27 letras en el abecedario inglés
 */
aeropADT * nuevaLista(void);

/* Agrega un aeropuerto al vector de listas
 * respetando su orden alfabético. 
 */
void addAerop(aeropADT lista[LETRAS], char * oaci, char* denom);

/* Verifica si existe el aeropuerto
 * en el caso de que exista, le suma un movimiento.
 */
int agregarMov(aeropADT list[LETRAS], char oaci[5]);

/* Retorna una lista con los aeropuertos ordenados
 * con sus movimientos descendientemente. 
 */
aeropADT ordenaCantMovs(aeropADT lista[LETRAS]);

void query1(aeropADT first);

#endif
