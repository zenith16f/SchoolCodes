#include <stdio.h>

// Functions
// Imprime los digitos de un numero
void imprimeDigitos(int numero) {
  // Numero negativo
  if (numero < 0) {
    printf("-");
    numero = -numero;
  }

  // Numero de un solo digito
  if (numero < 10) {
    printf("%d\n", numero);
  } else {

    // Numero de mas de un digito (recursividad)
    imprimeDigitos(numero / 10);
    // Imprime el digito actual
    printf("%d\n", numero % 10);
  }
}

// Main function
int main() {
  // Variables
  int numero;

  // Input
  printf("Introduce un numero: ");
  scanf("%d", &numero);

  // Output
  printf("Los digitos del numero son: \n");
  imprimeDigitos(numero);
  printf("\n");
  return 0;
}
