#include <stdio.h>
#include <stdlib.h>

void error();
void print_bits(unsigned x);
unsigned izmeni(unsigned x);

void error(){
	fprintf(stderr, "-1\n");
	exit(EXIT_FAILURE);
}

void print_bits(unsigned x){
	unsigned mask = 1 << sizeof(unsigned)*8 - 1;
	while(mask){
		if(x & mask){
			fprintf(stdout, "1");
		}
		else{
			fprintf(stdout, "0");
		}
		mask >>= 1;
	}
	puts("");
}

unsigned izmeni(unsigned x){
	unsigned mask0 = 1;
	unsigned mask1 = 2;
	unsigned mask2 = 4;
	for(int i = 1; i < sizeof(unsigned)*8 - 2; i++, mask0 <<= 1, mask1 <<= 1, mask2 <<= 1){
		if(mask1 & x){
			if(!(mask0 & x) && !(mask2 & x)){
				x ^= mask1;
			}
		}
		else if(!(mask1 & x)){
			if((mask0 & x) && (mask2 &x)){
				x ^= mask1;
			}
		}
		else{
			continue;
		}

	}
	return x;
}

int main(){

	unsigned x;
	scanf("%u", &x);

	if(x < 0){
		error();
	}

	x = izmeni(x);
	
	printf("%u\n", x);

	return 0;
}