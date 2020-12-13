#include <stdio.h>


int main(){

	int n, m, s = 0, i = 0;

	scanf("%i", &n);

	if(n<1){
		printf("-1\n");
		return -1;
	}
	
	while(i<n){
		scanf("%i", &m);
		if(m%5==0 && m%7!=0){
			s = s + m;
		}

		i++;
	}

printf("%i\n", s);

return 0;
}
