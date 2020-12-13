#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void error();
unsigned set_bits(unsigned x, int p, int n, unsigned y);
void print_bits(unsigned x);

void error(){
	fprintf(stderr, "-1\n");
	exit(EXIT_FAILURE);
}

unsigned set_bits(unsigned x, int p, int n, unsigned y){
	unsigned mask1 = 1, mask2 = 1 << p;
	unsigned f_call = x;
	for(int i = p; i <= p+n; i++){
		if((y & mask1) && !(x & mask2)){
			f_call += pow(2, i);
		}
		mask1 <<= 1;
		mask2 <<= 1;
	}

	return f_call;
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
	unsigned x, y, f_call;
	int p, n;
	scanf("%u %u %i %i", &x, &y, &n, &p);
	if(p < 0 || n < 0 || p+n >= (sizeof(unsigned)*8)){
		error();
	}

	f_call = set_bits(x, p, n, y);

	print_bits(x);
	print_bits(y);
	print_bits(f_call);

	return 0;
}