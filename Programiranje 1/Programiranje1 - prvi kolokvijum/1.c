#include <stdio.h>
#include <ctype.h>

int main(){

	char c;
	int a, b;
	
	scanf("%c %i %i", &c, &a, &b);

	if((c!='n' && c!='p') || a<100 || a>999 || b<100 || b>999){
		printf("-1\n");
		return -1;
	}

	if(c=='n'){
		printf("%i\n", a%10+a/100+b%10+b/100);
	}
	else{
		printf("%i\n", a/10%10+b/10%10);
	}

	

return 0;
}
