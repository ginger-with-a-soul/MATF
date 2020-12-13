#include <stdio.h>
#include <stdlib.h>

void error();
void print_bits(unsigned x);
unsigned change(unsigned x);

void error(){
	fprintf(stderr, "-1\n");
	exit(EXIT_FAILURE);
}

void print_bits(unsigned x){
	unsigned mask = 1 << (sizeof(unsigned)*8 - 1);

	while(mask){
		if(x & mask){
			printf("1");
		}
		else{
			printf("0");
		}

		mask >>= 1;
	}
	printf("\n");
}

unsigned change(unsigned x){
	unsigned mask = -1 << sizeof(unsigned)*8 - 4;
	x ^= mask;
	mask = 15;
	mask = ~mask;
	x &= mask;
	mask = 9;
	x |= mask;
	return x;
}

int main(){
	unsigned x;
	scanf("%u", &x);
	if(x < 0){
		error();
	}

	printf("%u\n", change(x));

	return 0;
}