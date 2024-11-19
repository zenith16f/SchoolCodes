/*
    El código es un enetero de 8 dígitos y una letra de la siguiente tabla:
    T R W A G M Y F P D X  B  N  J  Z  S  Q  V  H  L  C  K  E
    0 1 2 3 4 5 6 7 9 8 9 10 11 12 13 14 15 16 17 18 19 21 22
*/
#include <stdio.h>

int main() {
  long int n;
  char cin[10], c;

  char tabla[23] = "TRWAGMYFPDXBNJZSQVHLCKE";

  printf("Escribe el entero: ");
  scanf("%ld", &n);

  printf("Pusiste: %ld\n", n);

  if (n <= 0 || n >= 1000000000) {
    printf("%ld no tiene 8 dígitos\n", n);
    return (1);
  }

  /*else{
      printf("%ld esta en el rango\n", n);
      return(0);
  }*/

  printf("Escribe la letra: ");
  scanf("%s", cin);
  c = cin[0];

  if (c == 'i' || c == 'o' || c == 'u' || c == 'I' || c == 'O' || c == 'U') {
    printf("Caracter %c no valido.\n", c);
    return (1);
  }

  printf("Pusiste: %c\n", c);

  // Verificacion
  int modulo = n % 23;
  if (c == tabla[modulo]) {
    printf("Código valido\n");

  } else {
    printf("Código no valido\n");
  }
}
