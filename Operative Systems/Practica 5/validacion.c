/*
 * validacion.c
 */

#include "comunes.h"

int ContarPalabras(const char *cadena) {
  int contador = 0;
  int en_palabra = 0;
  int i;

  if (cadena == NULL)
    return 0;

  for (i = 0; cadena[i] != '\0'; i++) {
    if (cadena[i] != ' ' && cadena[i] != '\t' && cadena[i] != '\n') {
      if (!en_palabra) {
        contador++;
        en_palabra = 1;
      }
    } else {
      en_palabra = 0;
    }
  }

  return contador;
}

int ValidarFrase(const char *frase) {
  int palabras;

  if (frase == NULL)
    return 0;

  if (strlen(frase) == 0)
    return 0;

  if (strlen(frase) >= MAX_FRASE)
    return 0;

  palabras = ContarPalabras(frase);
  return (palabras == 10);
}
