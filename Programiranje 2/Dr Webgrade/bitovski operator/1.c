#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void error();
unsigned invertujSvakiTreci(unsigned x);

void error(){
	fprintf(stderr, "-1\n");
	exit(EXIT_FAILURE);
}

unsigned invertujSvakiTreci(unsigned x){
	unsigned new_x = 0, mask = 1;
	for(int i = 0; i<sizeof(unsigned)*8; i += 3, mask <<= 3){
		if(!(x & mask)){
			new_x += pow(2, i);
		}
	}
	return new_x;
}

int main(){
	unsigned x;
	scanf("%u", &x);
	if(x < 0){
		error();
	}
	x = invertujSvakiTreci(x);
	printf("%i\n", x);
	return 0;
}