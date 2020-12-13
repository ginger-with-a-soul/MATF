#include <stdio.h>
#include <stdlib.h>

int main(){
	
	int a, abs_a, h, s, d, j, min, max, s_min, s_max, rez;
	scanf("%i", &a);
	
	abs_a = a < 0? abs(a) : a;

	if(abs_a<1000 || abs_a>9999){
		printf("-1\n");
		return -1;
	}
	
	h = abs_a/1000;
	s = abs_a/100%10;
	d = abs_a/10%10;
	j = abs_a%10;

 	min = h;
	max = h;

	s_min = 1000;
	s_max = 1000;

	if(s>max){
		max = s;
		s_max = 100;
	}
	
	if(s<min){
		min = s;
		s_min = 100;
	}

	if(d>max){
		max = d;
		s_max = 10;
	}

	if(d<min){
		min = d;
		s_min = 10;
	}

	if(j>max){
		max = j;
		s_max = 1;
	}

	if(j<min){
		min = j;
		s_min = 1;
	}


	if(a>0)
		rez = a-max*s_max+min*s_max-min*s_min+max*s_min;
	else
		rez = (-1)*(abs_a-max*s_max+min*s_max-min*s_min+max*s_min);

	printf("%i\n", rez);










return 0;
}
