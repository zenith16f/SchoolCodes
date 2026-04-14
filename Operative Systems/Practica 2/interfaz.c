// Include
#include "login.h"

// Functions
// Inicializar Colores
void InicializarColores(void) {
  start_color();
  use_default_colors();

  init_pair(COLOR_FONDO, COLOR_WHITE, COLOR_BLACK);
  init_pair(COLOR_TITULO, COLOR_CYAN, COLOR_BLACK);
  init_pair(COLOR_INPUT, COLOR_WHITE, COLOR_BLUE);
  init_pair(COLOR_ERROR, COLOR_RED, COLOR_BLACK);
  init_pair(COLOR_EXITO, COLOR_GREEN, COLOR_BLACK);
  init_pair(COLOR_MENU, COLOR_YELLOW, COLOR_BLACK);
  init_pair(COLOR_BORDE, COLOR_CYAN, COLOR_BLACK);
}

// DibujarMarco
void DibujarMarco(WINDOW *win, const char *titulo) {
  int ancho;

  wattron(win, COLOR_PAIR(COLOR_BORDE));
  box(win, 0, 0);
  wattroff(win, COLOR_PAIR(COLOR_BORDE));

  if (titulo != NULL) {
    ancho = getmaxx(win);
    wattron(win, COLOR_PAIR(COLOR_TITULO) | A_BOLD);
    mvwprintw(win, 0, (ancho - strlen(titulo) - 4) / 2, "[ %s ]", titulo);
    wattroff(win, COLOR_PAIR(COLOR_TITULO) | A_BOLD);
  }
}

// MostrarTitulo
void MostrarTitulo(WINDOW *win, int fila) {
  int ancho = getmaxx(win);
  const char *lineas[] = {"",
                          "     SISTEMA DE INICIO DE SESION           ",
                          "     Practica 2 - Sistemas Operativos      ",
                          "     ESCOM - IPN  Grupo 4CV4               ",
                          ""};
  int i, total = 5;

  wattron(win, COLOR_PAIR(COLOR_TITULO) | A_BOLD);
  for (i = 0; i < total; i++) {
    mvwprintw(win, fila + i, (ancho - 45) / 2, "%s", lineas[i]);
  }
  wattroff(win, COLOR_PAIR(COLOR_TITULO) | A_BOLD);
}

// ObtenerTexto
void ObtenerTexto(WINDOW *win, int fila, int col, char *buffer, int max,
                  int oculto) {
  int ch, pos = 0;
  int ancho_campo = max < 30 ? max : 30;
  int i;

  /* Dibujar campo de entrada con fondo azul */
  wattron(win, COLOR_PAIR(COLOR_INPUT));
  for (i = 0; i < ancho_campo; i++)
    mvwaddch(win, fila, col + i, ' ');
  wattroff(win, COLOR_PAIR(COLOR_INPUT));

  wmove(win, fila, col);
  wrefresh(win);

  curs_set(1);
  noecho();
  keypad(win, TRUE);

  while (1) {
    ch = wgetch(win);

    if (ch == '\n' || ch == KEY_ENTER)
      break;

    if ((ch == KEY_BACKSPACE || ch == 127 || ch == 8) && pos > 0) {
      pos--;
      buffer[pos] = '\0';

      /* Redibujar campo limpio */
      wattron(win, COLOR_PAIR(COLOR_INPUT));
      for (i = 0; i < ancho_campo; i++)
        mvwaddch(win, fila, col + i, ' ');
      wattroff(win, COLOR_PAIR(COLOR_INPUT));

      /* Mostrar texto actualizado */
      wattron(win, COLOR_PAIR(COLOR_INPUT));
      for (i = 0; i < pos; i++)
        mvwaddch(win, fila, col + i, oculto ? '*' : buffer[i]);
      wattroff(win, COLOR_PAIR(COLOR_INPUT));

      wmove(win, fila, col + pos);
    } else if (pos < max - 1 && ch >= 32 && ch <= 126) {
      buffer[pos] = (char)ch;
      pos++;
      buffer[pos] = '\0';

      wattron(win, COLOR_PAIR(COLOR_INPUT));
      mvwaddch(win, fila, col + pos - 1, oculto ? '*' : (char)ch);
      wattroff(win, COLOR_PAIR(COLOR_INPUT));
    }

    wrefresh(win);
  }

  curs_set(0);
  buffer[pos] = '\0';
}

// MostrarMensaje
void MostrarMensaje(WINDOW *win, int fila, const char *msg, int tipo_color) {
  int ancho = getmaxx(win);
  int col = (ancho - strlen(msg)) / 2;

  if (col < 1)
    col = 1;

  wattron(win, COLOR_PAIR(tipo_color) | A_BOLD);
  mvwprintw(win, fila, col, "%s", msg);
  wattroff(win, COLOR_PAIR(tipo_color) | A_BOLD);
  wrefresh(win);
}

