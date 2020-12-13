#include <stdio.h>
#include <stdlib.h>

void error();
void print_bits(unsigned x);
int check(unsigned n, unsigned m);

void error(){
	fprintf(stderr, "-1\n");
	exit(EXIT_FAILURE);
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

int check(unsigned n, unsigned m){
	unsigned mask = m & 15, count = 0;
	int size = sizeof(unsigned)*8 - 4;
	for(int i = 0; i < size; i++, mask <<= 1){
		unsigned tmp = mask & n;
		if(!(tmp ^ mask)){
			count++;
		}
	}
	return count;
}

int main(){

	unsigned n, m;
	scanf("%u %u", &n, &m);

	if(n < 0 || m < 0){
		error();
	}

	printf("%i\n", check(n, m));

	return 0;
}