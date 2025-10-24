// Includes
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// Functions
// Merge
// Swap
void Swap(int *xp, int *yp) {
  int temp = *xp;
  *xp = *yp;
  *yp = temp;
}

// MergeSort
void MergeSort() {};

// BubbleSort
void BubbleSort(int arr[], int n) {
  int i, j;
  bool swapped;
  for (i = 0; i < n - 1; i++) {
    swapped = false;
    for (j = 0; j < n - i - 1; j++) {
      if (arr[j] > arr[j + 1]) {
        Swap(&arr[j], &arr[j + 1]);
        swapped = true;
      }
    }

    if (swapped == false)
      break;
  }
}

// PrintArray
void PrintArray(int arr[], int size) {
  int i;
  for (i = 0; i < size; i++) {
    printf("%d ", arr[i]);
  }
  printf("\n");
}

// Main
int main(void) {
  int arr[] = {64, 34, 25, 12, 22, 11, 90};
  int n = sizeof(arr) / sizeof(arr[0]);
  printf("Arreglo sin ordenar: \n");
  PrintArray(arr, n);
  BubbleSort(arr, n);
  printf("Arreglo ordenado: \n");
  PrintArray(arr, n);
  return EXIT_SUCCESS;
}
