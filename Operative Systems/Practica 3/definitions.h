/*
 * practica3.h - Definiciones para comunicación entre procesos padre-hijos
 */

#ifndef DEFINITIONS
#define DEFINITIONS

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/wait.h>
#include <string.h>

#define FILAS    3
#define COLS     9
#define PERMISOS 0644

#define ARCHIVO_SHM "archivo_shm"
#define ARCHIVO_SEM "archivo_sem"

typedef struct {
    int matriz[FILAS][COLS];
    int resultados[FILAS];
    int hijos_terminados;
} DatosCompartidos;

/* semaforo.c */
int  CrearSemaforo(key_t llave, int valor_inicial);
void SemaforoDown(int semid);
void SemaforoUp(int semid);
void EliminarSemaforo(int semid);

/* memoria.c */
int   CrearMemoriaCompartida(key_t llave, size_t tamano);
void *AdjuntarMemoria(int shmid);
void  DesvincularMemoria(void *ptr);
void  EliminarMemoria(int shmid);

/* proceso_hijo.c */
void ProcesoHijo(int shmid, int sem_mutex, int fila);

#endif
