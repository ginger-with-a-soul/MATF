#include <stdio.h>
#include <stdlib.h>

void greska();
int f14(int x);

void greska(){
	fprintf(stderr, "-1\n");
	exit(EXIT_FAILURE);
}

int f14(int x){
	if(x >= 10){
		return 0;
	}
	int x0, x1, x2;
	x0 = x%10;
	x1 = x/10%10;
	x2 = x/100%10;
	int levi_deo = f14(x/10);
	if(x0 + x2 == x1){
		return levi_deo*100 + x2*10 + x0;
	}
	else{
		return levi_deo*1000 + x2*100 + x1*10 + x0;
	}

}

int main(){

	int x, y;
	fscanf(stdin, "%i", &x);

	y = f14(x);

	fprintf(stdout, "%i\n", y);

	return 0;
}