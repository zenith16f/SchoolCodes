// Este codigo va a ser utilizado para la implementacion de la teoria de
// conjuntos en C usando operaciones de bits, va a recibir dos conjuntos y va a
// realizar las operaciones de union, interseccion, diferencia, diferencia
// simetrica y complemento. Cada bit va a representar un elemento del conjunto\n
// Por ejemplo, el conjunto {0, 2, 3} se va a representar como
// 00000000000000000000000000001110

// Include                                                                    //
#include <math.h>
#include <stdio.h>

// NOTE: Functions

// Union
void Union(unsigned short set1, unsigned short set2) {
  // Operation
  unsigned short unionSet = set1 | set2;

  // Output
  printf("La union de los conjuntos es: %d\n", unionSet);
}

// Intersection
void Intersection(unsigned short set1, unsigned short set2) {
  // Operation
  unsigned short intersectionSet = set1 & set2;

  // Output
  printf("La interseccion de los conjuntos es: %d\n", intersectionSet);
}

// Difference
void Difference(unsigned short set1, unsigned short set2) {
  // Operation
  unsigned short differenceSet = set1 & ~set2;

  // Output
  printf("La diferencia de los conjuntos es: %d\n", differenceSet);
}

// Symmetric Difference
void SymmetricDifference(unsigned short set1, unsigned short set2) {
  // Operation
  unsigned short symmetricDifferenceSet = set1 ^ set2;

  // Output
  printf("La diferencia simetrica de los conjuntos es: %d\n",
         symmetricDifferenceSet);
}

// Complement
void Complement(unsigned short universe, unsigned short set) {
  // Operation
  unsigned short complementSet = universe & ~set;

  // Output
  printf("El complemento del conjunto %d es: %d\n", set, complementSet);
}

// Main Function
int main(int argc, char *argv[]) {
  // Variables
  unsigned short universe = pow(2, 16) - 1, set1 = 7, set2 = 242;
  // set1 = 00000000000000000000000000000111=7
  // set2 = 00000000000000000000000011110010=242

  // Mensaje de bienvenida
  printf("Este programa va a realizar operaciones de conjuntos\n");
  printf("Los conjuntos van a ser representados por numeros enteros (Z)\n");

  // Input
  // printf("Ingrese el primer conjunto: ");

  // Function Calls
  // Union
  Union(set1, set2);

  // Intersection
  Intersection(set1, set2);

  // Difference
  Difference(set1, set2);

  // Symmetric Difference
  SymmetricDifference(set1, set2);

  // Complement
  Complement(universe, set1);
  Complement(universe, set2);

  return 0;
}
