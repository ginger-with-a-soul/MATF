#include <stdio.h>
#include <stdlib.h>

void greska();
int izmeni(int n);

void greska(){
	fprintf(stderr, "-1\n");
	exit(EXIT_FAILURE);
}

int izmeni(int n){
	if(n == 0){
		return n;
	}

	int levi_deo = izmeni(n/10);

	if(n%2 == 0){
		return levi_deo*10 + (n%10)/2;
	}
	else{
		return levi_deo*10 + n%10;
	}


}

int main(int argc, char *argv[]){
	int znak = 1;
	if(argc != 2){
		greska();
	}
	int n = atoi(argv[1]);
	if(n == 0){
		greska();
	}
	if(n<0){
		znak = -1;
		n *= znak;
	}

	fprintf(stdout, "%i\n", znak*izmeni(n));

	return 0;
}