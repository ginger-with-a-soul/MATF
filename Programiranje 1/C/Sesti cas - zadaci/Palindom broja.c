#include <stdio.h>

int main(){

	int a, h, s, d, j, novo_a;
	
	scanf("%i", &a);

	if(a<1000 || a>9999){
		printf("-1\n");
		return -1;
	}

	h = a/1000;
	s = a/100%10;
	d = a/10%10;
	j = a%10;

	if(h==j && s==d)
		novo_a = h*10+d;
	else
		novo_a = s*10+j;

	printf("%i\n", novo_a);


return 0;
}
