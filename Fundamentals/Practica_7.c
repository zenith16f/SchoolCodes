// Triangulo de Pascal
#include <stdio.h>
int fact(int n) {
  if (n <= 0)
    return 1;
  return n * fact(n - 1);
}

int combinaciones(int n, int k) { return fact(n) / (fact(n - k) * fact(k)); }

void imprime(int renglon) {
  for (int n = 0; n < renglon; n++) {
    for (int k = 0; k <= n; k++) {
      printf("%d  ", combinaciones(n, k));
    }
    printf("\n");
  }
}

int main() { imprime(6); }
