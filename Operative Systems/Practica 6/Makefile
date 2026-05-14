# Makefile
CC = gcc
CFLAGS = -Wall -Wextra -pedantic -std=c99
LDFLAGS = -lpthread
# Módulos compartidos
COMUNES = semaforo.o memoria.o validacion.o archivo.o
.PHONY: all clean
all: servidor cliente
servidor: servidor.o $(COMUNES)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)
cliente: cliente.o $(COMUNES)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)
servidor.o: servidor.c comunes.h semaforo.h memoria.h
	$(CC) $(CFLAGS) -c $< -o $@
cliente.o: cliente.c comunes.h semaforo.h memoria.h validacion.h
	$(CC) $(CFLAGS) -c $< -o $@
semaforo.o: semaforo.c comunes.h
	$(CC) $(CFLAGS) -c $< -o $@
memoria.o: memoria.c comunes.h
	$(CC) $(CFLAGS) -c $< -o $@
validacion.o: validacion.c comunes.h
	$(CC) $(CFLAGS) -c $< -o $@
archivo.o: archivo.c archivo.h
	$(CC) $(CFLAGS) -c $< -o $@
clean:
	rm -f *.o servidor cliente ipc_shm ipc_sem frases.txt