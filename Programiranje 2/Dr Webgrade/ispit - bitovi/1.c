#include <stdio.h>
#include <stdlib.h>

void error();
unsigned invert_if_0(unsigned x);

void error(){
	fprintf(stderr, "-1\n");
	exit(EXIT_FAILURE);
}

unsigned invert_if_0(unsigned x){
	unsigned mask = 4;
	unsigned size = sizeof(unsigned)*8;
	for(int i = 2; i < size; i += 3, mask <<= 3){
		if(x & mask){
			continue;
		}
		else{
			x |= mask;
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

	printf("%u\n", invert_if_0(x));

	return 0;
}