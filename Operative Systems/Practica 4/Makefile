CC = gcc
TARGET = practica4
SRC = hilos.c matriz.c main.c operaciones.c
OBJS = $(SRC:.c=.o)
CFLAGS = -Wall -Wextra -pedantic -std=c99
LDFLAGS = -lpthread

$(TARGET) : $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS) 

%.o : %.c logica.h	
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean

clean : 
	rm -f $(OBJS) $(TARGET)