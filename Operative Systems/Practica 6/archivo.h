#ifndef ARCHIVO_H
#define ARCHIVO_H

#include "comunes.h"

void formatoMensaje(pid_t cliente,char frase[], FILE *archivo);
int guardarFrase(pid_t cliente, char frase[]);
long historial();
long imprimirFrases(long cursor_actual);

#endif