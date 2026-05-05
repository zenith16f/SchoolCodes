#include "logica.h"

void mostrarLinea(int matriz[FILAS][COLUMNAS], int i){
	for(int j=0;j<COLUMNAS;j++){
		printf("[%d]", matriz[i][j]);
	}
}
void mostrarResultados(int matriz[MAX_THREADS]){
	for(int i=0; i<MAX_THREADS; i++){
		printf("\nResultado de hilo %d: %d\n", (i+1), matriz[i]);
	}
}

void mostrarMatriz(int matriz[FILAS][COLUMNAS]){
	for(int i=0;i<FILAS;i++){
		for(int j=0;j<COLUMNAS;j++){
			printf("[%2d]", matriz[i][j]);
		}
		printf("\n");
	}
}

int multiplicacionLineal(MatrizData *data, int id_fila){
	int temp_result = data->matriz[id_fila][0];
	int hilo_actual = (id_fila)+1;
    printf("\nHilo %d: Trabajando con la fila: ", hilo_actual);
    mostrarLinea(data->matriz, id_fila);
    printf("\n");
	for(int i=1; i<COLUMNAS; i++){
		printf("\nHilo %d:", hilo_actual);
		printf(" Multiplicacion de %d con %d", temp_result, data->matriz[id_fila][i]);
		temp_result = temp_result * data->matriz[id_fila][i];
		printf(", resultado obtenido: %d\n", temp_result);
		sleep(1);
	}
	printf("\nHilo %d: He terminado con la fila, el resultado que obtuve fue %d\n", hilo_actual, temp_result);
	return temp_result;
}