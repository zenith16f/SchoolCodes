// Defines
#define MAXSetSize 64
#define MAXGraficaSize 128
#define MAXTuplas MAXGraficaSize / 2
#define MAXElementos 100

// Includes
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Functions
// Funcion que recibe la funcion y verifica si es funcion o no. Usando la
// definicon de existencialismo y unicidad
int CondicionFuncion(int dominio[MAXSetSize], int grafica[MAXSetSize][2],
                     int numeroPares) {
  int visitados[MAXElementos] = {0};
  int todosVisitados[MAXElementos] = {0};

  // Marcar los elementos del dominio que aparecen en la relación
  for (int i = 0; i < numeroPares; i++) {
    int x = grafica[i][0];
    todosVisitados[x] = 1;
  }

  // Verificar unicidad y existencialidad simultáneamente
  for (int i = 0; i < numeroPares; i++) {
    int x = grafica[i][0];
    int y = grafica[i][1];
    if (visitados[y] == 1) {
      return 0;
    }
    visitados[y] = 1;
    todosVisitados[x] = 0;
  }

  // Verificar existencialidad
  for (int i = 0; i < MAXElementos; i++) {
    if (dominio[i] == 1 && todosVisitados[i] == 1) {
      return 0;
    }
  }

  return 1;
}

// Funcion que recibe la funcion y verifica si es inyectiva
int CondicionInyectividad(int dominio[MAXSetSize], int codominio[MAXSetSize],
                          int grafica[MAXSetSize][2], int numPares) {
  // Variables
  static int visitados[MAXElementos] = {0};

  // Verificacion
  for (int i = 0; i < numPares; i++) {
    int y = grafica[i][1];
    if (visitados[y] == 1) {
      return 0;
    }
    visitados[y] = 1;
  }

  return 1;
}

// Funcion que recibe la funcion y verifica si es suprayectiva
int CondicionSuprayectividad(int dominio[MAXSetSize], int codominio[MAXSetSize],
                             int grafica[MAXSetSize][2], int numPares) {
  // Variables
  int visitados[MAXElementos] = {0};

  // Verificacion
  for (int i = 0; i < numPares; i++) {
    int y = grafica[i][1];
    visitados[y] = 1;
  }

  for (int i = 0; i < MAXElementos; i++) {
    if (codominio[i] == 1 && visitados[i] == 0) {
      return 0;
    }
  }

  return 1;
}

// Funcion que recibe la funcion y verifica si es biyectiva
void CondicionBiyectividad(int dominio[MAXSetSize], int codominio[MAXSetSize],
                           int grafica[MAXSetSize][2]) {
  // Variables
  int cumpleFuncion, cumpleInyectividad, cumpleSuprayectividad;
  int numeroPares = sizeof(&grafica) / sizeof(grafica[0]);

  // Main Condition
  cumpleFuncion = CondicionFuncion(dominio, grafica, numeroPares);
  printf("%d\n", cumpleFuncion);

  if (cumpleFuncion) {
    cumpleInyectividad =
        CondicionInyectividad(dominio, codominio, grafica, numeroPares);
    cumpleSuprayectividad =
        CondicionSuprayectividad(dominio, codominio, grafica, numeroPares);

    printf("%d ", cumpleInyectividad);
    printf("%d \n", cumpleSuprayectividad);

    if (cumpleInyectividad && cumpleSuprayectividad) {
      printf("La funcion cumple con las condiciones de inyectividad y "
             "suprayectividad\n");
      printf("Por lo tanto tambien es biyectiva\n");
    }

    if (cumpleInyectividad && !cumpleSuprayectividad) {
      printf("La funcion cumple con las condiciones de inyectividad pero no "
             "suprayectividad\n");
      printf("Por lo tanto no es biyectiva\n");
    }

    if (!cumpleInyectividad && cumpleSuprayectividad) {
      printf("La funcion no cumple con las condiciones de inyectividad pero si "
             "suprayectividad\n");
      printf("Por lo tanto no es biyectiva\n");
    }

    if (!cumpleInyectividad && !cumpleSuprayectividad) {
      printf("La funcion no cumple con las condiciones de inyectividad ni "
             "suprayectividad\n");
      printf("Por lo tanto no es biyectiva\n");
    }
  }

  if (!cumpleFuncion) {
    printf("La expresion no es una funcion\n");
  }
};

// Funcion que recibe un conjunto en texto y lo transforma en un conjunto de
// elementos (Array)
int *SetConjunto(char *conjunto, int *numeroElementos) {
  // Variables
  static int arregloConjunto[MAXSetSize];
  int i = 0;
  char *ptr = strtok(conjunto, ",");

  // Transformacion
  while (ptr != NULL && i < MAXSetSize) {
    arregloConjunto[i++] = atoi(ptr);
    ptr = strtok(NULL, ",");
  }

  // return
  *numeroElementos = i;
  return arregloConjunto;
};

// Funcion que recibe la grafica de una funcion y la transforma en un conjunto
// de elementos
int SetGrafica(char *grafica, int graficaSet[MAXTuplas][2], int *numeroTuplas) {
  int i = 0, j = 0;
  char *ptr = strtok(grafica, ",");

  while (ptr != NULL && i < MAXTuplas - 1) {
    graficaSet[j][0] = atoi(ptr);
    ptr = strtok(NULL, ",");

    if (ptr != NULL) {
      graficaSet[j][1] = atoi(ptr);
      ptr = strtok(NULL, ",");
      j++;
    }
    i += 2;
  }

  *numeroTuplas = j;
  return 0;
};

// Main Function
int main(void) {
  // Variables
  char dominioSTR[MAXSetSize], codominioSTR[MAXSetSize],
      graficaSTR[MAXGraficaSize];
  int numeroElementosDom, numeroElementosCodom, numeroElementosGrafica,
      graficaSet[MAXTuplas][2];

  // Bienvenida
  printf("Este programa se encarga de recibir una expresion.\n");
  printf("Posteriormente se encargara de identificar si la expresion es o no es"
         "funcion, en caso de ser funcion si es inyectiva, suprayectiva y/o "
         "biyectiva en base a su dominio y codominio.\n");

  // Dom and Codom Input
  printf("Ingrese el dominio de la funcion con comas (Elementos maximos 32, en "
         "los enteros positivos): ");
  scanf("%s", dominioSTR);
  int *dominio = SetConjunto(dominioSTR, &numeroElementosDom);

  printf("Ingrese el codominio de la funcion con comas (Elementos maximos 32, "
         "en los enteros positivos): ");
  scanf(" %s", codominioSTR);
  int *codominio = SetConjunto(codominioSTR, &numeroElementosCodom);

  // Grafica Input (Se separa de par en par)
  printf("Ingrese la grafica de la funcion con comas (Elementos maximos 64, en "
         "los enteros positivos): ");
  scanf(" %s", graficaSTR);

  SetGrafica(graficaSTR, graficaSet, &numeroElementosGrafica);

  // Biyectividad Call
  CondicionBiyectividad(dominio, codominio, graficaSet);

  return 0;
}
