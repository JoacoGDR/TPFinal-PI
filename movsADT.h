#ifndef _MOVIMIENTOS_ADT_
#define _MOVIMIENTOS_ADT_

typedef struct tMovsCDT * tMovsADT;

//Crea un nuevo header en la memoria. 
tMovsADT newMov(void);

// Aumenta los movimientos al día insertado en la respectiva clase.
void aumentaDia(tMovsADT movs, int clase, int dia);

//Aumenta los movimientos de la clase en su respectiva clasificación.
void aumentaClasifVuelo(tMovsCDT * movs, int clase, int clasif);


//Realizan los Querys 2 y 3 respectivamente
void query2(tMovsCDT * header);
void query3(tMovsCDT * header);

#endif
