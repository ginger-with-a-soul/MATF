#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

void greska();
void greska(){
	fprintf(stderr, "-1\n");
	exit(EXIT_FAILURE);
}

int main(int argc, char *argv[]){

	int i = 0, brojilac, imenilac;
	double decimal;

	if(argc<2){
		greska();
	}

	for(i = 1;i<argc;i++){
		int crte = -1, j = 0;
		for(j = 0;argv[i][j];j++){
			if(argv[i][0] == '/' || !isdigit(argv[i][0])){
				greska();
			}
			if(argv[i][j] == '/'){
				crte++;
			}
		}
		if(!isdigit(argv[i][j-1])){
			greska();
		}
		if(crte){
				greska();
			}
		sscanf(argv[i], "%i/%i", &brojilac, &imenilac);
		if(imenilac == 0){
			greska();
		}
		decimal = (double)brojilac/imenilac;
		fprintf(stdout, "%.2lf ", decimal);
	}


	return 0;
}