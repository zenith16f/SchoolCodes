/*
 * servidor.c
 * Compilación: make
 * Ejecución:   ./servidor
 */

#include "comunes.h"
#include "memoria.h"
#include "semaforo.h"
#include <signal.h>

static int g_shmid = -1;
static int g_sem_mutex = -1;
static int g_sem_servidor = -1;
static int g_sem_cliente = -1;
static DatosCompartidos *g_datos = NULL;
static int g_servidor_corriendo = 1;
static int g_clientes_atendidos = 0;

typedef struct {
  DatosCompartidos *datos;
  int sem_mutex;
  int sem_servidor;
  int sem_cliente;
  int numero_cliente;
  pid_t pid_cliente;
  char frase[MAX_FRASE];
} DatosHilo;

void ManejarSenial(int sig) {
  (void)sig;
  printf("\n\n[Servidor] Señal de terminación recibida.\n");
  g_servidor_corriendo = 0;

  if (g_datos != NULL) {
    g_datos->servidor_activo = 0;
    DesvincularMemoria(g_datos);
  }

  if (g_sem_mutex != -1)
    EliminarSemaforo(g_sem_mutex);
  if (g_sem_servidor != -1)
    EliminarSemaforo(g_sem_servidor);
  if (g_sem_cliente != -1)
    EliminarSemaforo(g_sem_cliente);
  if (g_shmid != -1)
    EliminarMemoria(g_shmid);

  remove(ARCHIVO_SHM);
  remove(ARCHIVO_SEM);

  printf("[Servidor] Recursos IPC liberados. Total de clientes atendidos: %d\n",
         g_clientes_atendidos);
  printf("[Servidor] Servidor finalizado.\n");
  exit(EXIT_SUCCESS);
}

void *AtenderCliente(void *arg) {
  DatosHilo *info = (DatosHilo *)arg;

  printf("\n[Hilo %d] ============================================\n",
         info->numero_cliente);
  printf("[Hilo %d] Atendiendo al cliente con PID: %d\n", info->numero_cliente,
         info->pid_cliente);
  printf("[Hilo %d] Hilo ID: %lu\n", info->numero_cliente,
         (unsigned long)pthread_self());

  /* Mostrar la frase recibida */
  printf("[Hilo %d] Frase recibida del cliente:\n", info->numero_cliente);
  printf("[Hilo %d] >>> \"%s\"\n", info->numero_cliente, info->frase);

  /* Preparar respuesta */
  SemaforoDown(info->sem_mutex);

  snprintf(info->datos->respuesta, MAX_FRASE,
           "Servidor: Frase recibida correctamente por hilo %d (TID: %lu)",
           info->numero_cliente, (unsigned long)pthread_self());

  /* Señalar al cliente que la respuesta está lista */
  SemaforoUp(info->sem_mutex);
  SemaforoUp(info->sem_cliente);

  printf("[Hilo %d] Respuesta enviada al cliente PID %d\n",
         info->numero_cliente, info->pid_cliente);
  printf("[Hilo %d] ============================================\n",
         info->numero_cliente);

  free(info);
  return NULL;
}

int main(void) {
  key_t llave_shm, llave_sem_mutex, llave_sem_servidor, llave_sem_cliente;
  pthread_t hilo;
  DatosHilo *info_hilo;

  printf("=====================================================\n");
  printf("  PRACTICA 5: Cliente-Servidor con procesos\n");
  printf("  no emparentados\n");
  printf("  Servidor - PID: %d\n", getpid());
  printf("=====================================================\n");

  signal(SIGINT, ManejarSenial);

  fclose(fopen(ARCHIVO_SHM, "w"));
  fclose(fopen(ARCHIVO_SEM, "w"));

  llave_shm = ftok(ARCHIVO_SHM, ID_SHM);
  llave_sem_mutex = ftok(ARCHIVO_SEM, ID_SEM_MUTEX);
  llave_sem_servidor = ftok(ARCHIVO_SEM, ID_SEM_SERVIDOR);
  llave_sem_cliente = ftok(ARCHIVO_SEM, ID_SEM_CLIENTE);

  if (llave_shm == -1 || llave_sem_mutex == -1 || llave_sem_servidor == -1 ||
      llave_sem_cliente == -1) {
    perror("[Servidor] Error en ftok");
    exit(EXIT_FAILURE);
  }

  g_shmid = CrearMemoriaCompartida(llave_shm, sizeof(DatosCompartidos));
  if (g_shmid == -1)
    exit(EXIT_FAILURE);

  g_datos = (DatosCompartidos *)AdjuntarMemoria(g_shmid);
  if (g_datos == NULL)
    exit(EXIT_FAILURE);

  memset(g_datos, 0, sizeof(DatosCompartidos));
  g_datos->servidor_activo = 1;
  g_datos->hay_cliente = 0;

  printf("[Servidor] Memoria compartida creada (ID: %d, %lu bytes)\n", g_shmid,
         (unsigned long)sizeof(DatosCompartidos));

  /* Crear semáforos */
  g_sem_mutex = CrearSemaforo(llave_sem_mutex, 1);
  g_sem_servidor = CrearSemaforo(llave_sem_servidor, 0);
  g_sem_cliente = CrearSemaforo(llave_sem_cliente, 0);

  if (g_sem_mutex == -1 || g_sem_servidor == -1 || g_sem_cliente == -1) {
    ManejarSenial(0);
    exit(EXIT_FAILURE);
  }

  printf("[Servidor] Semáforos creados:\n");
  printf("  Mutex (ID: %d) - Protege la sección crítica\n", g_sem_mutex);
  printf("  Servidor (ID: %d) - Señal de cliente a servidor\n", g_sem_servidor);
  printf("  Cliente (ID: %d) - Señal de servidor a cliente\n", g_sem_cliente);
  printf("\n[Servidor] Esperando conexiones de clientes...\n");
  printf("[Servidor] Presione Ctrl+C para terminar.\n\n");

  while (g_servidor_corriendo) {

    SemaforoDown(g_sem_servidor);

    if (!g_servidor_corriendo)
      break;

    g_clientes_atendidos++;

    SemaforoDown(g_sem_mutex);

    info_hilo = (DatosHilo *)malloc(sizeof(DatosHilo));
    if (info_hilo == NULL) {
      perror("[Servidor] Error al asignar memoria para hilo");
      SemaforoUp(g_sem_mutex);
      continue;
    }

    info_hilo->datos = g_datos;
    info_hilo->sem_mutex = g_sem_mutex;
    info_hilo->sem_servidor = g_sem_servidor;
    info_hilo->sem_cliente = g_sem_cliente;
    info_hilo->numero_cliente = g_clientes_atendidos;
    info_hilo->pid_cliente = g_datos->cliente_id;
    strncpy(info_hilo->frase, g_datos->frase, MAX_FRASE - 1);
    info_hilo->frase[MAX_FRASE - 1] = '\0';

    g_datos->hay_cliente = 0;

    SemaforoUp(g_sem_mutex);

    printf("[Servidor] Cliente #%d conectado (PID: %d). Creando hilo...\n",
           g_clientes_atendidos, info_hilo->pid_cliente);

    if (pthread_create(&hilo, NULL, AtenderCliente, info_hilo) != 0) {
      perror("[Servidor] Error al crear hilo");
      free(info_hilo);
      continue;
    }

    pthread_detach(hilo);
  }

  ManejarSenial(0);
  return 0;
}
