#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void greska();
void greska(){
	fprintf(stderr, "-1\n");
	exit(EXIT_FAILURE);
}

int main(int argc, char *argv[]){

	int a, b, n, i = 0;

	if(argc != 4){
		greska();
	}

	n = atoi(argv[1]);
	a = atoi(argv[2]);
	b = atoi(argv[3]);

	if(n<1){
		greska();
	}

	if(a>=b){
		greska();
	}

	srand(time(NULL));

	for(i = 0;i<n;i++){
		fprintf(stdout, "%.2lf\n", (double)(a+(b-a)*((double)rand()/RAND_MAX))); /*INTERPOLACIJA - predstavljanje brojeva
																				izmedju 2 intervala
																				[a,b] -> (a+(b-a)*(rand()/RAND_MAX))*/
	}

}