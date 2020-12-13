#include <stdio.h>
#include <stdlib.h>

void greska();
void greska(){
	fprintf(stderr, "-1\n");
	exit(EXIT_FAILURE);
}

int main(){

	int n, *p, i = 0;

	fscanf(stdin,"%i", &n);
	if(n<1){
		greska();
	}

	p = (int*)calloc(n, sizeof(int));
	if(p == NULL){
		greska();
	}

	for(i = 0;i<n;i++){
		scanf("%i", &p[i]);
	}

	for(i = n-1;i>=0;i--){
		fprintf(stdout, "%i ", p[i]);
	}

	free(p);

	return 0;
}