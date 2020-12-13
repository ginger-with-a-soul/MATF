#include <stdio.h>

int main(int argc, char *argv[]){

	int i, br;

	for(i = 1;i<argc;i++){
		if(argv[i][0]=='-'){
			for(br = 1;argv[i][br]!='\0';br++){
				printf("%c ", argv[i][br]);
			}
		}
	}

	printf("\n");

	return 0;
}