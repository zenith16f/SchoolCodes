#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include "logica.h"

void *multiplicacionFilaMatriz(void *paquete){
	//Obtener datos matriz
	PaqueteIndividual *paquete_hilo = (PaqueteIndividual *)paquete;
	MatrizData *data = paquete_hilo->datos_compartidos;
	int fila = paquete_hilo->id_logico;
	int i_hilo = fila + 1;
	//Presentacion
	printf("\nHilo %d: Hola soy el hilo %d con el id [%ld]\n", i_hilo,i_hilo,pthread_self());
	//Calculo de multiplicacion
	data->arr_results[fila]= multiplicacionLineal(data, fila);
	pthread_exit(NULL);
}
//Creacion de hilos
void manejoHilos(void *paquete){
	//HILOS	
	pthread_t ids[MAX_THREADS];
	PaqueteIndividual hilos_paquete[MAX_THREADS];
	MatrizData *data = (MatrizData *)paquete;

	//Funcion de hilos
	for(int i=0;i<MAX_THREADS;i++){
		hilos_paquete[i].id_logico = i;
		hilos_paquete[i].datos_compartidos = data;
		pthread_create(&ids[i], NULL, multiplicacionFilaMatriz,(void *)&hilos_paquete[i]);
	}

	for(int j=0;j<MAX_THREADS;j++){
		pthread_join(ids[j], NULL);
	}	
	sleep(1);
}


