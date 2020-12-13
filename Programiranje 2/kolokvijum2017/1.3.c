#include <stdio.h>
#include <stdlib.h>

void greska();
int noviBroj(int x, int n);

void greska(){
	fprintf(stderr, "-1\n");
	exit(EXIT_FAILURE);
}

int noviBroj(int x, int n){
	if(x == 0){
		return x;
	}
	int levi_deo = x/10;
	if(x%10%2 == 0){
		int 
	}
	else{

	}


}

int main(){
	int x, n, y;
	fscanf(stdin, "%i %i", &x, &n);
	if(n<0){
		greska();
	}

	y = noviBroj(x, n);

	fprintf(stdout, "%i\n", y);

	return 0;
}