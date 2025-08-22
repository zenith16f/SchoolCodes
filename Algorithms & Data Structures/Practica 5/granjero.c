#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Estado
{
    int granjero;
    int zorro;
    int gallina;
    int maiz;
    char accion[50];
    struct Estado *anterior;
} Estado;

int es_estado_final(Estado *e)
{
    return e->granjero == 1 && e->zorro == 1 && e->gallina == 1 && e->maiz == 1;
}

int estado_repetido(Estado *nuevo, Estado *historial)
{
    while (historial != NULL)
    {
        if (nuevo->granjero == historial->granjero &&
            nuevo->zorro == historial->zorro &&
            nuevo->gallina == historial->gallina &&
            nuevo->maiz == historial->maiz)
            return 1;
        historial = historial->anterior;
    }
    return 0;
}

Estado *crear_estado(Estado *actual, int mover_zorro, int mover_gallina, int mover_maiz)
{
    Estado *nuevo = (Estado *)malloc(sizeof(Estado));
    nuevo->granjero = 1 - actual->granjero;
    nuevo->zorro = actual->zorro;
    nuevo->gallina = actual->gallina;
    nuevo->maiz = actual->maiz;
    nuevo->anterior = actual;

    if (mover_zorro && actual->zorro == actual->granjero)
    {
        nuevo->zorro = 1 - actual->zorro;
        strcpy(nuevo->accion, "Granjero lleva al zorro");
    }
    else if (mover_gallina && actual->gallina == actual->granjero)
    {
        nuevo->gallina = 1 - actual->gallina;
        strcpy(nuevo->accion, "Granjero lleva a la gallina");
    }
    else if (mover_maiz && actual->maiz == actual->granjero)
    {
        nuevo->maiz = 1 - actual->maiz;
        strcpy(nuevo->accion, "Granjero lleva el maiz");
    }
    else
    {
        strcpy(nuevo->accion, "Granjero cruza solo");
    }

    return nuevo;
}

void imprimir_estado(Estado *e)
{
    printf("Granjero:%d Zorro:%d Gallina:%d Maiz:%d\n", e->granjero, e->zorro, e->gallina, e->maiz);
}

void imprimir_orillas(Estado *e) {
    // Lado izquierdo
    if (e->granjero == 0) printf("granjero ");
    if (e->zorro == 0) printf("zorro ");
    if (e->gallina == 0) printf("gallina ");
    if (e->maiz == 0) printf("maiz ");

    // Río
    printf("  <=======>  ");

    // Lado derecho
    if (e->granjero == 1) printf("granjero ");
    if (e->zorro == 1) printf("zorro ");
    if (e->gallina == 1) printf("gallina ");
    if (e->maiz == 1) printf("maiz ");

    printf("\n");
}


void imprimir_solucion(Estado *e) {
    if (e == NULL)
        return;
    imprimir_solucion(e->anterior);

    imprimir_orillas(e);
    if (e->anterior != NULL)
        printf("- %s\n\n", e->accion);
    else
        printf("Inicio del problema\n\n");
}

int es_estado_seguro(Estado *e)
{
    // Si el granjero no está con la gallina, pero sí el zorro
    if (e->granjero != e->gallina && e->gallina == e->zorro)
        return 0;
    // Si el granjero no está con la gallina, pero sí el maíz
    if (e->granjero != e->gallina && e->gallina == e->maiz)
        return 0;
    return 1;
}
int resolver(Estado *actual)
{
    if (!es_estado_seguro(actual))
        return 0;

    if (es_estado_final(actual))
    {
        imprimir_solucion(actual);
        return 1;
    }
        //combinaciones
        Estado *movimientos[4];
        movimientos[0] = crear_estado(actual, 0, 0, 0); // solo granjero
        movimientos[1] = crear_estado(actual, 1, 0, 0); // granjero + zorro
        movimientos[2] = crear_estado(actual, 0, 1, 0); // granjero + gallina
        movimientos[3] = crear_estado(actual, 0, 0, 1); // granjero + maiz

    for (int i = 0; i < 4; i++)
    {
        if (!estado_repetido(movimientos[i], actual))
        {
            if (resolver(movimientos[i]))
                return 1;
        }
        free(movimientos[i]); // liberar si no se usa
    }

    return 0;
}

void main()
{
    Estado *inicio = (Estado *)malloc(sizeof(Estado));
    inicio->granjero = 0;
    inicio->zorro = 0;
    inicio->gallina = 0;
    inicio->maiz = 0;
    inicio->anterior = NULL;

    if (!resolver(inicio))
        printf("No hay solución\n");
}
