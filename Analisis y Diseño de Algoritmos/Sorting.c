// Includes
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// Functions
// Merge
void Merge(int arr[], int inicio, int medio, int fin) {
  int i, j, k;
  int n1 = medio - inicio + 1;
  int n2 = fin - medio;
  int izq[n1], der[n2];

  for (i = 0; i < n1; i++)
    izq[i] = arr[inicio + i];

  for (j = 0; j < n2; j++)
    der[j] = arr[medio + 1 + j];

  i = 0;
  j = 0;
  k = inicio;

  while (i < n1 && j < n2) {
    if (izq[i] <= der[j]) {
      arr[k] = izq[i];
      i++;
    } else {
      arr[k] = der[j];
      j++;
    }
    k++;
  }

  while (i < n1) {
    arr[k] = izq[i];
    i++;
    k++;
  }

  while (j < n2) {
    arr[k] = der[j];
    j++;
    k++;
  }
}
// Swap
void Swap(int *xp, int *yp) {
  int temp = *xp;
  *xp = *yp;
  *yp = temp;
}

// MergeSort
void MergeSort(int arr[], int inicio, int fin) {
  if (inicio < fin) {

    int medio = (inicio + fin) / 2;

    MergeSort(arr, inicio, medio);
    MergeSort(arr, medio + 1, fin);

    Merge(arr, inicio, medio, fin);
  }
};

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
  int arrBubble[] = {20, 34, 12, 5, 67, 23, 1, 89};
  int nBubble = sizeof(arrBubble) / sizeof(arrBubble[0]);
  int arrMerge[] = {300, 150, 400, 250, 100, 350, 200, 50};
  int nMerge = sizeof(arrMerge) / sizeof(arrMerge[0]);
  printf("Arreglos sin ordenar: \n");
  printf("Bubble Sort: \n");
  PrintArray(arrBubble, nBubble);
  printf("Merge Sort: \n");
  PrintArray(arrMerge, nMerge);
  BubbleSort(arrBubble, nBubble);
  printf("Arreglo ordenado (Bubble Sort): \n");
  PrintArray(arrBubble, nBubble);
  printf("Arreglo ordenado (Merge Sort): \n");
  MergeSort(arrMerge, 0, nMerge - 1);
  PrintArray(arrMerge, nMerge);
  return EXIT_SUCCESS;
}
