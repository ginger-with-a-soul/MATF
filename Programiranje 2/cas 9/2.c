#include <stdio.h>
#include <stdlib.h>

void greska();
void proveri(int x, unsigned k);

void greska(){
	fprintf(stderr, "-1\n");
	exit(EXIT_FAILURE);
}

void proveri(int x, unsigned k){
	unsigned mask = 1 << k;
	if(x & mask){
		printf("jeste\n");
	}
	else{
		printf("nije\n");
	}
}


int main(){
	unsigned k;
	int x;

	scanf("%i %u", &x, &k);
	if(k < 0 || k >= (sizeof(int)*8)){
		printf("pozicija nije u dobrom opsegu\n");
		exit(EXIT_FAILURE);
	}

	proveri(x, k);

	return 0;
}