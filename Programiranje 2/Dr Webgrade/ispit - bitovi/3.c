#include <stdio.h>
#include <stdlib.h>

void error();
unsigned change_groups_of_bits(unsigned x);

void error(){
	fprintf(stderr, "-1\n");
	
}

unsigned change_groups_of_bits(unsigned x){
	unsigned mask1 = 1;
	unsigned mask2 = 2;
	unsigned mask3 = 4;
	unsigned size = sizeof(unsigned)*8 - 2;
	for(int i = 1; i < size; i++, mask1 <<= 1, mask2 <<= 1, mask3 <<= 1){
		if(x & mask1){
			if(!(x & mask2)){
				if(x & mask3){
					x ^= mask2;
					continue;
				}
			}
		}
		else if(!(x & mask1)){
			if(x & mask2){
				if(!(x & mask3)){
					x ^= mask2;
				}
			}
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

	printf("%u\n", change_groups_of_bits(x));

	return 0;
}