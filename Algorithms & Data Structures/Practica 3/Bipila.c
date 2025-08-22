// Include
#include <stdio.h>
#include <stdlib.h>


// Structure
typedef struct Bipila {
    int *data; // Array de datos
    int size;  // Tamaño del array
    int topDown;  // Top de la pila inferior
    int topUp;  // Top de la pila superior
} Bipila;

// Functions
// Create
Bipila* crearBipila(int size){
    Bipila* bipila = (Bipila*)malloc(sizeof(Bipila)); 
    bipila->data = (int*)malloc(size * sizeof(int));
    bipila->size = size;
    bipila->topDown = 0;
    bipila->topUp = size; 
    return bipila;
}

// IS_EMPTY
int isEmptyDown(Bipila* bipila) {
    return bipila->topDown == -1; // Return only if topDown is equal to -1 (empty)
}

int isEmptyUp(Bipila* bipila) {
    return bipila->topUp == bipila->size; // Return only if topUp is equal to size (empty)
}

// IS_FULL
int isFull(Bipila* bipila) {
    return bipila->topDown == bipila->topUp; // Return only if topDown + 1 is equal to topUp (full)
}

// POP
int popDown(Bipila* bipila) {
    if (isEmptyDown(bipila)) {
        printf("Pila inferior vacia\n");
        return -1; 
    }
    return bipila->data[bipila->topDown--]; // Return the value and decrement topDown
}

int popUp(Bipila* bipila) {
    if (isEmptyUp(bipila)) {
        printf("Pila superior vacia\n");
        return -1; 
    }
    return bipila->data[bipila->topUp++]; // Return the value and increment topUp
}

// PUSH
void pushDown(Bipila* bipila, int value) {
    if (isFull(bipila)) {
        printf("Pila inferior llena\n");
        return;
    }
    bipila->data[++bipila->topDown] = value; 
}

void pushUp(Bipila* bipila, int value) {
    if (isFull(bipila)) {
        printf("Pila superior llena\n");
        return;
    }
    bipila->data[--bipila->topUp] = value; 
}

// TOP
int topDown(Bipila* bipila) {
    if (isEmptyDown(bipila)) {
        printf("Pila inferior vacia\n");
        return -1; 
    }
    return bipila->data[bipila->topDown]; // Return the value of the top element
}

int topUp(Bipila* bipila) {
    if (isEmptyUp(bipila)) {
        printf("Pila superior vacia\n");
        return -1; 
    }
    return bipila->data[bipila->topUp]; // Return the value of the top element
}

// Free
void liberarMemoria(Bipila* bipila) {
    free(bipila->data); // Free the data array
    free(bipila); // Free the bipila structure
}

// Main
void main(void *){
    Bipila* bipila = crearBipila(15); // Create a bipila of size 10

    // PushDown 
    pushDown(bipila, 1);
    pushDown(bipila, 2);
    pushDown(bipila, 3);
    pushDown(bipila, 8);
    pushDown(bipila, 14);
    pushDown(bipila, 1);
    pushDown(bipila, 2);
    pushDown(bipila, 3);
    pushDown(bipila, 8);
    pushDown(bipila, 14);

    // PushUp 
    pushUp(bipila, 4);
    pushUp(bipila, 5);
    pushUp(bipila, 6);
    pushUp(bipila, 16);
    pushUp(bipila, 24);

    // Tope
    printf("El tope de la pila superior es: %d\n",bipila->topUp);
    printf("El tope de la pila inferior es: %d\n",bipila->topDown);
    printf("Tamaño: %d\n",bipila->size);

    // Is Full
    printf("Llena tras ingresar datos? %d\n",isFull(bipila));

    // Top 
    printf("Top up: %d\n",topUp(bipila));
    printf("Top Down: %d\n",topDown(bipila));

    // Pop 
    printf("Pop down: %d\n", popDown(bipila)); // This should print 3
    printf("Pop down: %d\n", popDown(bipila)); // This should print 2

    // Pop 
    printf("Pop up: %d\n", popUp(bipila)); // This should print 6
    printf("Pop up: %d\n", popUp(bipila)); // This should print 5

    // Is Full
    printf("Llena tras sacar datos? %d\n",isFull(bipila));

     // Tope
     printf("El tope de la pila superior es: %d\n",bipila->topUp);
     printf("El tope de la pila inferior es: %d\n",bipila->topDown);

    // Liberar
    liberarMemoria(bipila); 
}

// Codigo Bipila (2 pilas comparten el mismo espacio de memoria)
// Autor: Zenith16f
