#ifndef LOGICA_H
#define LOGICA_H

#define FILAS 3
#define COLUMNAS 9
#define MAX_THREADS 3

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

//Estructuras
typedef struct
{
    int matriz[FILAS][COLUMNAS];
    int arr_results[MAX_THREADS];
} MatrizData;

typedef struct 
{
    int id_logico;
    MatrizData *datos_compartidos;
} PaqueteIndividual;

//Matriz
void numeracion(int i,int j, int matriz[FILAS][COLUMNAS]);
void numeracionImpar(int i, int j, int matriz[FILAS][COLUMNAS]);
void numeracionPar(int i, int j, int matriz[FILAS][COLUMNAS]);
void llenarMatriz(int matriz[FILAS][COLUMNAS]);

//Hilos
void manejoHilos(void *paquete);
void *multiplicacionFilaMatriz(void *paquete);

//Operaciones
void mostrarLinea(int matriz[FILAS][COLUMNAS], int i);
void mostrarMatriz(int matriz[FILAS][COLUMNAS]);
void mostrarResultados(int matriz[MAX_THREADS]);
int multiplicacionLineal(MatrizData *data, int id_fila);

#endif 

