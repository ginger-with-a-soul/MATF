#include <stdio.h>
#include <stdlib.h>

void error();
unsigned odradi_posao(unsigned x, unsigned y);

void error(){
	fprintf(stderr, "-1\n");
	exit(EXIT_FAILURE);
}

unsigned odradi_posao(unsigned x, unsigned y){
	unsigned oneX = 0, oneY = 0;
	unsigned mask = 1;
	unsigned size = sizeof(unsigned)*8 - 1;

	for(int i = 0; i < size; i++, mask <<= 1){
		if(x & mask){
			oneX++;
		}
		if(y & mask){
			oneY++;
		}
	}

	if(oneX > oneY){
		mask = 0;
		return x ^ ~mask;
	}
	else{
		return x & ~y;
	}
}

int main(){
	unsigned x, y;

	scanf("%u %u", &x, &y);

	if(x < 0 || y < 0){
		error();
	}

	fprintf(stdout, "%u\n", odradi_posao(x, y));

	return 0;
}