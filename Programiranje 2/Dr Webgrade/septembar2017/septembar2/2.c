#include <stdio.h>
#include <stdlib.h>

#define MAX_DUZINA 26

typedef struct{

	char prvi_grad[MAX_DUZINA];
	char drugi_grad[MAX_DUZINA];
	float kilometraza;
	unsigned trajanje;

}LET;

void error();
int poredi(const void *a, const void *b);

void error(){
	fprintf(stderr, "-1\n");
	exit(EXIT_FAILURE);
}

int poredi(const void *a, const void *b){
	LET *prvi = (LET*)a, *drugi = (LET*)b;

	if(prvi->kilometraza < drugi->kilometraza){
		return 1;
	}
	else if(prvi->kilometraza > drugi->kilometraza){
		return -1;
	}
	else{
		if(prvi->trajanje < drugi->trajanje){
			return -1;
		}
		else{
			return 1;
		}
	}
}

int main(){

	FILE *input;
	LET *array;
	int size = 100, i = 0;

	input = fopen("letovi.txt", "r");
	if(input == NULL){
		error();
	}

	array = (LET*)calloc(size, sizeof(LET));
	if(array == NULL){
		error();
	}

	while(fscanf(input, "%s %s %f %i", array[i].prvi_grad, array[i].drugi_grad, &array[i].kilometraza, &array[i].trajanje) == 4){
		if(array[i].kilometraza <= 0 || array[i].trajanje < 1){
			error();
		}
		if(i + 10 == size){
			size += 100;
			array = realloc(array, sizeof(LET) * size);
			if(array == NULL){
				error();
			}
		}
		i++;
	}

	qsort(array, i, sizeof(LET), poredi);

	for(int j = 0; j < i; j++){
		fprintf(stdout, "%s %s %.2f %i\n", array[j].prvi_grad, array[j].drugi_grad, array[j].kilometraza, array[j].trajanje);
	}

	free(array);
	fclose(input);
	return 0;
}