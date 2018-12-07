Trabajo Practico Final. Programacion Imperativa. Segundo Cuatrimestre 2018.

Alumnos:

	Preusche, Santiago
	Garcia del Rio, Joaquin
	Digon, Lucia

Instrucciones para Compilar y Ejecutar el Programa:

- Crear una carpeta que contenga los archivos entregados ("aeropsADT.c", "aeropADT.h", "movsADT.c", "movsADT.h", "procesamiento.c", 
  "procesamiento.h"). Esta carpeta tambien debe contener los archivos: "aeropuertos.csv" y "movimientos.csv".

- Abrir la terminal (y estando en dicha carpeta), escribir:
	gcc *.c -o NOMBRE -Wall -std=c99 -pedantic -fsanitize=address
NOMBRE es el nombre que tendra el ejecutable, se puede elegir el nombre que uno quiera.

- Para ejecutar el programa, escribir en la terminal:
	./NOMBRE aeropuertos.csv movimientos.csv

- Terminada la ejecucion, apareceran 3 archivos .csv en la carpeta: "movimientos_aeropuerto.csv" "dia_semana.csv" "composicion.csv"
que corresponden a los querys 1, 2 y 3 respectivamente.
