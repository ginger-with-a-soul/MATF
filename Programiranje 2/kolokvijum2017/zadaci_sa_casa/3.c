#include <stdio.h>
#include <stdlib.h>

int veci_od_proseka();
void greska();
void greska(){
	fprintf(stderr, "-1\n");
	exit(EXIT_FAILURE);
}

int veci_od_proseka(){
	int n, *p, i = 1, count = 0, velicina = 100;
	double suma = 0, prosek;

	p = (int*)calloc(velicina, sizeof(int));
	if(p == NULL){
		greska();
	}

	do{
		fscanf(stdin, "%i", &n);
		
		if(i>velicina){
			velicina += 100;
			p = (int*)realloc(p, velicina);
			if(p == NULL){
				greska();
			}
		}
		p[i++] = n;
		suma += n;

	}while(n != 0);
	i = i - 2;
	if(i == 0){
		return count;
	}
	prosek = (double)suma/(i);
	for(int j = 1;j<=i;j++){
		if(p[j]>prosek){
			count++;
		}
	}

	
	free(p);
	return count;
}

int main(){
	int x;

	x = veci_od_proseka();
	
	fprintf(stdout, "%i\n", x);

	return 0;
}
