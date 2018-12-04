#ifndef _AEROPUERTOS_ADT_
#define _AEROPUERTOS_ADT_
typedef struct aeropCDT * aeropADT;
typedef struct listaCDT * listaADT;

listaADT nuevaLista(void);
listaADT addAerop(listaADT lista, char * oaci, char* denom);
aeropADT ordenaCantMovs();
void freeLista(listaADT lista);


#endif