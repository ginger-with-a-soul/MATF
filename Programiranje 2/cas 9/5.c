#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void greska();
unsigned get_bits(int x, unsigned p, unsigned n);

void greska(){
	fprintf(stderr, "-1\n");
	exit(EXIT_FAILURE);
}

unsigned get_bits(int x, unsigned p, unsigned n){
	unsigned new_x = 0, mask =  1 << p;
	for(int i = p; i <= p+n; i++){
			if(x & mask){
				new_x += pow(2, i);
		}
		mask <<= 1;
	}
	return new_x;

}

int main(){

	int x;
	unsigned p, n, new_x;
	scanf("%i %u %u", &x, &p, &n);
	if(p < 0 ||  n < 0 || n+p >= (sizeof(int)*8)){
		greska();
	}

	new_x = get_bits(x, p, n);

	unsigned mask = 1 << (sizeof(int)*8 - 1);

	for(int i = 0; i < sizeof(int)*8; i++){
		if(x & mask){
			printf("1");
		}
		else{
			printf("0");
		}
		mask >>= 1;
	}
	printf("\n");

	mask = 1 << (sizeof(int)*8 - 1);
	for(int i = 0; i < sizeof(int)*8; i++){
		if(new_x & mask){
			printf("1");
		}
		else{
			printf("0");
		}
		mask >>= 1;
	}
	printf("\n");

	return 0;
}