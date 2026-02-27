#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// Struct
typedef struct {
  char **items;
  int size;
  int capacity;
} ListaCadenas;

// Functions
// Longitud de una cadena
void longitud(char *a) {
  if (strlen(a) == 0) {
    printf("%d", 1);
    return;
  }
  printf("%d", strlen(a));
  return;
}

// Inversión de una cadena
char *invertir(char *a) {
  char *x = (char *)malloc((strlen(a) + 1) * sizeof(char));
  memcpy(x, a, strlen(a) + 1);
  char temp;
  for (char *k = x, *z = x + strlen(x) - 1; k < z; k++, z--) {
    temp = *k;
    *k = *z;
    *z = temp;
  }
  return x;
}

// Concatenación de dos cadenas
char *concatenar(char *a, char *b) {

  int l1 = strlen(a);
  int l2 = strlen(b);
  if (l1 == 0 && l2 == 0)
    return strdup("λ");

  char *z = (char *)malloc((l1 + l2 + 1) * sizeof(char));
  memcpy(z, a, l1);
  memcpy(z + l1, b, l2);
  z[l1 + l2] = '\0';
  return z;
}

// Prefijo optimizado de una cadena
void prefijos(char *a) {
  for (int i = 0; i <= strlen(a); i++) {
    printf("prefijo: %.*s \n", i, a);
  }
}

// Potencia de una cadena optimizada
char *potencia(char *a, int pt) {
  if (pt == 0)
    return strdup("λ");
  int sz = strlen(a);
  char *z;
  if (pt < 0) {
    z = invertir(a);
    pt *= -1;
  } else {
    z = a;
  }
  char *x = (char *)malloc(sizeof(char) * ((sz * pt) + 1));
  for (int i = 0; i < pt; i++) {
    memcpy(x + (sz * i), z, sz);
  }
  x[pt * sz] = '\0';
  if (z != a)
    free(z);

  return x;
}

// Subsecuencia de una cadena
void subsecuencias(char *a) {
  int l = strlen(a);
  if (l > 12) {
    printf("Error: No se aceptan cadenas mayores a 12 caracteres (%d "
           "ingresados)\n",
           l);
    return;
  }
  int mask = 1 << l;
  printf("subsecuencias: { %s", "λ");
  int pos = 0;
  char buff[l + 1];
  for (int i = 1; i < mask; i++) {
    pos = 0;
    for (int j = 0; j < l; j++) {
      if (i & (1 << j))
        buff[pos++] = a[j];
    }
    buff[pos] = '\0';
    printf(", %s", buff);
  }
  printf(" }\n");
}

// Sufijos
void sufix(char *k) {
  if (k == NULL || strlen(k) == 0) {
    printf("  λ\n");
    return;
  }
  int len = strlen(k);

  printf("Sufijos de \"%s\":\n", k);
  for (int i = 0; i < len; i++) {
    printf("  \"%s\"\n", k + i);
  }
  printf("  λ\n");
}

// Subcadenas
void subCadenas(char *k) {
  if (k == NULL || strlen(k) == 0) {
    printf("  λ\n");
    return;
  }
  int len = strlen(k);
  printf("Subcadenas de \"%s\":\n", k);
  for (int i = 0; i < len; i++) {
    for (int j = i + 1; j <= len; j++) {
      printf("  \"%.*s\"\n", j - i, k + i);
    }
  }
  printf("  λ\n");
}

// Add Cadenas
void addCadenatoList(ListaCadenas *lista, char *cadena) {
  if (lista->size == lista->capacity) {
    lista->capacity = (lista->capacity == 0) ? 4 : lista->capacity * 2;
    lista->items = realloc(lista->items, lista->capacity * sizeof(char *));
  }
  lista->items[lista->size++] = strdup(cadena);
}

// Ask Cadenas
void askCadena(ListaCadenas *lista) {
  char cadena[100];
  int otra = 1;
  regex_t regex;
  if (regcomp(&regex, "^[[:alnum:]]+$", REG_EXTENDED)) {
    printf("Si compilo");
    return;
  }

  while (otra) {
    printf("Ingrese una cadena: ");
    fgets(cadena, sizeof(cadena), stdin);
    cadena[strcspn(cadena, "\n")] = '\0';
    if (regexec(&regex, cadena, 0, NULL, 0) != 0) {
      printf("Error: La cadena solo puede ser alfanumerica \n");
      continue;
    }
    if (strlen(cadena) > 50) {
      printf("Error: La cadena excede los 50 caracteres (%lu ingresados)\n",
             strlen(cadena));
      continue;
    }

    addCadenatoList(lista, cadena);
    printf("Desea ingresar otra cadena? (1 para si, 0 para no): ");
    scanf("%d", &otra);
    getchar();
  }
}

