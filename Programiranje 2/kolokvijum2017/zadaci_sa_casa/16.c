#include <stdio.h>
#include <stdlib.h>

void greska();
int f16(int a[], int n);

void greska(){
	fprintf(stderr, "-1\n");
	exit(EXIT_FAILURE);
}

int f16(int a[], int n){
	if(n <= 0){
		return 1;
	}

	int proizvod_neparnih = f16(a+1, n-1);
	if(a[0]%2){
		return proizvod_neparnih * a[0];
	}
	else{
		return proizvod_neparnih;
	}

}

int main(){
	int n, *a, y;
	scanf("%i", &n);
	if(n<1){
		greska();
	}
	a = (int*)calloc(n, sizeof(int));
	if(a == NULL){
		greska();
	}
	for(int i = 0;i<n;i++){
		scanf("%i", &a[i]);
	}
	printf("%i\n", f16(a, n));
	free(a);
	return 0;
}