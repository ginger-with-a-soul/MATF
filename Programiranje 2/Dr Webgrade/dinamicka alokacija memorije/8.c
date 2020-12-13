#include <stdio.h>
#include <stdlib.h>

void greska();
void greska(){
	fprintf(stderr, "-1\n");
	exit(EXIT_FAILURE);
}

int main(){
	int n, *p, br = 0;

	fscanf(stdin, "%i", &n);
	if(n<1){
		greska();
	}

	p =(int*)calloc(n, sizeof(int));

	for(int i = 0;i<n;i++){
		fscanf(stdin, "%i", &p[i]);
	}

	for(int i = 0;i<n;i++){
		if(i == 0){
				fprintf(stdout, "0 ");
				continue;
			}
		for(int j = i;j>0;j--){
			if(p[i]>p[j-1]){
				br++;
			}
		}
		fprintf(stdout, "%i ", br);
		br = 0;
	}

	free(p);
	return 0;
}