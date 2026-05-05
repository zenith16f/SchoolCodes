/*
 * comunes.h
 */

#ifndef COMUNES_H
#define COMUNES_H

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <unistd.h>

/* ======================== CONSTANTES ======================== */
#define MAX_FRASE 256
#define MAX_CLIENTES 5
#define PERMISOS 0644

/* Archivos para generar claves IPC con ftok */
#define ARCHIVO_SHM "ipc_shm"
#define ARCHIVO_SEM "ipc_sem"

/* Caracteres para ftok */
#define ID_SHM 'M'
#define ID_SEM_MUTEX 'S'
#define ID_SEM_SERVIDOR 'V'
#define ID_SEM_CLIENTE 'C'

/* ======================== ESTRUCTURA COMPARTIDA ======================== */

typedef struct {
  char frase[MAX_FRASE];
  pid_t cliente_id;
  int hay_cliente;
  int servidor_activo;
  char respuesta[MAX_FRASE];
} DatosCompartidos;

#endif /* COMUNES_H */
