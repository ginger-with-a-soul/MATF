#include <stdio.h>


int main(){

	int n, i = 0, m, s_p = 0, s_n = 0;

	scanf("%i", &n);

	if(n<1){
		printf("-1\n");
		return -1;
	}

	while(i<n){
		scanf("%i", &m);
		if(m>-1){
			s_p = s_p + m;
		}
		else{
			s_n = s_n +m;
		}
		i++;
	}

	printf("%i\v%i\n", s_p, s_n);


return 0;
}
