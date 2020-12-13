#include <stdio.h>
#include <stdlib.h>

void error();

void error(){
	fprintf(stderr, "-1\n");
	exit(EXIT_FAILURE);
}

int main(int argc, char *argv[]){

	if(argc != 3){
		error();
	}

	int a = atoi(argv[1]), b = atoi(argv[2]), sum = 0;

	if(a < 0 || b < a){
		error();
	}

	for(int i = a; i <= b; i++){
		sum = 0;
		for(int j = i - 1; j >= 1; j--){
			if(i % j == 0){
				sum += j;
			}
		}
		if(sum == i){
			printf("%i ", i);
		}
	}

	puts("");

	return 0;
}