#include <stdio.h>
#include <stdlib.h>

void greska();
void f12(int *a, int n);

void greska(){
	fprintf(stderr, "-1\n");
	exit(EXIT_FAILURE);
}

void f12(int *a, int n){
	if(n <= 2){
		return;
	}
	int a0, a1, a2;
	a0 = a[0];
	a1 = a[1];
	a2 = a[2];

	f12(a+1, n-1);

	if(a[0] + a[2] == a[1]){
		a[1] = 0;
	}

}

int main(){
	int n, *a;
	fscanf(stdin, "%i", &n);
	if(n<0){
		greska();
	}
	a = (int*)calloc(n, sizeof(int));
	if(a == NULL){
		greska();
	}
	for(int i = 0;i<n;i++){
		scanf("%i", &a[i]);
	}

	f12(a, n);

	for(int i = 0;i<n;i++){
		fprintf(stdout, "%i ", a[i]);
	}
	printf("\n");

	free(a);
	return 0;
}