// Defines
#define EXPRESSION 100
#define MAXSetSize 64

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
			     unsigned int *grafica) {
  // Variables

  // Verificacion

};

// Funcion que recibe la funcion y verifica si es inyectiva
void CondicionInyectividad(char *funcion) {
  // Variables

  // Verificacion

};

// Funcion que recibe la funcion y verifica si es suprayectiva
void CondicionSuprayectividad(char *funcion) {
  // Variables

  // Verificacion

};

// Funcion que recibe la funcion y verifica si es biyectiva
void CondicionBiyectividad(char *funcion) {
  // Variables
  bool condicionInicial, cumpleInyectividad, cumpleSuprayectividad;

  // Main Condition
  

  while (condicionInicial) {
    CondicionInyectividad(funcion);
    CondicionSuprayectividad(funcion);

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

  if (!condicionInicial) {
    printf("La expresion no es una funcion por lo que no cumple la condicion "
           "de suprayectividad e inyectividad\n");
    printf("Por lo tanto no es biyectiva\n");
  }
};

// Funcion que recibe un conjunto en texto y lo transforma en un conjunto de
// elementos
void SetConjunto(char *conjunto) {};

// Funcion que recibe la grafica de una funcion y la transforma en un conjunto
// de elementos
void SetGrafica(char *grafica) {};

// Main Function
int main(void) {
  // Variables
  char expresion[EXPRESSION], dominioSTR[MAXSetSize], codominioSTR[MAXSetSize];
  int dominio[MAXSetSize], codominio[MAXSetSize], grafica[MAXSetSize];

  // Bienvenida
  printf("Este programa se encarga de recibir una expresion.\n");
  printf("Posteriormente se encargara de identificar si la expresion es o no es"
         "funcion, en caso de ser funcion si es inyectiva, suprayectiva y/o "
         "biyectiva en base a su dominio y codominio.\n");

  // Expression Input
  ExpresionAlgebraica(expresion);

  // Dom and Codom Input

  printf("Ingrese el dominio de la funcion con comas (Elementos maximos 64 en "
         "los enteros positivos): ");
  scanf("%s", dominioSTR);

  printf("Ingrese el codominio de la funcion con comas (Elementos maximos 64 "
         "en los enteros positivos): ");
  scanf(" %s", codominioSTR);

  printf("El dominio de la funcion es: %s\n", dominioSTR);
  printf("El codominio de la funcion es: %s\n", codominioSTR);

  // Biyectividad Call (This function call the other functions)
  // CondicionBiyectividad(expresion);

  return 0;
}
