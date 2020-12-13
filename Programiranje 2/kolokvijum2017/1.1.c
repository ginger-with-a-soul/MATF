#include <stdio.h>
#include <stdlib.h>

void greska();
int noviBroj(int x, int n);

void greska(){
	fprintf(stderr, "-1\n");
	exit(EXIT_FAILURE);
}

int noviBroj(int x, int n){
	if(n == 0){
		return x;
	}
	if(x%10%2==0){
		return noviBroj(x/10, n-1);
	}
	else{
		return noviBroj(x/10, n)*10 + x%10;
	}

}

int main(){
	int x, n, znak = 1;
	scanf("%i %i", &x, &n);
	if(n<0){
		greska();
	}
	if(x<0){
		znak = -1;
	}
	printf("%i\n", znak*noviBroj(x, n));

	return 0;
}