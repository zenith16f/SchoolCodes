#include <stdio.h>

void copiaCadena(char *src, char *dest) {
  for (int i = 0; src[i] != '\0'; i++) {
    // printf("%c", src[i]);
    dest[i] = src[i];
  }
}

void copiaCadenaV2(char *src, char *dest) {
  int i = 0;
  while (src[i] != '\0') {
    dest[i] = src[i];
    i++;
  }
}

void copiaCadenaV3(char *src, char *dest) {
  int i = 0;
  while (*(src + i) != '\0') {
    *(dest + i) = *(src + i);
    i++;
  }
}

void copiaCadenaV4(char *src, char *dest) {
  int i = 0;
  while ((*(dest + i) = *(src + i)) != '\0') {
    i++;
  }
}

void copiaCadenaV5(char *src, char *dest) {
  while ((*dest = *src) != '\0') {
    src++;
    dest++;
  }
}

void copiaCadenaV6(char *src, char *dest) {
  while ((*dest++ = *src++) != '\0')
    ;
}

int main() {
  char a[14] = "Marco Antonio", b[14];

  copiaCadena(a, b);
  printf("COPIA V1\n");
  printf("Cadena original: %s\n", a);
  printf("Cadena copiada: %s\n", b);

  printf("\nCOPIA V2\n");
  copiaCadenaV2(a, b);
  printf("Cadena original: %s\n", a);
  printf("Cadena copiada: %s\n", b);

  printf("\nCOPIA V3\n");
  copiaCadenaV3(a, b);
  printf("Cadena original: %s\n", a);
  printf("Cadena copiada: %s\n", b);

  printf("\nCOPIA V4\n");
  copiaCadenaV4(a, b);
  printf("Cadena original: %s\n", a);
  printf("Cadena copiada: %s\n", b);

  printf("\nCOPIA V5\n");
  copiaCadenaV5(a, b);
  printf("Cadena original: %s\n", a);
  printf("Cadena copiada: %s\n", b);

  printf("\nCOPIA V6\n");
  copiaCadenaV6(a, b);
  printf("Cadena original: %s\n", a);
  printf("Cadena copiada: %s\n", b);
  return 0;
}
