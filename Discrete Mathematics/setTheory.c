// TODO: Falta agregar la posibilidad de ingresar los conjuntos (El universo, el
// primero y el segundo), donde el universo solo se especifica la cantidad de
// elementos que contara con , el primero y segundo, se leera en texto y se hara
// la transformacion para pasarlo a un numero donde se sume los 'elementos del
// conjunto'

// Defines
#define MAX_LIMIT 64

// Includes
#include <math.h>
#include <stdio.h>

// NOTE: Functions

// Union
void Union(unsigned long set1, unsigned long set2) {
  // Operation
  unsigned long unionSet = set1 | set2;

  // Output
  printf("La union de los conjuntos es: %ld\n", unionSet);
}

// Intersection
void Intersection(unsigned long set1, unsigned long set2) {
  // Operation
  unsigned long intersectionSet = set1 & set2;

  // Output
  printf("La interseccion de los conjuntos es: %ld\n", intersectionSet);
}

// Difference
void Difference(unsigned long set1, unsigned long set2) {
  // Operation
  unsigned long differenceSet = set1 & ~set2;

  // Output
  printf("La diferencia de los conjuntos es: %ld\n", differenceSet);
}

// Symmetric Difference
void SymmetricDifference(unsigned long set1, unsigned long set2) {
  // Operation
  unsigned long symmetricDifferenceSet = set1 ^ set2;

  // Output
  printf("La diferencia simetrica de los conjuntos es: %ld\n",
         symmetricDifferenceSet);
}

// Complement
void Complement(unsigned long universe, unsigned long set) {
  // Operation
  unsigned long complementSet = universe & ~set;

  // Output
  printf("El complemento del conjunto %ld es: %ld\n", set, complementSet);
}

// Main Function
int main(int argc, char *argv[]) {
  // Variables
  int elements;
  char conjunto1[MAX_LIMIT], conjunto2[MAX_LIMIT];
  unsigned long universe, set1 = 7, set2 = 242;
  // set1 = 00000000000000000000000000000111=7
  // set2 = 00000000000000000000000011110010=242

  // Mensaje de bienvenida
  printf("Este programa va a realizar operaciones de conjuntos\n");
  printf("Los conjuntos van a ser representados por numeros enteros (Z)\n");

  // Input
  // Universe Set
  printf(
      "Ingrese los elementos del conjunto (universo siendo el maximo 64 )\n");
  printf("-> ");
  scanf("%d", &elements);
  universe = pow(2, elements) - 1;
  printf("El conjunto universo es: %ld \n", universe);

  // First Set
  printf("Ingresa los elementos del primer conjuento separados por comas\n");
  printf("-> ");
  fgets(conjunto1, MAX_LIMIT, stdin);
  printf("Ingresaste: %s\n", conjunto1);

  // Second Set
  printf("Ingresa los elementos del primer conjuento separados por comas\n");
  printf("-> ");
  fgets(conjunto2, MAX_LIMIT, stdin);
  printf("Ingresaste: %s\n", conjunto2);

  // Function Calls
  // Union
  Union(set1, set2);

  // Intersection
  Intersection(set1, set2);

  // Difference
  Difference(set1, set2);
  Difference(set2, set1);

  // Symmetric Difference
  SymmetricDifference(set1, set2);

  // Complement
  Complement(universe, set1);
  Complement(universe, set2);

  return 0;
}
