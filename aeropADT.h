#ifndef _AEROPUERTOS_ADT_
#define _AEROPUERTOS_ADT_
#define LETRAS 'Z'-'A' + 1


typedef struct aeropCDT * aeropADT;

aeropADT * nuevaLista(void);

void addAerop(aeropADT lista[LETRAS], char * oaci, char* denom);
int agregarMov(aeropADT list[LETRAS], char oaci[5]);

void ordenaCantMovs(aeropADT lista[LETRAS]);


#endif
