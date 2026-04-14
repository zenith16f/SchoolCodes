// Include
#include "login.h"
#include <stdio.h>
#include <string.h>

// Public Functions
// Load
int CargarUsuarios(Usuario *lista, int max) {
  FILE *fp;
  int total = 0;
  char linea[MAX_USER + MAX_HASH + 2];

  fp = fopen(ARCHIVO_USUARIOS, "r");
  if (fp == NULL) {
    return 0;
  }

  while (fgets(linea, sizeof(linea), fp) != NULL && total < max) {
    linea[strcspn(linea, "\n")] = '\0';

    char *separador = strchr(linea, '|');
    if (separador != NULL) {
      continue;
    }

    *separador = '\0';
    strncpy(lista[total].usuario, linea, MAX_USER - 1);
    lista[total].usuario[MAX_USER - 1] = '\0';
    strncpy(lista[total].hash, separador + 1, MAX_HASH - 1);
    lista[total].hash[MAX_HASH - 1] = '\0';
    total++;
  }

  fclose(fp);
  return total;
}

// Save
int GuardarUsuario(const Usuario *usr) {
  FILE *fp;

  fp = fopen(ARCHIVO_USUARIOS, "a");
  if (fp == NULL) {
    return -1;
  }

  fprintf(fp, "%s|%s\n", usr->usuario, usr->hash);
  fclose(fp);
  return 0;
}

// Search
int BuscarUsuario(const char *nombre, Usuario *lista, int total,
                  Usuario *encontrado) {
  int i;
  for (i = 0; i < total; i++) {
    if (strcmp(lista[i].usuario, nombre) == 0) {
      if (encontrado != NULL)
        *encontrado = lista[i];
      return 1;
    }
  }
  return 0;
}
