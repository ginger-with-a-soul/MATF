#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void error();
void print_bits(unsigned x);
unsigned mirror(unsigned x);

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

unsigned mirror(unsigned x){
	unsigned size = (sizeof(unsigned))*8;
	unsigned new_x = 0;
	unsigned mask = 1 << size - 1;
	for(int power = 0; mask; power++){
		if(x & mask){
			new_x += pow(2, power);
		}
		mask >>= 1;
	}
	return new_x;
}

int main(){
	unsigned x;
	fscanf(stdin, "%u", &x);
	print_bits(x);
	x = mirror(x);
	print_bits(x);
	return 0;
}