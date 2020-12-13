#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>

int main(){
char c = getchar();
switch(c){
	case '1':
	printf("Ponedeljak\n");
	break;
	case '2':
	printf("Utorak\n");
	break;
	case '3':
	printf("Sreda\n");
	break;
	case '4':
	printf("Cetvrtak\n");
	break;
	case '5':
	printf("Petak\n");
	break;
	case '6':
	printf("Subota\n");
	break;
	case '7':
	printf("Nedelja\n");
	break;
	default:
	printf("Neispravan unos!\n");
	break;
	}
return 0;
}
