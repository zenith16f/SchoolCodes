/*
 * semaforo.c
 */

#include "comunes.h"

int CrearSemaforo(key_t llave, int valor_inicial) {
  int semid;

  semid = semget(llave, 1, IPC_CREAT | PERMISOS);
  if (semid == -1) {
    perror("[Semaforo] Error en semget");
    return -1;
  }

  if (semctl(semid, 0, SETVAL, valor_inicial) == -1) {
    perror("[Semaforo] Error en semctl SETVAL");
    return -1;
  }

  return semid;
}

int ObtenerSemaforo(key_t llave) {
  int semid;

  semid = semget(llave, 1, 0);
  if (semid == -1) {
    perror("[Semaforo] Error al obtener semaforo existente");
    return -1;
  }

  return semid;
}

void SemaforoDown(int semid) {
  struct sembuf operacion;

  operacion.sem_num = 0;
  operacion.sem_op = -1;
  operacion.sem_flg = 0;

  if (semop(semid, &operacion, 1) == -1) {
    perror("[Semaforo] Error en SemaforoDown");
    exit(EXIT_FAILURE);
  }
}

void SemaforoUp(int semid) {
  struct sembuf operacion;

  operacion.sem_num = 0;
  operacion.sem_op = +1;
  operacion.sem_flg = 0;

  if (semop(semid, &operacion, 1) == -1) {
    perror("[Semaforo] Error en SemaforoUp");
    exit(EXIT_FAILURE);
  }
}

void EliminarSemaforo(int semid) {
  if (semctl(semid, 0, IPC_RMID) == -1) {
    perror("[Semaforo] Error al eliminar semaforo");
  }
}
