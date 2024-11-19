//  NOTE: Este codigo recibe un caracter (letra) y un codigo numerico, realiza
//  la operacion modulo y con el resultado se define si la letra ingresada es la
//  correcta, o si no

// Includes
#include <math.h>
#include <stdio.h>

// Function to validate the entered letter
int ValidateLetterInput(const char letter[]) {
  int lengthArray = sizeof(&letter) / 8;

  // WARNING: Este if no funciona correctamente, ya que si se ingresa una letra
  // funciona pero si se ingresa mas de una letra sigue funcionando, lo cual no
  // deberia ser asi ya que solo debe de recibir una letra

  // Check if we have only one letter
  if (lengthArray != 1) {
    return 0;
  } else {
    // Check if the letter is in the correct range (A-Z)
    if ((letter[0] >= 'A' && letter[0] <= 'Z') ||
        (letter[0] >= 'a' && letter[0] <= 'z')) {
      return 1;
    } else {
      return 0;
    }
  }
};

// Function to validate the entered number
int ValidateNumberInput(long int numeroValidar) {
  // Check if the number is in the correct range (0-99999999)
  if (numeroValidar <= 0 || numeroValidar >= pow(10, 8)) {
    return 0;
  } else {
    return 1;
  }
};

// Function to perform the validation of code
int CodeReader(const long int *number, const char *letra) {
  // Array with the correct values
  char validLetter[] = "TRWAGMYFPDXBNJZSQVHLCKE";

  // Calculate the module
  int module = *number % 23;

  // Find the letter in the array
  char letter = validLetter[module];

  // Check if the letter is correct
  if (letter == letra[0]) {
    printf("La letra ingresada es correcta al compararla con el resultado de "
           "la operacion \n");
    return 1;
  } else {
    printf("La letra ingresada no es correcta al compararla con el resultado "
           "de la operacion \n");
    return 0;
  }
}

// Main Function
int main(void) {
  // Variables
  long int numero;
  char letra[10];

  // Number Input
  printf("Ingresa los numeros correspondientes a tu codigo:");
  scanf("%ld", &numero);

  // Number Validation
  if (ValidateNumberInput(numero)) {
    printf("Tu codigo numerico es correcto \n");
  } else {
    printf("Tu codigo numerico no es correcto\n");
    return 0;
  }

  // Letter Input
  printf("Ingresa la letra correspondiente a tu codigo: ");
  scanf("%s", letra);

  // Letter Validation
  if (ValidateLetterInput(letra)) {
    printf("Tu letra es correcta \n");
  } else {
    printf("Tu letra no es correcta \n");
    return 0;
  }

  // Code Validation
  CodeReader(&numero, letra);
}
