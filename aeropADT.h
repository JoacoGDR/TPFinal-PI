#ifndef _AEROPUERTOS_ADT_
#define _AEROPUERTOS_ADT_
#define LETRAS 'Z'-'A' + 1
typedef struct aeropCDT * aeropADT;
typedef struct listaCDT * listaADT;
aeropADT * nuevaLista(void);
void addAerop(aeropADT lista[LETRAS], char * oaci, char* denom);
void ordenaCantMovs(aeropADT lista[LETRAS]);
void freeLista(aeropADT lista[LETRAS]);


#endif
