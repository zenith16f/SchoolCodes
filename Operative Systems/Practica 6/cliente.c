/*
 * cliente.c
 * Compilación: make
 * Ejecución: ./cliente (en otra terminal)
 */
#include "comunes.h"
#include "memoria.h"
#include "semaforo.h"
#include "validacion.h"
int main(void)
{
    key_t llave_shm, llave_sem_mutex, llave_sem_servidor, llave_sem_cliente;
    int shmid, sem_mutex, sem_servidor, sem_cliente;
    DatosCompartidos *datos;
    char frase[MAX_FRASE];
    int palabras;
    printf("=====================================================\n");
    printf(" PRACTICA 6: Cliente-Servidor con procesos\n");
    printf(" no emparentados y archivos\n");
    printf(" Cliente - PID: %d\n", getpid());
    printf("=====================================================\n\n");
    llave_shm = ftok(ARCHIVO_SHM, ID_SHM);
    llave_sem_mutex = ftok(ARCHIVO_SEM, ID_SEM_MUTEX);
    llave_sem_servidor = ftok(ARCHIVO_SEM, ID_SEM_SERVIDOR);
    llave_sem_cliente = ftok(ARCHIVO_SEM, ID_SEM_CLIENTE);
    if (llave_shm == -1 || llave_sem_mutex == -1 || llave_sem_servidor == -1 ||
        llave_sem_cliente == -1)
    {
        fprintf(stderr,
                "[Cliente] Error: No se pudieron generar las claves IPC.\n");
        fprintf(stderr, "[Cliente] Asegúrese de que el servidor esté corriendo.\n");
        exit(EXIT_FAILURE);
    }
    /* Obtener recursos IPC existentes (creados por el servidor) */
    shmid = ObtenerMemoriaCompartida(llave_shm, sizeof(DatosCompartidos));
    if (shmid == -1)
    {
        fprintf(stderr,
                "[Cliente] Error: No se pudo acceder a la memoria compartida.\n");
        fprintf(stderr, "[Cliente] Asegúrese de que el servidor esté corriendo.\n");
        exit(EXIT_FAILURE);
    }
    datos = (DatosCompartidos *)AdjuntarMemoria(shmid);
    if (datos == NULL)
        exit(EXIT_FAILURE);
    sem_mutex = ObtenerSemaforo(llave_sem_mutex);
    sem_servidor = ObtenerSemaforo(llave_sem_servidor);
    sem_cliente = ObtenerSemaforo(llave_sem_cliente);
    if (sem_mutex == -1 || sem_servidor == -1 || sem_cliente == -1)
    {
        fprintf(stderr, "[Cliente] Error: No se pudieron obtener los semáforos.\n");
        DesvincularMemoria(datos);
        exit(EXIT_FAILURE);
    }
    if (!datos->servidor_activo)
    {
        fprintf(stderr, "[Cliente] Error: El servidor no está activo.\n");
        DesvincularMemoria(datos);
        exit(EXIT_FAILURE);
    }
    printf("[Cliente] Conexión establecida con el servidor.\n");
    printf("[Cliente] Memoria compartida adjuntada (ID: %d)\n\n", shmid);
    do
    {
        printf("[Cliente] Ingrese una frase de exactamente 10 palabras:\n");
        printf("[Cliente] > ");
        if (fgets(frase, MAX_FRASE, stdin) == NULL)
        {
            fprintf(stderr, "[Cliente] Error al leer la entrada.\n");
            DesvincularMemoria(datos);
            exit(EXIT_FAILURE);
        }
        frase[strcspn(frase, "\n")] = '\0';
        if (strlen(frase) == 0)
        {
            printf("[Cliente] Error: La frase no puede estar vacía.\n\n");
            continue;
        }
        palabras = ContarPalabras(frase);
        if (!ValidarFrase(frase))
        {
            printf("[Cliente] Error: La frase tiene %d palabra(s). "
                   "Se requieren exactamente 10.\n\n",
                   palabras);
        }
    } while (!ValidarFrase(frase));
    printf("\n[Cliente] Frase válida (%d palabras). Enviando al servidor...\n",
           ContarPalabras(frase));
    /* ======== SECCIÓN CRÍTICA ======== */
    SemaforoDown(sem_mutex);
    strncpy(datos->frase, frase, MAX_FRASE - 1);
    datos->frase[MAX_FRASE - 1] = '\0';
    datos->cliente_id = getpid();
    datos->hay_cliente = 1;
    SemaforoUp(sem_mutex);
    /* ======== FIN SECCIÓN CRÍTICA ======== */
    SemaforoUp(sem_servidor);
    printf("[Cliente] Frase enviada. Esperando respuesta del servidor...\n");
    SemaforoDown(sem_cliente);
    SemaforoDown(sem_mutex);
    printf("\n[Cliente] Respuesta del servidor:\n");
    printf("[Cliente] >>> \"%s\"\n", datos->respuesta);
    SemaforoUp(sem_mutex);
    DesvincularMemoria(datos);
    printf("\n[Cliente] Comunicación completada. Cliente finalizado.\n");
    printf("=====================================================\n");
    return 0;
}