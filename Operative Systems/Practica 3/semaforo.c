/*
 * semaforo.c - Operaciones sobre semáforos System V
 */

#include "definitions.h"

/*
 * CrearSemaforo - Crea un semáforo con un valor inicial
 * @llave:          clave IPC generada con ftok
 * @valor_inicial:  valor con el que se inicializa el semáforo
 * Retorna: identificador del semáforo, o -1 en error
 */
int CrearSemaforo(key_t llave, int valor_inicial)
{
    int semid;

    semid = semget(llave, 1, IPC_CREAT | PERMISOS);
    if (semid == -1) {
        perror("Error al crear el semaforo");
        return -1;
    }

    if (semctl(semid, 0, SETVAL, valor_inicial) == -1) {
        perror("Error al inicializar el semaforo");
        return -1;
    }

    return semid;
}

/*
 * SemaforoDown - Operación P (wait/decremento) sobre el semáforo
 * @semid: identificador del semáforo
 */
void SemaforoDown(int semid)
{
    struct sembuf operacion;

    operacion.sem_num = 0;
    operacion.sem_op = -1;
    operacion.sem_flg = 0;

    if (semop(semid, &operacion, 1) == -1) {
        perror("Error en SemaforoDown");
        exit(EXIT_FAILURE);
    }
}

/*
 * SemaforoUp - Operación V (signal/incremento) sobre el semáforo
 * @semid: identificador del semáforo
 */
void SemaforoUp(int semid)
{
    struct sembuf operacion;

    operacion.sem_num = 0;
    operacion.sem_op = +1;
    operacion.sem_flg = 0;

    if (semop(semid, &operacion, 1) == -1) {
        perror("Error en SemaforoUp");
        exit(EXIT_FAILURE);
    }
}

/*
 * EliminarSemaforo - Elimina el semáforo del sistema
 * @semid: identificador del semáforo a eliminar
 */
void EliminarSemaforo(int semid)
{
    if (semctl(semid, 0, IPC_RMID) == -1) {
        perror("Error al eliminar el semaforo");
    }
}