// MostrarMenuPrincipal
int MostrarMenuPrincipal(void) {
  int filas, cols, ch, opcion = 1;
  WINDOW *win;

  getmaxyx(stdscr, filas, cols);
  win = newwin(22, 50, (filas - 22) / 2, (cols - 50) / 2);

  keypad(win, TRUE);
  curs_set(0);

  while (1) {
    werase(win);
    DibujarMarco(win, "MENU PRINCIPAL");
    MostrarTitulo(win, 2);

    /* Opciones del menú */
    int fila_base = 9;
    const char *opciones[] = {"  Iniciar Sesion  ", "  Registrarse     ",
                              "  Salir           "};
    int i;

    for (i = 0; i < 3; i++) {
      if (i + 1 == opcion) {
        wattron(win, COLOR_PAIR(COLOR_MENU) | A_REVERSE | A_BOLD);
      } else {
        wattron(win, COLOR_PAIR(COLOR_FONDO));
      }
      mvwprintw(win, fila_base + i * 2, 15, "%s", opciones[i]);
      wattroff(win, COLOR_PAIR(COLOR_MENU) | A_REVERSE | A_BOLD);
      wattroff(win, COLOR_PAIR(COLOR_FONDO));
    }

    /* Instrucciones */
    wattron(win, COLOR_PAIR(COLOR_BORDE));
    mvwprintw(win, 17, 5, "Use las flechas y ENTER para seleccionar");
    wattroff(win, COLOR_PAIR(COLOR_BORDE));

    wrefresh(win);

    ch = wgetch(win);
    switch (ch) {
    case KEY_UP:
      if (opcion > 1)
        opcion--;
      break;
    case KEY_DOWN:
      if (opcion < 3)
        opcion++;
      break;
    case '\n':
    case KEY_ENTER:
      delwin(win);
      return opcion;
    }
  }
}

// PantallaLogin
void PantallaLogin(Usuario *lista, int total) {
  int filas, cols;
  char usuario[MAX_USER] = {0};
  char contrasena[MAX_PASS] = {0};
  char hash[MAX_HASH] = {0};
  Usuario encontrado;
  WINDOW *win;

  getmaxyx(stdscr, filas, cols);
  win = newwin(18, 50, (filas - 18) / 2, (cols - 50) / 2);
  keypad(win, TRUE);

  werase(win);
  DibujarMarco(win, "INICIAR SESION");

  /* Etiquetas */
  wattron(win, COLOR_PAIR(COLOR_FONDO) | A_BOLD);
  mvwprintw(win, 3, 4, "Usuario:");
  mvwprintw(win, 6, 4, "Contrasena:");
  wattroff(win, COLOR_PAIR(COLOR_FONDO) | A_BOLD);

  wrefresh(win);

  /* Leer usuario */
  ObtenerTexto(win, 4, 4, usuario, MAX_USER, 0);

  /* Validar usuario */
  if (!ValidarUsuario(usuario)) {
    MostrarMensaje(win, 10, "Usuario invalido (min 3 chars, alfanumerico)",
                   COLOR_ERROR);
    MostrarMensaje(win, 12, "Presione cualquier tecla para continuar...",
                   COLOR_BORDE);
    wgetch(win);
    delwin(win);
    return;
  }

  /* Leer contraseña (oculta con asteriscos) */
  ObtenerTexto(win, 7, 4, contrasena, MAX_PASS, 1);

  /* Validar contraseña */
  if (!ValidarContrasena(contrasena)) {
    MostrarMensaje(win, 10, "Contrasena invalida (min 4 caracteres)",
                   COLOR_ERROR);
    MostrarMensaje(win, 12, "Presione cualquier tecla para continuar...",
                   COLOR_BORDE);
    wgetch(win);
    delwin(win);
    return;
  }

  /* Cifrar contraseña con SHA-256 */
  Sha256String(contrasena, hash);

  /* Limpiar contraseña en texto plano de la memoria */
  memset(contrasena, 0, MAX_PASS);

  /* Buscar usuario y verificar hash */
  if (BuscarUsuario(usuario, lista, total, &encontrado) &&
      strcmp(encontrado.hash, hash) == 0) {
    MostrarMensaje(win, 10, "Inicio de sesion exitoso!", COLOR_EXITO);
    wrefresh(win);
    napms(1000);
    delwin(win);
    PantallaBienvenida(usuario);
  } else {
    MostrarMensaje(win, 10, "Usuario o contrasena incorrectos", COLOR_ERROR);
    MostrarMensaje(win, 12, "Presione cualquier tecla para continuar...",
                   COLOR_BORDE);
    wgetch(win);
    delwin(win);
  }
}

