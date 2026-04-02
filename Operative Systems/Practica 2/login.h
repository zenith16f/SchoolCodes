#ifndef LOGIN_H
#define LOGIN_H

#include <ctype.h>
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Defines
#define MAX_USER 32
#define MAX_PASS 64
#define MAX_HASH 65 /* SHA-256 produce 64 hex chars + '\0' */
#define MAX_USUARIOS 100
#define ARCHIVO_USUARIOS "usuarios.dat"

// Colores
#define COLOR_FONDO 1
#define COLOR_TITULO 2
#define COLOR_INPUT 3
#define COLOR_ERROR 4
#define COLOR_EXITO 5
#define COLOR_MENU 6
#define COLOR_BORDE 7

// Structs
typedef struct {
  char usuario[MAX_USER];
  char hash[MAX_HASH];
} Usuario;

// Funciones
// cifrado.c
void Sha256String(const char *entrada, char *salida);

// archivo.c
int CargarUsuarios(Usuario *lista, int max);
int GuardarUsuario(const Usuario *usr);
int BuscarUsuario(const char *nombre, Usuario *lista, int total,
                  Usuario *encontrado);

// interfaz.c
void InicializarColores(void);
void DibujarMarco(WINDOW *win, const char *titulo);
void MostrarTitulo(WINDOW *win, int fila);
void ObtenerTexto(WINDOW *win, int fila, int col, char *buffer, int max,
                  int oculto);
int MostrarMenuPrincipal(void);
void MostrarMensaje(WINDOW *win, int fila, const char *msg, int tipo_color);
void PantallaLogin(Usuario *lista, int total);
void PantallaRegistro(Usuario *lista, int *total);
void PantallaBienvenida(const char *usuario);

// Validacion.c
int ValidarUsuario(const char *usuario);
int ValidarContrasena(const char *contrasena);

#endif
