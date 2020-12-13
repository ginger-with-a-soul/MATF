#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void error();
unsigned invertujK(unsigned x, unsigned k);

void error(){
	fprintf(stderr, "-1\n");
	exit(EXIT_FAILURE);
}

unsigned invertujK(unsigned x, unsigned k){
	unsigned mask = 1, new_x = x;
	for(int i = 0, j = 0; i < sizeof(unsigned)*8; i++, mask <<= 1){
		if(x & mask){
			j++;
		}
		if(j == k){
			j = 0;
			new_x -= pow(2, i);
		}
	}
	return new_x;
}

int main(){
	unsigned x, k;
	scanf("%u %u", &x, &k);
	if(x < 0 || k < 0){
		error();
	}
	x = invertujK(x, k);
	printf("%u\n", x);
	return 0;
}