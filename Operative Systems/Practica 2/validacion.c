#include "login.h"

int ValidarUsuario(const char *usuario) {
  int i, len;

  if (usuario == NULL) {
    return 0;
  }

  len = strlen(usuario);
  if (len < 3 || len >= MAX_USER) {
    return 0;
  }

  for (i = 0; i < len; i++) {
    if (!isalnum((unsigned char)usuario[i]) && usuario[i] != '_')
      return 0;
  }

  return 1;
}

int ValidarContrasena(const char *contraseña) {
  int len;

  if (contraseña == NULL) {
    return 0;
  }

  len = strlen(contraseña);

  if (len < 4 || len >= MAX_PASS) {
    return 0;
  }

  if (strchr(contraseña, '|') != NULL) {
    return 0;
  }

  return 1;
}
