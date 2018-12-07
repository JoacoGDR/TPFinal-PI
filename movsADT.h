#ifndef _MOVIMIENTOS_ADT_
#define _MOVIMIENTOS_ADT_

typedef struct tMovsCDT * tMovsADT;

//Crea un nuevo header en la memoria. 
tMovsADT newMov(void);

// Aumenta los movimientos al día insertado en la respectiva clase.
void aumentaDia(tMovsADT movs, int clase, int dia);

//Aumenta los movimientos de la clase en su respectiva clasificación.
void aumentaClasifVuelo(tMovsADT movs, int clase, int clasif);

//imprime a cantidad de movimientos por dia de semana en el archivo de destino
void printPorSemana (tMovsADT h, FILE * destino);

//imprime  la cantidad de movimientos segun la clase de vuelo
void printPorVuelo (tMovsADT l , FILE * destino);



#endif
