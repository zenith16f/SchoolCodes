#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Nodo
{
    int esPregunta;  // 1 si es pregunta, 0 si es animal
    char texto[100]; // pregunta o animal
    struct Nodo *izq;
    struct Nodo *der;
} Nodo;

Nodo *crearNodo(const char *texto, int esPregunta)
{
    Nodo *nuevo = (Nodo *)malloc(sizeof(Nodo));
    nuevo->esPregunta = esPregunta;
    strcpy(nuevo->texto, texto);
    nuevo->izq = nuevo->der = NULL;
    return nuevo;
}

char leerRespuesta()
{
    char resp[10];
    if (fgets(resp, sizeof(resp), stdin) == NULL)
    {
        return 0;
    }
    return (resp[0] == 's' || resp[0] == 'S') ? 's' : 'n';
}

void recorrerArbol(Nodo **raiz)
{
    Nodo *actual = *raiz;

    while (actual->esPregunta)
    {
        printf("%s (s/n): ", actual->texto);
        char r = leerRespuesta();
        if (r == 's')
        {
            actual = actual->der;
        }
        else
        {
            actual = actual->izq;
        }
    }

    // Llegamos a un animal
    printf("¿Es un(a) %s? (s/n): ", actual->texto);
    if (leerRespuesta() == 's')
    {
        printf("Adivinado \n");
    }
    else
    {
        char nuevoAnimal[100], nuevaPregunta[100];
        printf("Cual era el animal en que pensabas? ");
        /* fgets(nuevoAnimal, sizeof(nuevoAnimal), stdin); */
        if (fgets(nuevoAnimal, sizeof(nuevoAnimal), stdin) == NULL)
        {
            return;
        }
        nuevoAnimal[strcspn(nuevoAnimal, "\n")] = '\0'; // quitar salto

        printf("Dame una pregunta que distinga a un(a) %s de un(a) %s: ", nuevoAnimal, actual->texto);
        if (fgets(nuevaPregunta, sizeof(nuevaPregunta), stdin) == NULL)
        {
            return;
        }
        nuevaPregunta[strcspn(nuevaPregunta, "\n")] = '\0';

        printf("Para un(a) %s, ¿Cual seria la respuesta? (s/n): ", nuevoAnimal);
        char r = leerRespuesta();

        // Se crea un nodo hoja para el nuevo animal que el usuario ha pensado
        Nodo *nuevoAnimalNodo = crearNodo(nuevoAnimal, 0);
        Nodo *antiguoAnimalNodo = crearNodo(actual->texto, 0);

        strcpy(actual->texto, nuevaPregunta);
        actual->esPregunta = 1;

        if (r == 's')
        {
            actual->der = nuevoAnimalNodo;
            actual->izq = antiguoAnimalNodo;
        }
        else
        {
            actual->der = antiguoAnimalNodo;
            actual->izq = nuevoAnimalNodo;
        }

        printf("Gracias por la nueva informacion\n");
    }
}

void liberarArbol(Nodo *nodo)
{
    if (nodo)
    {
        liberarArbol(nodo->izq);
        liberarArbol(nodo->der);
        free(nodo);
    }
}

void main()
{
    printf("Bienvenido al Adivinador de Animales\n\n");

    Nodo *raiz = crearNodo("¿Vive en la tierra?", 1);
    raiz->der = crearNodo("leon", 0);
    raiz->izq = crearNodo("medusa", 0);

    char jugarDeNuevo;
    do
    {
        recorrerArbol(&raiz);
        printf("Quieres volver a jugar? (s/n): ");
        jugarDeNuevo = leerRespuesta();
    } while (jugarDeNuevo == 's');

    liberarArbol(raiz);
}
