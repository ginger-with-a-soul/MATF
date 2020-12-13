#include <stdio.h>
#include <stdlib.h>

void greska();
void print_bits(int n);

void print_bits(int n){
	unsigned mask = 1 << (sizeof(int)*8 - 1);

	while(mask){
		if(n & mask){
			fprintf(stdout, "1");
		}
		else{
			fprintf(stdout, "0");
		}

		mask >>= 1;
	}

	puts("");
}

void greska(){
	fprintf(stderr, "-1\n");
	exit(EXIT_FAILURE);
}

int main(){
	int n;
	scanf("%i", &n);

	print_bits(n);

	return 0;
}