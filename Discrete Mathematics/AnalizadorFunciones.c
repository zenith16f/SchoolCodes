// Defines
#define MAXSetSize 64
#define MAXGraficaSize 128

// Includes
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definitions
// Funcion: Relacion entre dos conjuntos de tal forma que a cada elemento del
// primer conjunto le corresponde un unico elemento del segundo conjunto, para
// que se cumpla una funcion f(x) = dom, codom y grafica de for grafica de f =
// {(x, f(x)) | x pertenece a dom} Inyectividad: f(x) = f(y) => x = y || f(x) !=
// f(y) => x != y Suprayectividad: f(x) = y Biyectividad: Inyectividad +
// Sobreyectividad

// Functions
// Funcion que verifica si es una funcion usando dominio, codominio y grafica
void CondicionFuncion(unsigned int *dominio, unsigned int *codominio,
			     unsigned int *grafica,bool *cumple) {
  // Variables

  // Verificacion

};

// Funcion que recibe la funcion y verifica si es inyectiva
void CondicionInyectividad(unsigned int *dominio, unsigned int *codominio,
			     unsigned int *grafica, bool *cumple) {
  // Variables

  // Verificacion

};

// Funcion que recibe la funcion y verifica si es suprayectiva
void CondicionSuprayectividad(unsigned int *dominio, unsigned int *codominio,
			       unsigned int *grafica, bool *cumple) {
  // Variables

  // Verificacion

};

// Funcion que recibe la funcion y verifica si es biyectiva
void CondicionBiyectividad(unsigned int *dominio, unsigned int *codominio,
			    unsigned int *grafica) {
  // Variables
  bool cumpleFuncion, cumpleInyectividad, cumpleSuprayectividad;

  // Main Condition
  CondicionFuncion(dominio, codominio, grafica, &cumpleFuncion);

  while (cumpleFuncion) {
    CondicionInyectividad(dominio, codominio, grafica, &cumpleInyectividad);
    CondicionSuprayectividad(dominio, codominio, grafica, &cumpleSuprayectividad);

    if (cumpleInyectividad && cumpleSuprayectividad) {
      printf("La funcion cumple con las condiciones de inyectividad y "
             "sobreyectividad\n");
      printf("Por lo tanto la funcion es biyectiva\n");
    } else {
      printf("La funcion no cumple con las condiciones de inyectividad y "
             "sobreyectividad\n");
      printf("Por lo tanto la funcion no es biyectiva\n");
    }
  }

  if (!cumpleFuncion) {
    printf("La expresion no es una funcion por lo que no cumple la condicion "
           "de suprayectividad e inyectividad\n");
    printf("Por lo tanto no es biyectiva\n");
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

	// Return 
	*numeroElementos = i;
	return arregloConjunto;
};

// Funcion que recibe un conjunto de elementos y lo transforma en un conjunto de tuplas (Array)
void graficaConjunto(char *conjunto) {
	// Variables
	unsigned int conjuntoEx;

};

// Funcion que recibe la grafica de una funcion y la transforma en un conjunto
// de elementos
void SetGrafica(char *grafica) {};

// Main Function
int main(void) {
  // Variables
  char dominioSTR[MAXSetSize], codominioSTR[MAXSetSize], graficaSTR[MAXGraficaSize];
  int numeroElementosDom, numeroElementosCodom, numeroElementosGraf;

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

  printf("El dominio de la funcion en txt es: %s\n", dominioSTR);
  printf("El codominio de la funcion en txt es: %s\n", codominioSTR);

 printf("El dominio (arreglo) contiene %d elementos:\n", numeroElementosDom);
    for (int i = 0; i < numeroElementosDom; i++) {
        printf("%d ", dominio[i]);
    }
    printf("\n");

    printf("El codominio (arreglo) contiene %d elementos:\n", numeroElementosCodom);
    for (int i = 0; i < numeroElementosCodom; i++) {
	  printf("%d ", codominio[i]);
    }
    printf("\n");

  printf("La grafica de la funcion es: %s\n", graficaSTR);



  // Biyectividad Call (This function call the other functions)
  // CondicionBiyectividad(expresion);

  return 0;
}
