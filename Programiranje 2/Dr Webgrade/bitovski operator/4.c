#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void error();
unsigned count(unsigned x);

void error(){
	fprintf(stderr, "-1\n");
	exit(EXIT_FAILURE);
}

unsigned count(unsigned x){
	unsigned mask, match = 0;
	for(int i = 0; i < sizeof(unsigned)*8; i++){
		mask = pow(2, i);
		if(!(x & mask)){
			mask <<= 1;
			if(x & mask){
				mask <<= 1;
				i += 1;
				if(!(x & mask)){
					match++;
				}
			}
		}
	}
	return match;
}

int main(){
	unsigned x;
	scanf("%u", &x);
	if(x < 0){
		error();
	}
	x = count(x);
	printf("%u\n", x);
	return 0;
}