// Get Cadenas
void getCadenas(ListaCadenas *lista) {
  printf("Cadenas ingresadas:\n");
  for (int i = 0; i < lista->size; i++) {
    printf("%d  \"%s\"\n", i + 1, lista->items[i]);
  }
}

// Select Option
char *selectOption(ListaCadenas *lista) {
  int opcion;
  do {
    printf("Selecciona una cadena (1-%d): ", lista->size);
    scanf("%d", &opcion);
    if (opcion < 1 || opcion > lista->size)
      printf("Opción inválida, intenta de nuevo.\n");
  } while (opcion < 1 || opcion > lista->size);
  return lista->items[opcion - 1];
}

// OperationMenu
void OperationsMenu(ListaCadenas *lista) {
  // Variables
  char display = 'y';
  int operacion, opcion = 0;
  while (display == 'y') {
    printf("Seleccione una operacion \n");
    printf("1. Concatenacion \n");
    printf("2. Potencia \n");
    printf("3. Prefijos \n");
    printf("4. Sufijos \n");
    printf("5. Subcadenas \n");
    printf("6. Subsecuencias \n");
    printf("7. Ingresar otra(s) cadenas\n");
    printf("0. Salir\n");
    scanf("%d", &operacion);

    switch (operacion) {
    case 0:
      operacion = 0;
      display = 'n';
      break;
    case 1:
      getCadenas(lista);
      char *resultadoConcat =
          concatenar(selectOption(lista), selectOption(lista));
      printf("Resultado de la concatenacion: %s\n", resultadoConcat);
      addCadenatoList(lista, resultadoConcat);
      free(resultadoConcat);
      break;
    case 2:
      getCadenas(lista);
      char *seleccionPot = selectOption(lista);
      // Validacion (Opcional)
      // if (strlen(seleccionPot) > 12) {
      //   printf("Error: La cadena \"%s\" tiene %lu caracteres.\n",
      //   seleccionPot,
      //          strlen(seleccionPot));
      //   printf("La potencia solo acepta cadenas de 12 caracteres o
      //   menos.\n"); break; // Regresa al menú sin ejecutar la operación
      // }

      printf("Ingresa la potencia a la que se busca elevar: ");
      int exponente;
      scanf("%d", &exponente);
      char *resultadoPotencia = potencia(seleccionPot, exponente);
      printf("Resultado de la potencia: %s\n", resultadoPotencia);
      addCadenatoList(lista, resultadoPotencia);
      free(resultadoPotencia);
      break;
    case 3:
      getCadenas(lista);
      prefijos(selectOption(lista));
      break;
    case 4:
      getCadenas(lista);
      sufix(selectOption(lista));

      break;
    case 5:
      getCadenas(lista);
      subCadenas(selectOption(lista));
      break;
    case 6:
      getCadenas(lista);
      char *seleccionSubsecuencia = selectOption(lista);

      // Validar que la cadena no exceda 12 caracteres
      if (strlen(seleccionSubsecuencia) > 12) {
        printf("Error: La cadena \"%s\" tiene %lu caracteres.\n",
               seleccionSubsecuencia, strlen(seleccionSubsecuencia));
        printf(
            "La subsecuencia solo acepta cadenas de 12 caracteres o menos.\n");
        break; // Regresa al menú sin ejecutar la operación
      }
      subsecuencias(seleccionSubsecuencia);
      break;
    case 7:
      getchar();
      askCadena(lista);
      break;
    default:
      printf("Selecciona una operacion correcta.");
      break;
    }

    getchar();
    if (operacion == 0) {
      printf("Saliendo del programa...");
    } else {

      printf("Ingresar otra operacion? (y/n)");
      getchar();
      scanf("%c", &display);
      if (display != 'y' && display != 'n') {
        printf("\nIngresa una opcion adecuada");
        display = 'y';
      };
    }
  }
}

// FreeLista
void freeLista(ListaCadenas *lista) {
  for (int i = 0; i < lista->size; i++)
    free(lista->items[i]);
  free(lista->items);
}

// Main
int main() {
  ListaCadenas lista = {NULL, 0, 0};
  askCadena(&lista);
  OperationsMenu(&lista);
  freeLista(&lista);
  return 0;
}
