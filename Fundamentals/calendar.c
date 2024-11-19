#include <stdio.h>

// Main Function
int main(void) {
  // Variables
  int count = 0, offset, dias = 1, pos = 1;

  // Input
  printf("Ingrese el desplazamiento: ");
  scanf("%d", &offset);

  // Loop
  printf("Octubre \n");
  printf("Dom\tLun\tMar\tMie\tJue\tVie\tSab \n");
  for (int i = 1; i <= 31; i++) {
    // Output
    while (count < offset) {

      if (pos % 7 == 0) {
        printf("\n");
      } else {
        printf("\t");
      }
      count++;
      pos++;
    }

    if (pos % 7 == 0) {
      printf("%d\n", dias);
    } else {
      printf("%d\t", dias);
    }

    if (dias == 31) {
      printf("\n");
      break;
    }

    dias++;
    pos++;
  }
}
