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
// primer conjunto le corresponde un unico elemento del segundo conjunto, para que se cumpla una funcion f(x) = dom, codom y grafica de for 
// grafica de f = {(x, f(x)) | x pertenece a dom}
// Inyectividad: f(x) = f(y) => x = y || f(x) != f(y) => x != y
// Suprayectividad: f(x) = y
// Biyectividad: Inyectividad + Sobreyectividad

// Functions
// Funcion que recibe la expresion algebraica y la transforma en una
// funcion(Operable)
void ExpresionAlgebraica(char *funcion) {
  printf("Ingrese la expresion algebraica: ");
  scanf("%s", funcion);
  printf("La expresion algebraica ingresada es: %s\n", funcion);
};

// Funcion que recibe la funcion y verifica si es una funcion
bool CondicionFuncion(char *funcion) {
  // Variables
  bool cumple;

  // Verificacion

  // return
  return cumple;
};

// Funcion que recibe la funcion y verifica si es inyectiva
bool CondicionInyectividad(char *funcion) {
  // Variables
  bool cumple;

  // Verificacion

  // return
  return cumple;
};

// Funcion que recibe la funcion y verifica si es suprayectiva
bool CondicionSuprayectividad(char *funcion) {
  // Variables
  bool cumple;

  // Verificacion

  // return
  return cumple;
};

// Funcion que recibe la funcion y verifica si es biyectiva
void CondicionBiyectividad(char *funcion) {
  // Variables
  bool condicionInicial, cumpleInyectividad, cumpleSuprayectividad;

  // Main Condition
  condicionInicial = CondicionFuncion(funcion);

  while (condicionInicial) {
    cumpleInyectividad = CondicionInyectividad(funcion);
    cumpleSuprayectividad = CondicionSuprayectividad(funcion);

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

// Main Function
int main(void) {
  // Variables
  char expresion[EXPRESSION], dominioSTR[MAXSetSize], codominioSTR[MAXSetSize];
  int dominio[MAXSetSize], codominio[MAXSetSize];

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
