#include <stdio.h>
#include <stdlib.h>


void error();
unsigned match(unsigned x, unsigned y);

void error(){
	fprintf(stderr, "-1\n");
	
}
void print_bits(unsigned x){
	unsigned mask = 1 << sizeof(unsigned)*8 - 1;
	while(mask){
		if(x & mask){
			printf("1");
		}
		else{
			printf("0");
		}
		mask >>= 1;
	}
	puts("");
}

unsigned match(unsigned x, unsigned y){
	unsigned count = 0;
	unsigned z;
	unsigned mask = ~(~0 << 4);
	y &= mask;
	z = x & mask;
	for(int i = 0; i < sizeof(unsigned)*8 - 3; i++, mask <<= 1, y <<= 1){
		z = x & mask;
		if(!(z ^ y)){
			count++;
		} 
	}
	return count;
}
int main(){

	unsigned x, y;
	scanf("%u %u", &x, &y);
	if(x < 0 || y < 0){
		error();
	}

	printf("%u\n", match(x, y));

	return 0;
}