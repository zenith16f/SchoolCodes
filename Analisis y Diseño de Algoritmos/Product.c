#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Functions
// Pow function
long long potencia(int base, int exp){
	long long result = 1;
	for(int i = 0; i < exp; i++){
		result *= base;
	}
	return result;
}
// Product of two integers
long long multiplicar(long long x, long long y, int n){
	if(n== 1){
		return x * y;
	}

	int mid = n / 2;
	long long divisor = potencia(10, mid);

	long long a = x / divisor;
	long long b = x % divisor;

	long long c = y / divisor;
	long long d = y % divisor;

	long long A = multiplicar(a, c, mid);
	long long B = multiplicar(a, d, mid);
	long long C = multiplicar(b, c, mid);
	long long D = multiplicar(b, d, mid);

	
	return (A * potencia(10, n)) + ((B + C) * potencia(10, mid)) + D;
}
// Main
int main() {
	long long x=4312;
	long long y =2131;
	int n = 4;

	// Classic multiplication
	long long classicProduct = x * y;
	printf("El producto es (Multiplicacion clasica): %lld\n", classicProduct);

	printf("El producto es (Multiplicacion divide y venceras):" );
	long long resultado = multiplicar(x, y, n);
	printf("%lld\n", resultado);
	return 0;
}
