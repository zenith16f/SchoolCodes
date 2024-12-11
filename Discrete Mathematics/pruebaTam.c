#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int main(int argc, char *argv[]) {

	printf("int: %d\n", sizeof(int));
	printf("long: %d\n", sizeof(long));
	printf("long long: %d\n", sizeof(long long));
	printf("uint64_t: %d\n", sizeof(uint64_t));

	printf("INT_MAX: %d\n", INT_MAX);
	printf("LONG_MAX: %ld\n", LONG_MAX);
	printf("LLONG_MAX: %lld\n", LLONG_MAX);
	printf("UINT64_MAX: %lu\n", UINT64_MAX);


	return 0;
	
}
