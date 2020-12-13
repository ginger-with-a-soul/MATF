#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
	int broj, max, signal = 0, count = 0;

	for(int i = 1;i<argc;i++){
		broj = atoi(argv[i]);
		broj = abs(broj);
		max = broj%10;
		broj /= 10;
		while(broj){
			if(broj%10 >= max){
				signal = 1;
				break;
			}
			max = broj%10;
			broj /= 10;
		}
		if(!signal){
			count++;
		}
		signal = 0;	
	}
	fprintf(stdout, "%i\n", count);
	return 0;
}