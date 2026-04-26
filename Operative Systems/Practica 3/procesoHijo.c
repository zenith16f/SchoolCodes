/*
 * procesoHijo.c - Lógica del proceso hijo
 * Práctica 3 - Sistemas Operativos - ESCOM IPN
 *
 * Cada proceso hijo:
 *   1. Se presenta con su PID y el PID de su padre
 *   2. Accede a la memoria compartida protegido por el semáforo
 *   3. Lee los datos de la fila asignada
 *   4. Calcula la suma de los elementos de su fila
 *   5. Muestra en pantalla los datos procesados y el resultado
 *   6. Escribe el resultado en la memoria compartida
 *   7. Incrementa el contador de hijos terminados
 */

#include "definitions.h"

void ProcesoHijo(int shmid, int sem_mutex, int fila)
{
    DatosCompartidos *datos;
    int suma, j;

    /* Adjuntar memoria compartida en el proceso hijo */
    datos = (DatosCompartidos *)AdjuntarMemoria(shmid);
    if (datos == NULL) {
        exit(EXIT_FAILURE);
    }

    /* Presentación del proceso hijo */
    printf("\n[Hijo %d] Hola, soy el proceso hijo para la fila %d\n",
           fila + 1, fila + 1);
    printf("[Hijo %d] Mi PID es: %d\n", fila + 1, getpid());
    printf("[Hijo %d] El PID de mi padre es: %d\n", fila + 1, getppid());

    /* ======== SECCIÓN CRÍTICA: lectura de la matriz ======== */
    SemaforoDown(sem_mutex);

    printf("\n[Hijo %d] Entrando a la seccion critica para leer fila %d\n",
           fila + 1, fila + 1);

    /* Leer y mostrar los datos de la fila asignada */
    printf("[Hijo %d] Datos de la fila %d: ", fila + 1, fila + 1);
    suma = 0;
    for (j = 0; j < COLS; j++) {
        printf("%d ", datos->matriz[fila][j]);
        suma += datos->matriz[fila][j];
    }
    printf("\n");

    /* Mostrar el resultado de la suma */
    printf("[Hijo %d] Suma de la fila %d = %d\n", fila + 1, fila + 1, suma);

    /* Escribir el resultado en la memoria compartida */
    datos->resultados[fila] = suma;
    printf("[Hijo %d] Resultado almacenado en memoria compartida\n",
           fila + 1);

    /* Incrementar contador de hijos terminados */
    datos->hijos_terminados++;
    printf("[Hijo %d] Hijos terminados hasta ahora: %d de %d\n",
           fila + 1, datos->hijos_terminados, FILAS);

    printf("[Hijo %d] Saliendo de la seccion critica\n", fila + 1);

    SemaforoUp(sem_mutex);
    /* ======== FIN SECCIÓN CRÍTICA ======== */

    /* Desvincular memoria compartida del hijo */
    DesvincularMemoria(datos);

    printf("[Hijo %d] Proceso hijo finalizado (PID: %d)\n\n",
           fila + 1, getpid());
}
