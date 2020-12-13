#include <stdio.h>
#include <ctype.h>

int main(){
	
	int a, b, c, rez;
	char c1, c2;
	scanf("%i %i %i %c %c", &a, &b, &c, &c1, &c2);
	
	if(c1=='k'){
		if(c2=='k')
			rez = a && b && c;
		else if(c2=='d')
			rez = a && b || c;
		else if(c2=='v')
			rez = a && b > c;
		else if(c2=='m')
			rez = a && b < c;
		else{
			printf("Los unos c2!\n");
			return -1;
		}

	}

	else if(c1=='d'){
		if(c2=='k')
			rez = a || b && c;
		else if(c2=='d')
			rez = a || b || c;
		else if(c2=='v')
			rez = a || b > c;
		else if(c2=='m')
			rez = a || b < c;
		else{
			printf("Los unos c2!\n");
			return -1;
		}

	}

	else if(c1=='v'){
		if(c2=='k')
			rez = a > b && c;
		else if(c2=='d')
			rez = a > b || c;
		else if(c2=='v')
			rez = a > b > c;
		else if(c2=='m')
			rez = a > b < c;
		else{
			printf("Los unos c2!\n");
			return -1;
		}

	}

	else if(c1=='m'){
		if(c2=='k')
			rez = a < b && c;
		else if(c2=='d')
			rez = a < b || c;
		else if(c2=='v')
			rez = a < b > c;
		else if(c2=='m')
			rez = a < b < c;
		else{
			printf("Los unos c2!\n");
			return -1;
		}

	}
	else{
		printf("Los unos c1!\n");
		return -1;	
	}

	printf("Rezultat je: %i\n", rez);




return 0;
}
