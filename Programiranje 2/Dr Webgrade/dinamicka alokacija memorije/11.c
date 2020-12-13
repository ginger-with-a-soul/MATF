#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

void greska();
void greska(){
	fprintf(stderr, "-1\n");
	exit(EXIT_FAILURE);
}

int main(){

	typedef struct VEKTOR{
		int x;
		int y;
		int z;
	}VEKTOR;

	VEKTOR *p, v, *a;
	int n, d, max = 0, pozicija;
	FILE *ulaz;

	ulaz = fopen("vektori.txt", "r");
	if(ulaz == NULL){
		greska();
	}

	fscanf(ulaz, "%i", &n);

	p = (VEKTOR*)calloc(n, sizeof(VEKTOR)+1);
	if(p == NULL){
		greska();
	}
	a = p;

	for(int i = 0;i<n;i++){
		fscanf(ulaz, "%i %i %i", &v.x[p++], &v.y[p++], &v.z[p]);
		d = sqrt(v.x[p-2]*v.x[p-2] + v.y[p-1]*v.y[p-1] + v.z[p]*v.z[p]);
		if(max<d){
			max = d;
			pozicija = i+1;
		}
		p++;
	}

	fprintf(stdout, "%i %i %i\n", v.x[a+3*pozicija], v.y[a+3*pozicija+1], v.z[a+3*pozicija+1]);

	fclose(ulaz);
	free(p);
	return 0;
}