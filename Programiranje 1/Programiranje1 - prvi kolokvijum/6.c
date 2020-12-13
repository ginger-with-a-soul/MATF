#include <stdio.h>

int main(){

	int a, b, h1, h2, s1, s2, d1, d2, j1, j2;
	
	scanf("%i %i", &a, &b);

	if(a<1000 || a>9999 ||b<1000 || b>9999){
		printf("-1\n");
		return -1;
	}

	h1 = a/1000;
	h2 = b/1000;
	s1 = a/100%10;
	s2 = b/100%10;
	d1 = a/10%10;
	d2 = b/10%10;
	j1 = a%10;
	j2 = b%10;

	if(h1==j2 && h2==j1 && s1==d2 && s2==d1){
		printf("1\n");
		return 0;
	}
	else{
		printf("0\n");
	}


return 0;
}
