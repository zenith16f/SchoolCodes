// Defines
#include <stdint.h>
#define MAXSetSize 64 // Bits
#define MAXGraficaSize 128
#define MAXTuplas MAXGraficaSize / 2
#define MAXElementos 64

// Includes
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Functions
// Funcion que recibe la funcion y verifica si es funcion o no. Usando la
// definicon de existencialismo y unicidad
int CondicionFuncion(uint64_t dominio, int grafica[MAXSetSize][2],
                     int numeroPares ) {
  // Variables
  int i,contador = 0;

  // Verificacion
  for (i = 0; i < 32 ; i++) {
    if (dominio & (1 << i)) {
      for (int j = 0; j < numeroPares; j++) {
        if (grafica[j][0] == i) {
          contador += 1;
        }
      }
      if (contador == 0 || contador > 1) {
        return 0; // No es funcion
      } else {
        contador = 0;
      }
    }
  }

  return 1; // Es funcion
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
                             int grafica[MAXSetSize][2], int numPares,
                             int tamDominio, int tamCodominio) {
  // Variables
  int cubierto[MAXElementos] = {0};

  // Verificacion
  for (int i = 0; i < numPares; i++) {
    int elementoCodominio = grafica[i][1];

    for (int j = 0; j < tamCodominio; j++) {
      if (codominio[j] == elementoCodominio) {
        cubierto[j] = 1;
        break;
      }
    }
  }

  // Verifica si todos los elementos del codominio fueron cubiertos
  for (int i = 0; i < tamCodominio; i++) {
    if (!cubierto[i]) {
      return 0;
    }
  }

  return 1;
}

// Funcion que recibe la funcion y verifica si es biyectiva
void CondicionBiyectividad(uint64_t dominio, unsigned long codominio,
                           int grafica[MAXSetSize][2], int *numeroPares,
                           int *numeroElementosDom, int *numeroElementosCodom) {
  // Variables
  int cumpleFuncion, cumpleInyectividad, cumpleSuprayectividad;
  // Main Condition
  cumpleFuncion =
      CondicionFuncion(dominio, grafica, *numeroPares);

  if (cumpleFuncion) {
    printf("La expresion es una funcion.\n");
    /*cumpleInyectividad = CondicionInyectividad(dominio, codominio, grafica,
    *numeroPares); cumpleSuprayectividad =  CondicionSuprayectividad(dominio,
    codominio, grafica, *numeroPares, *numeroElementosDom,
    *numeroElementosCodom);

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
    }*/
  }

  if (!cumpleFuncion) {
    printf("La expresion no es una funcion\n");
  }
};

// Funcion que recibe un conjunto en texto y lo transforma en un conjunto de
// bits
int setInputConversion(char *texto) {
  // Variables
  unsigned long long suma = 0;
  char *ptr = strtok(texto, ",");

  // Operation
  while (ptr != NULL) {
    int num = atoi(ptr);

    // Validacion
    if (num < 0 || num > 31) {
      printf("El numero %d no es valido\n", num);
      exit(1);
    }

    suma |= (long)pow(2, num);
    ptr = strtok(NULL, ",");
  }

  return suma;
}

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
  uint64_t dominio = setInputConversion(dominioSTR);

  printf("Ingrese el codominio de la funcion con comas (Elementos maximos 32, "
         "en los enteros positivos): ");
  scanf(" %s", codominioSTR);
  unsigned long codominio =
      setInputConversion(codominioSTR);

  // Grafica Input (Se separa de par en par)
  printf("Ingrese la grafica de la funcion con comas (Elementos maximos 64, en "
         "los enteros positivos): ");
  scanf(" %s", graficaSTR);

  SetGrafica(graficaSTR, graficaSet, &numeroElementosGrafica);

  // Debug

  // Biyectividad Call
  CondicionBiyectividad(dominio, codominio, graficaSet, &numeroElementosGrafica,
                        &numeroElementosDom, &numeroElementosCodom);

  return 0;
}
