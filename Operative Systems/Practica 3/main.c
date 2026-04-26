/*
 * main.c - Proceso padre: comunicación entre procesos padre-hijos
 * Práctica 3 - Sistemas Operativos - ESCOM IPN
 * Equipo: Cuellar, Guzmán, Macías, Palomo - Grupo 4CV4
 *
 * Este programa:
 *   1. Crea un segmento de memoria compartida y coloca una matriz
 *   2. Crea un semáforo para sincronizar el acceso
 *   3. Muestra la matriz en pantalla
 *   4. Crea 3 procesos hijos (uno por fila)
 *   5. Cada hijo calcula la suma de su fila y la almacena en memoria
 *   6. El padre espera a que todos los hijos terminen
 *   7. El padre lee y muestra los resultados
 *   8. Libera los recursos IPC
 *
 * Compilación: make
 * Ejecución:   ./main
 */

#include "definitions.h"

int main(void)
{
    DatosCompartidos *datos;
    int shmid, sem_mutex;
    key_t llave_shm, llave_sem;
    pid_t pids[FILAS];
    int i, j, estado;

    /* Matriz Prubea de 3x5
    int matriz_inicial[FILAS][COLS] = {
        {  2,  4,  6,  8, 10},
        {  1,  3,  5,  7,  9},
        { 11, 22, 33, 44, 55}
    };
    */

    // Matriz Practica 3X8
    int matriz_inicial[FILAS][COLS] = {
        {1,2,3,4,5,6,7,8,9},
        {1,3,5,7,9,11,13,15,17},
        {2,4,6,8,10,12,14,16,18}
    };

    printf("==========================================\n");
    printf("  PRACTICA 3: Comunicacion entre procesos\n");
    printf("  padre-hijos con memoria compartida\n");
    printf("  y semaforos\n");
    printf("==========================================\n");
    printf("\n[Padre] Mi PID es: %d\n", getpid());

    /* ====== Crear archivos necesarios para ftok ====== */
    /* ftok necesita que los archivos existan */
    fclose(fopen(ARCHIVO_SHM, "w"));
    fclose(fopen(ARCHIVO_SEM, "w"));

    /* ====== Crear memoria compartida ====== */
    llave_shm = ftok(ARCHIVO_SHM, 'M');
    if (llave_shm == -1) {
        perror("Error en ftok para memoria compartida");
        exit(EXIT_FAILURE);
    }

    shmid = CrearMemoriaCompartida(llave_shm, sizeof(DatosCompartidos));
    if (shmid == -1) {
        exit(EXIT_FAILURE);
    }

    datos = (DatosCompartidos *)AdjuntarMemoria(shmid);
    if (datos == NULL) {
        exit(EXIT_FAILURE);
    }

    printf("[Padre] Memoria compartida creada (ID: %d, tamano: %lu bytes)\n",
           shmid, (unsigned long)sizeof(DatosCompartidos));

    /* ====== Crear semáforo ====== */
    llave_sem = ftok(ARCHIVO_SEM, 'S');
    if (llave_sem == -1) {
        perror("Error en ftok para semaforo");
        DesvincularMemoria(datos);
        EliminarMemoria(shmid);
        exit(EXIT_FAILURE);
    }

    sem_mutex = CrearSemaforo(llave_sem, 1);
    if (sem_mutex == -1) {
        DesvincularMemoria(datos);
        EliminarMemoria(shmid);
        exit(EXIT_FAILURE);
    }

    printf("[Padre] Semaforo creado (ID: %d, valor inicial: 1)\n", sem_mutex);

    /* ====== Colocar la matriz en memoria compartida ====== */
    for (i = 0; i < FILAS; i++) {
        for (j = 0; j < COLS; j++) {
            datos->matriz[i][j] = matriz_inicial[i][j];
        }
        datos->resultados[i] = 0;
    }
    datos->hijos_terminados = 0;

    /* ====== Mostrar la matriz ====== */
    printf("\n[Padre] Matriz colocada en memoria compartida:\n");
    printf("------------------------------------------\n");
    for (i = 0; i < FILAS; i++) {
        printf("  Fila %d: |", i + 1);
        for (j = 0; j < COLS; j++) {
            printf(" %3d |", datos->matriz[i][j]);
        }
        printf("\n");
    }
    printf("------------------------------------------\n");

    /* ====== Crear los 3 procesos hijos ====== */
    printf("\n[Padre] Creando %d procesos hijos...\n", FILAS);

    for (i = 0; i < FILAS; i++) {
        pids[i] = fork();

        if (pids[i] == -1) {
            perror("Error al crear proceso hijo");
            /* Limpiar recursos antes de salir */
            DesvincularMemoria(datos);
            EliminarMemoria(shmid);
            EliminarSemaforo(sem_mutex);
            exit(EXIT_FAILURE);
        }

        if (pids[i] == 0) {
            /* Código del proceso hijo */
            ProcesoHijo(shmid, sem_mutex, i);
            exit(EXIT_SUCCESS);
        }

        printf("[Padre] Hijo %d creado con PID: %d (asignado fila %d)\n",
               i + 1, pids[i], i + 1);
    }

    /* ====== Esperar a que todos los hijos terminen ====== */
    printf("\n[Padre] Esperando a que los %d hijos terminen...\n", FILAS);

    for (i = 0; i < FILAS; i++) {
        waitpid(pids[i], &estado, 0);
        if (WIFEXITED(estado)) {
            printf("[Padre] Hijo %d (PID: %d) termino con estado: %d\n",
                   i + 1, pids[i], WEXITSTATUS(estado));
        }
    }

    /* ====== Leer y mostrar los resultados ====== */
    printf("\n==========================================\n");
    printf("  RESULTADOS\n");
    printf("==========================================\n");
    printf("[Padre] Todos los hijos han terminado\n");
    printf("[Padre] Leyendo resultados de la memoria compartida:\n\n");

    for (i = 0; i < FILAS; i++) {
        printf("  Fila %d: |", i + 1);
        for (j = 0; j < COLS; j++) {
            printf(" %3d |", datos->matriz[i][j]);
        }
        printf(" => Suma = %d\n", datos->resultados[i]);
    }

    printf("\n[Padre] Total de hijos que procesaron: %d\n",
           datos->hijos_terminados);

    /* ====== Liberar recursos IPC ====== */
    printf("\n[Padre] Liberando recursos IPC...\n");
    DesvincularMemoria(datos);
    EliminarMemoria(shmid);
    EliminarSemaforo(sem_mutex);

    /* Limpiar archivos de ftok */
    remove(ARCHIVO_SHM);
    remove(ARCHIVO_SEM);

    printf("[Padre] Recursos liberados. Programa finalizado.\n");
    printf("==========================================\n");

    return 0;
}
