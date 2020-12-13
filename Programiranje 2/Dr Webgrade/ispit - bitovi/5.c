#include <stdio.h>
#include <stdlib.h>

void error();
int prebroj_1(unsigned x);
unsigned promeni_prvi(unsigned x, unsigned y);

void error(){
	fprintf(stderr, "-1\n");
	exit(EXIT_FAILURE);
}

int prebroj_1(unsigned x){
	unsigned mask = 1 << sizeof(unsigned)*8 - 1, count = 0;
	while(mask){
		if(mask & x){
			count++;
		}
		mask >>= 1;
	}
	return count;
}

unsigned promeni_prvi(unsigned x, unsigned y){
	unsigned mask = ~0;;
	if(prebroj_1(x) > prebroj_1(y)){
		x ^= mask;
	}
	else{
		y ^= mask;
		x &= y;
	}
	return x;
}

int main(){

	unsigned x, y;
	scanf("%u %u", &x, &y);
	if(x < 0 || y < 0){
		error();
	}

	printf("%u\n", promeni_prvi(x, y));

	return 0;
}