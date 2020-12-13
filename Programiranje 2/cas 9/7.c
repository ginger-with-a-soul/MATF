#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void error();
unsigned invert_bits(unsigned x, int p, int n);
void print_bits(unsigned x);

void rrror(){
	fprintf(stderr, "-1\n");
	exit(EXIT_FAILURE);
}

unsigned invert_bits(unsigned x, int p, int n){
	unsigned mask = 1 << p;
	for(int i = p; i < p+n; i++){
		if(x & mask){
			x -= pow(2, i);
		}
		else{
			x += pow(2, i);
		}
		mask <<= 1;
	}
	return x;
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

int main(){

	unsigned x, inv_x;
	int p, n;
	scanf("%u %i %i", &x, &n, &p);
	if(n < 0 || p < 0 || n+p >= (sizeof(unsigned)*8)){
		error();
	}
	inv_x = invert_bits(x, p, n);
	print_bits(x);
	print_bits(inv_x);

	return 0;
}