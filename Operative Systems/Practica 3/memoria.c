/*
 * memoria.c - Operaciones sobre memoria compartida System V
 */

#include "definitions.h"

/*
 * CrearMemoriaCompartida - Crea o accede a un segmento de memoria compartida
 * @llave:  clave IPC generada con ftok
 * @tamano: tamaño en bytes del segmento solicitado
 * Retorna: identificador del segmento, o -1 en error
 */
int CrearMemoriaCompartida(key_t llave, size_t tamano)
{
    int shmid;

    shmid = shmget(llave, tamano, IPC_CREAT | PERMISOS);
    if (shmid == -1) {
        perror("Error al crear memoria compartida");
        return -1;
    }

    return shmid;
}

/*
 * AdjuntarMemoria - Adjunta el segmento de memoria compartida al proceso
 * @shmid: identificador del segmento
 * Retorna: puntero al inicio del segmento, o NULL en error
 */
void *AdjuntarMemoria(int shmid)
{
    void *ptr;

    ptr = shmat(shmid, NULL, 0);
    if (ptr == (void *)-1) {
        perror("Error al adjuntar memoria compartida");
        return NULL;
    }

    return ptr;
}

/*
 * DesvincularMemoria - Desvincula el segmento del espacio del proceso
 * @ptr: puntero al segmento previamente adjuntado
 */
void DesvincularMemoria(void *ptr)
{
    if (shmdt(ptr) == -1) {
        perror("Error al desvincular memoria compartida");
    }
}

/*
 * EliminarMemoria - Marca el segmento para eliminación
 * @shmid: identificador del segmento a eliminar
 */
void EliminarMemoria(int shmid)
{
    if (shmctl(shmid, IPC_RMID, NULL) == -1) {
        perror("Error al eliminar memoria compartida");
    }
}
