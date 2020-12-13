#include <stdio.h>
#include <stdlib.h>

void postavi(int x, unsigned k);

void postavi(int x, unsigned k){
	unsigned mask = 1 << k;
	x  |= mask;
	printf("%i\n", x);
}
int main(){
	unsigned k;
	int x;
	scanf("%i %u", &x, &k);
	if(k < 0 || k >= (sizeof(int)*8)){
		printf("pozicija nije u dobrom opsegu\n");
		exit(EXIT_FAILURE);
	}

	postavi(x, k);

	return 0;
}