// PantallaRegistro
void PantallaRegistro(Usuario *lista, int *total) {
  int filas, cols;
  char usuario[MAX_USER] = {0};
  char contrasena[MAX_PASS] = {0};
  char confirmar[MAX_PASS] = {0};
  char hash[MAX_HASH] = {0};
  Usuario nuevo;
  WINDOW *win;

  getmaxyx(stdscr, filas, cols);
  win = newwin(20, 50, (filas - 20) / 2, (cols - 50) / 2);
  keypad(win, TRUE);

  werase(win);
  DibujarMarco(win, "REGISTRO DE USUARIO");

  /* Etiquetas */
  wattron(win, COLOR_PAIR(COLOR_FONDO) | A_BOLD);
  mvwprintw(win, 3, 4, "Nombre de usuario:");
  mvwprintw(win, 6, 4, "Contrasena:");
  mvwprintw(win, 9, 4, "Confirmar contrasena:");
  wattroff(win, COLOR_PAIR(COLOR_FONDO) | A_BOLD);

  wrefresh(win);

  /* Leer usuario */
  ObtenerTexto(win, 4, 4, usuario, MAX_USER, 0);

  if (!ValidarUsuario(usuario)) {
    MostrarMensaje(win, 13, "Usuario invalido (3-31 chars, alfanumerico)",
                   COLOR_ERROR);
    MostrarMensaje(win, 15, "Presione cualquier tecla para continuar...",
                   COLOR_BORDE);
    wgetch(win);
    delwin(win);
    return;
  }

  /* Verificar que no exista */
  if (BuscarUsuario(usuario, lista, *total, NULL)) {
    MostrarMensaje(win, 13, "El usuario ya existe", COLOR_ERROR);
    MostrarMensaje(win, 15, "Presione cualquier tecla para continuar...",
                   COLOR_BORDE);
    wgetch(win);
    delwin(win);
    return;
  }

  /* Leer contraseña */
  ObtenerTexto(win, 7, 4, contrasena, MAX_PASS, 1);

  if (!ValidarContrasena(contrasena)) {
    MostrarMensaje(win, 13, "Contrasena invalida (min 4 caracteres)",
                   COLOR_ERROR);
    MostrarMensaje(win, 15, "Presione cualquier tecla para continuar...",
                   COLOR_BORDE);
    wgetch(win);
    delwin(win);
    return;
  }

  /* Confirmar contraseña */
  ObtenerTexto(win, 10, 4, confirmar, MAX_PASS, 1);

  if (strcmp(contrasena, confirmar) != 0) {
    MostrarMensaje(win, 13, "Las contrasenas no coinciden", COLOR_ERROR);
    MostrarMensaje(win, 15, "Presione cualquier tecla para continuar...",
                   COLOR_BORDE);
    wgetch(win);
    memset(contrasena, 0, MAX_PASS);
    memset(confirmar, 0, MAX_PASS);
    delwin(win);
    return;
  }

  /* Cifrar y guardar */
  Sha256String(contrasena, hash);
  memset(contrasena, 0, MAX_PASS);
  memset(confirmar, 0, MAX_PASS);

  strncpy(nuevo.usuario, usuario, MAX_USER - 1);
  strncpy(nuevo.hash, hash, MAX_HASH - 1);

  if (GuardarUsuario(&nuevo) == 0) {
    lista[*total] = nuevo;
    (*total)++;
    MostrarMensaje(win, 13, "Usuario registrado exitosamente!", COLOR_EXITO);
  } else {
    MostrarMensaje(win, 13, "Error al guardar el usuario", COLOR_ERROR);
  }

  MostrarMensaje(win, 15, "Presione cualquier tecla para continuar...",
                 COLOR_BORDE);
  wgetch(win);
  delwin(win);
}

// PantallaBienvenida
void PantallaBienvenida(const char *usuario) {
  int filas, cols;
  WINDOW *win;

  getmaxyx(stdscr, filas, cols);
  win = newwin(14, 50, (filas - 14) / 2, (cols - 50) / 2);

  werase(win);
  DibujarMarco(win, "BIENVENIDO");

  wattron(win, COLOR_PAIR(COLOR_EXITO) | A_BOLD);
  mvwprintw(win, 3, (50 - strlen("Bienvenido,") - strlen(usuario) - 1) / 2,
            "Bienvenido, %s", usuario);
  wattroff(win, COLOR_PAIR(COLOR_EXITO) | A_BOLD);

  wattron(win, COLOR_PAIR(COLOR_FONDO));
  mvwprintw(win, 5, 6, "Ha iniciado sesion correctamente.");
  mvwprintw(win, 6, 6, "Su contrasena fue cifrada con SHA-256");
  mvwprintw(win, 7, 6, "y almacenada de forma segura.");
  wattroff(win, COLOR_PAIR(COLOR_FONDO));

  MostrarMensaje(win, 10, "Presione cualquier tecla para salir...",
                 COLOR_BORDE);
  wgetch(win);
  delwin(win);
}
