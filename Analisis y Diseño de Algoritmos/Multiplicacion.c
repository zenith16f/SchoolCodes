// Includes
#include <stdio.h>
#include <stdlib.h>

// Functions
// Funcion Iterativa
int multiplicacionIterativa(int numeroUno, int numeroDos) {
  int resultado, signo = 1;
  if (numeroUno < 0) {
    numeroUno = -numeroUno;
    signo = -signo;
  };

  if (numeroDos < 0) {
    numeroDos = -numeroDos;
    signo = -signo;
  };

  for (int i = 0; i < numeroDos; ++i) {
    resultado += numeroUno;
  };

  return resultado;
};

// Funcion Recursiva
int multiplicacionRecursiva(int numeroUno, int numeroDos) {
  if (numeroDos == 0) {
    return 0;
  }

  if (numeroDos > 0) {
    return numeroUno + multiplicacionRecursiva(numeroUno, numeroDos - 1);
  };

  return -multiplicacionRecursiva(numeroUno, -numeroDos);
}

// Funcion Recursiva (2)
int multiplicacionRecursiva2(int numeroUno, int numeroDos) {
  if (numeroDos == 0) {
    return 0;
  };

  if (numeroDos < 0) {
    return -multiplicacionRecursiva2(numeroUno, -numeroDos);
  };

  int half = multiplicacionRecursiva2(numeroUno, numeroDos / 2);
  int doble = half + half;
  if (numeroDos % 2 == 0) {
    return doble;
  } else {
    return doble + 1;
  };
};

// Main
int main(int argc, char *argv[]) { 

	// Variables
	int numeroUno = -7, numeroDos =5;

	// Calling
	printf("Multiplicacion Iterativa: %d * %d = %d \n", numeroUno,numeroDos,multiplicacionIterativa(numeroUno, numeroDos));
	
	printf("Multiplicacion Recursiva: %d * %d = %d \n", numeroUno,numeroDos,multiplicacionRecursiva(numeroUno, numeroDos));
	
	printf("Multiplicacion Recursiva (Segunda Forma): %d * %d = %d \n", numeroUno,numeroDos,multiplicacionRecursiva2(numeroUno, numeroDos));

	return EXIT_SUCCESS; 

}
