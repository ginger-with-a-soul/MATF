#include <stdio.h>
#include <stdlib.h>

int main(){

	int n, d, i = 0, raz, m, nm, bp = 0;

	scanf("%i %i", &n, &d);
	raz = abs(d-n);
	
	if(n<1 || d<1){
		printf("-1\n");
		return -1;
	}
	
	while(i<n){
		scanf("%i", &m);
		if(i<1){
		nm = m;
		}
		else if(i>=1){
			if(raz==abs(nm-m)){
			bp++;			
			}
			nm = m;
		}

	i++;
	}

printf("%i\n", bp);


return 0;
}
