#include <stdio.h>

int main(){
	
	int pp = 1, b, bp = 0;

	scanf("%i", &b);
	if(b>0){
		pp *= b;
		bp++;
	}
	else if(b==0){
		printf("Nisu uneseni brojevi!\n");
		return -1;
	}
	
	while(b!=0){
		scanf("%i", &b);
		if(b>0){
			pp *= b;
			bp++;
		}
			
	}
	
	if(bp==0){
		printf("Nisu uneti pozitivni brojevi!\n");
		return -1;
	}
	else
		printf("%i\n", pp);

return 0;
}
