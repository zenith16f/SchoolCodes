# Makefile - Sistema de inicio de sesión con ncurses
# Práctica 2 - Sistemas Operativos - ESCOM IPN
# Equipo: Cuellar, Guzmán, Macías, Palomo - Grupo 4CV4

CC      = gcc
CFLAGS  = -Wall -Wextra -pedantic -std=c99
LDFLAGS = -lncurses
TARGET  = login
SRCS    = main.c cifrado.c archivo.c interfaz.c validacion.c
OBJS    = $(SRCS:.c=.o)

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.c login.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET) usuarios.dat
