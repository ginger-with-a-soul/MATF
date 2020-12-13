#include <stdio.h>
#include <stdlib.h>

void error();

void error(){
	fprintf(stderr, "-1\n");
	exit(EXIT_FAILURE);
}

int main(int argc, char *argv[]){

	if(argc != 2){
		error();
	}

	int n = atoi(argv[1]), sum = 0, x, counter = 0;
	if(n < 1){
		error();
	}

	for(int i = 0; i < n; i++){
		fscanf(stdin, "%i", &x);
		if(x <= 0){
			error();
		}
		int digit_sum = 0, tmp = x;
		while(x){
			digit_sum += x % 10;
			x /= 10;
		}
		if(tmp % digit_sum == 0){
			counter++;
			sum += tmp;
		}
	}
	if(counter){
		fprintf(stdout, "%.2f\n", (float)sum/counter);
	}
	else{
		fprintf(stdout, "%.2f\n", (float)counter);
	}

	return 0;
}