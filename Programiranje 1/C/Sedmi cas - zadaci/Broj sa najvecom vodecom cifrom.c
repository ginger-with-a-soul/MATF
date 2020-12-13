#include <stdio.h>

int main(){

	int n, m, i = 0, nm, vc1 = 0, vc2 = 0;
	
	scanf("%i", &n);
	if(n<0){
		printf("-1\n");
		return -1;
	}
	else if(n==0){
		printf("Niste uneli ni jedan broj!\n");
		return 0;
	}

	while(i<n){
		scanf("%i", &m);
		nm = m;
	// treba resiti kako da se ispise prvi a ne poslednji takav broj
		if(m/10==0){
			vc1 = m;
			if(vc1>vc2)
				vc2 = m;	
		}
		while(m/10!=0){
			m /= 10;
			if(m>vc1){
				vc1 = m;
			}
		}

	i++;
	}


	printf("%i\n", nm);

return 0;
}
