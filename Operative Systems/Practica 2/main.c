// Include
#include "login.h"
#include <ncurses.h>

// Main Function
int main(void) {
  Usuario lista[MAX_USUARIOS];
  int total, opcion;
  // Cargar Usuarios Existentes
  total = CargarUsuarios(lista, MAX_USUARIOS);

  // NCURSES
  initscr();
  cbreak();
  noecho();
  curs_set(0);
  keypad(stdscr, TRUE);

  if (has_colors())
    InicializarColores();

  // Menu Principal
  do {
      opcion = MostrarMenuPrincipal();

      switch (opcion) {
          case 1:
              PantallaLogin(lista, total);
              break;
          case 2:
              PantallaRegistro(lista, &total);
              break;
          case 3:
              break;
      }
  } while (opcion != 3);

  endwin();

  return 0;
}
