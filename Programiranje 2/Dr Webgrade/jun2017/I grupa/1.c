#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void error();
void error(){
	fprintf(stderr, "-1\n");
	exit(EXIT_FAILURE);
}

int main(int argc, char *argv[]){

	if(argc != 3){
		error();
	}

	int a = atoi(argv[1]), b = atoi(argv[2]), counter, tmp, sum;

	if(a < 0 || b < a){
		error();
	}

	for(int i = a; i <= b; i++){
		counter = 0;
		tmp = i;
		while(tmp){
			counter++;
			tmp /= 10;
		}
		tmp = i;
		sum = 0;
		while(tmp){
			sum += pow(tmp%10, counter);
			tmp /= 10;
		}
		if(sum == i){
			printf("%i ", i);
		}
	}

	printf("\n");

	return 0;
}