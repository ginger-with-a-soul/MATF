#include <stdio.h>
#include <stdlib.h>

void error();
unsigned inv_every_3_if_0(unsigned x);
void print_bits(unsigned x);

void error(){
	fprintf(stderr, "-1\n");
	exit(EXIT_FAILURE);
}

unsigned inv_every_3_if_0(unsigned x){
	unsigned mask = 4;
	unsigned size = sizeof(unsigned)*8 - 1;
	for(int i = 2; i <= size; i += 3, mask <<= 3){
		if(mask & x){
			continue;
		}
		else{
			x |= mask;
		}
	}

	return x;
}

void print_bits(unsigned x){
	unsigned mask = 1;
	unsigned size = sizeof(unsigned)*8 - 1;
	for(int i = 0; i <= size; i++, mask <<= 1){
		if(x & mask){
			printf("1");
		}
		else{
			printf("0");
		}
	}

	fprintf(stdout, "\n");
}

int main(){

	unsigned x;

	scanf("%u", &x);
	if(x < 0){
		error();
	}

	x = inv_every_3_if_0(x);
	printf("%u\n", x);

	return 0;
}