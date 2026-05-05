#include <stdio.h>
#include <stdlib.h>
#include "logica.h"

int main(){
	MatrizData data;
	llenarMatriz(data.matriz);
	printf("Hilo Padre: \nTrabajar con la siguiente matriz\n\n");
	mostrarMatriz(data.matriz);
	manejoHilos((void *)&data);
	printf("\nHilo Padre: Resultados Obtenidos\n\n");
	mostrarResultados(data.arr_results);
	return 0;
}
