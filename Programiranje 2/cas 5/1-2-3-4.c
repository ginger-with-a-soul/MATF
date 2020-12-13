#include <stdio.h>
#include <stdlib.h>

void ispis1(int n);
void ispis2(int n);
int broj_parnih(int n);
int najveca_cifra(int n);
int ukloni(int n, int c);

void ispis1(int n){
	if(n<10){
		fprintf(stdout, "%i ", n);
		return;
	}
	else{
		ispis1(n/10);
		fprintf(stdout, "%i ", n%10);
	}
}

void ispis2(int n){
	if(n<10){
		fprintf(stdout, "%i ", n);
		return;
	}
	else{
		fprintf(stdout, "%i ", n%10);
		ispis2(n/10);
	}
}
int broj_parnih(int n){

	if(n<10){
		if(n%2){
			return 0;
		}
		else{
			return 1;
		}
	}
	else{
		if(n%2){
			return broj_parnih(n/10);
		}
		else{
			return 1 + broj_parnih(n/10);
		}
	}

}

int najveca_cifra(int n){
	if(n<10){
		return n;
	}

	int max = najveca_cifra(n/10);
	
	
	if(max<n%10){
		return (n%10);
	}
	else{
		return max;
	}
}

int ukloni(int n, int c){
	if(n == 0){
		return 0;
	}
	int levo = ukloni(n/10, c);

	if(n%10 == c){
		return levo;
	}
	else{
		return levo*10 + n%10;
	}
}

int main(){

	int n, p = 0, c;
	fscanf(stdin, "%i", &n);

	if(n<0){
		n = abs(n);
		p = 1;
	}

	ispis1(n);
	printf("\n");

	ispis2(n);
	printf("\nbroj parnih: %i\n", broj_parnih(n));

	printf("max cifra: %i\nucitaj cifru c: ", najveca_cifra(n));

	scanf("%i", &c);
	printf("bez cifre c: %i\n", ukloni(n, c));





	if(p){
		n *= -1;
	}


	return 0;
}