# Makefile - Comunicación entre procesos padre-hijos


CC      = gcc
CFLAGS  = -Wall -Wextra -pedantic -std=c99
TARGET  = main
SRCS    = main.c semaforo.c memoria.c procesoHijo.c
OBJS    = $(SRCS:.c=.o)

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c definitions.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET) archivo_shm archivo_sem
