// Includes
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// Functions
// Busqueda elemento minimo
void MinSearch(int arr[], int size) {
  int number, i = 0;
  number = arr[0];
  while (i < size) {
    if (number > arr[i]) {
      number = arr[i];
    };
    i++;
  };
  printf("El numero menor es: %d \n", number);
};

// Search for x element in array
bool SearchElement(int arr[], int n, int x) {
  int i = 0;
  while (i < n) {
    if (x == arr[i]) {
      return true;
    };
    i++;
  };
  return false;
};

// Search element in either array A or B
bool SearchElementIn(int A[], int B[], int n, int x) {
  int i = 0;
  while (i < n) {
    if (A[i] == x || B[i] == x) {
      return true;
    };
    i++;
  };
  return false;
};

// Search Common element in array A and B
bool SearchCommon(int A[], int B[], int n) {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (A[i] == B[j]) {
        return true;
      };
    };
  };
  return false;
};

// Search Duplicate in and array
bool SearchDuplicate(int A[], int n) {
  for (int i = 0; i < n; i++) {
    for (int j = i + 1; j < n; j++) {
      if (A[i] == A[j]) {
        return true;
      };
    };
  };
  return false;
};

// Function Caller
void FunctionCaller(int A[], int B[], int C[], int sizeA, int sizeB,
                    int sizeC) {
  int x = 22;
  if (SearchElement(A, sizeA, x)) {
    printf("El elemento %d se encuentra en el arreglo A \n", x);
  } else {
    printf("El elemento %d no se encuentra en el arreglo A \n", x);
  };

  if (SearchElementIn(A, B, sizeA < sizeB ? sizeA : sizeB, x)) {
    printf("El elemento %d se encuentra en el arreglo A o B \n", x);
  } else {
    printf("El elemento %d no se encuentra en el arreglo A o B \n", x);
  };

  if (SearchCommon(A, B, sizeA < sizeB ? sizeA : sizeB)) {
    printf("Existen elementos comunes entre los arreglos A y B \n");
  } else {
    printf("No existen elementos comunes entre los arreglos A y B \n");
  };

  if (SearchDuplicate(C, sizeC)) {
    printf("Existen elementos duplicados en el arreglo \n");
  } else {
    printf("No existen elementos duplicados en el arreglo \n");
  };
};

// Main
int main(void) {
  int A[] = {64, 34, 25, 12, 22, 11, 90};
  int B[] = {34, 23, 12, 43, 56, 21};
  int C[] = {1, 1, 2, 3, 4, 5, 6};

  int sizeA = sizeof(A) / sizeof(A[0]);
  int sizeB = sizeof(B) / sizeof(B[0]);
  int sizeC = sizeof(C) / sizeof(C[0]);

  FunctionCaller(A, B, C, sizeA, sizeB, sizeC);

  return EXIT_SUCCESS;
}
