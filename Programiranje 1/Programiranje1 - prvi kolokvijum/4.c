#include <stdio.h>


int main(){
	
	int a, h, s, d, j, p = 1;
	scanf("%i", &a);
	
	h = a/1000;
	s = a/100%10;
	d = a/10%10;
	j = a%10;

	if(h%2==0){
		p *= h;
	}
	if(s%2==0){
		p *= s;
	}
	if(d%2==0){
		p *= d;
	}
	if(j%2==0){
		p *=j;
	}

	printf("%i\n", a*p);


return 0;
}
