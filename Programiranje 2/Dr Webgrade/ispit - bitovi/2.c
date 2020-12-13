#include <stdio.h>
#include <stdlib.h>

void error();
unsigned change_groups_of_bits(unsigned x);

void error(){
	fprintf(stderr, "-1\n");
	exit(EXIT_FAILURE);
}

void print_bits(unsigned x){
	unsigned mask = 1 << sizeof(unsigned)*8 - 1;
	while(mask){
		if(x & mask){
			printf("1");
		}
		else{
			printf("0");
		}
		mask >>= 1;
	}
	puts("");
}

unsigned change_groups_of_bits(unsigned x){
	unsigned mask = (~0 << 4);
	x &= mask;
	mask = 9;
	x |= mask;
	mask = (~0 << 28);
	x ^= mask;
	return x;
}
int main(){

	unsigned x;
	scanf("%u", &x);
	if(x < 0){
		error();
	}

	printf("%u\n", change_groups_of_bits(x));

	return 0;
}