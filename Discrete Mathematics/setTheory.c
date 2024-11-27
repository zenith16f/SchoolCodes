// Define
#define MAX_LIMIT 64

// Includes
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Functions
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
void Difference(unsigned long set1, unsigned long set2, char A, char B) {
  // Operation
  unsigned long differenceSet = set1 & ~set2;

  // Output
  printf("La diferencia de los conjuntos (%c - %c) es: %ld\n", A, B,
         differenceSet);
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
void Complement(unsigned long universe, unsigned long set, char A) {
  // Operation
  unsigned long complementSet = universe & ~set;

  // Output
  printf("El complemento del conjunto %c es: %ld\n", A, complementSet);
}

// Universe Set Input
void UniverseSetInput(unsigned long *universe) {
  // Variables
  int elements;

  // Input
  printf(
      "Ingrese los elementos del conjunto (universo siendo el maximo 64 )\n");
  printf("-> ");
  scanf("%d", &elements);

  // Validation
  while (elements > 64 || elements < 0) {
    printf("El numero de elementos no puede ser mayor a 64 o menor a 0\n");
    printf(
        "Ingrese los elementos del conjunto (universo siendo el maximo 64 )\n");
    printf("-> ");
    scanf("%d", &elements);
  }

  // Operation
  *universe = pow(2, elements) - 1;
}

// INFO: Esta funcion no se esta utilizando, se cambio por setInputConversion
// (No falla pero no se esta utilizando y le falta validacion)

/*int SetInputConversion(char *set) {
  // Variables
  int setNumber = 0, i = 0;

  // Operation
  while (set[i] != '\0') {
    if (set[i] == ',') {
        i++;
        continue;
    }
    setNumber += pow(2, set[i] - '0');
    i++;
  }

  return setNumber;
}
*/

// Set Input Conversion
int setInputConversion(char *texto) {
  // Variables
  unsigned long suma = 0;
  char *ptr = strtok(texto, ",");

  // Operation
  while (ptr != NULL) {
    int num = atoi(ptr);
    // Validacion
    if (num < 0 || num > 63) {
      printf("El numero %d no es valido\n", num);
      exit(1);
    }
    suma += pow(2, num-1);
    ptr = strtok(NULL, ",");
  }

  return suma;
}

// Function Caller
void functionCaller(unsigned long set1, unsigned long set2,
                    unsigned long universe, char nomConjunto1,
                    char nomConjunto2) {
  // Function Calls
  // Union
  Union(set1, set2);

  // Intersection
  Intersection(set1, set2);

  // Difference
  Difference(set1, set2, nomConjunto1, nomConjunto2);
  Difference(set2, set1, nomConjunto2, nomConjunto1);

  // Symmetric difference
  SymmetricDifference(set1, set2);

  // Complement
  Complement(universe, set1, nomConjunto1);
  Complement(universe, set2, nomConjunto2);
}

// Main Function
int main(void) {
  // Variables
  char conjunto1[MAX_LIMIT], conjunto2[MAX_LIMIT];
  unsigned long universe, set1, set2;
  char nomConjunto1, nomConjunto2;

  // Mensaje de bienvenida
  printf("Este programa va a realizar operaciones de conjuntos\n");
  printf("Los conjuntos van a ser representados por numeros enteros positivos (Z+)\n");

  // Input
  // Universe Set
  UniverseSetInput(&universe);

  // First Set
  printf("Ingresa los elementos del primer conjunto (A) separados por comas "
         "(De 0 a 63)\n");
  printf("-> ");
  scanf(" %s", conjunto1);
  set1 = setInputConversion(conjunto1);
  nomConjunto1 = 'A';

  // Second Set
  printf("Ingresa los elementos del segundo conjunto (B) separados por comas "
         "(De 0 a 63)\n");
  printf("-> ");
  scanf(" %s", conjunto2);
  set2 = setInputConversion(conjunto2);
  nomConjunto2 = 'B';

  // Function Caller
  functionCaller(set1, set2, universe, nomConjunto1, nomConjunto2);

  // Return
  return 0;
}
