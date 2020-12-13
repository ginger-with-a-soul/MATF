#include <stdio.h>
#include <stdlib.h>

void suma_bitova(int n);

void suma_bitova(int n){
	unsigned mask = 1 << (sizeof(int)*8 - 1), suma = 0;

	while(mask){
		if(n & mask){
			suma++;
		}
		mask >>= 1;
	}

	printf("%u\n", suma);
}

int main(){
	int n;
	scanf("%i", &n);

	suma_bitova(n);
	return 0;
}