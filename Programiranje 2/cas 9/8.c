#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void error();
void print_bits(unsigned x);
unsigned right_rotate(unsigned x, int n);

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

unsigned right_rotate(unsigned x, int n){
	n %= 32;
	unsigned rot_x = 0;
	int index = 31 - n;
	if(index == 31){
		rot_x = x;
		return rot_x;
	}
	unsigned mask = 1;
	for(int i = 0; i < (sizeof(unsigned)*8); i++){
		if(x & mask){
			rot_x += pow(2, index);
		}
		mask <<= 1;
		index++;
		if(index == 32){
			index = 0;
		}
	}

	return rot_x *= 2;
}

int main(){
	unsigned x, rot_x;
	int n;
	scanf("%u %i", &x, &n);
	if(n < 0){
		error();
	}
	rot_x = right_rotate(x, n);
	print_bits(x);
	print_bits(rot_x);

	return 0;
}