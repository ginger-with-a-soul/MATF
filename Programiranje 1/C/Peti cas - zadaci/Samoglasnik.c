#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>

int main(){
char c = tolower(getchar());
switch(c){
	case 'a':
	case 'e':
	case 'i':
	case 'o':
	case 'u':
		printf("Samoglasnik je!\n");
		break;
	default:
		printf("Nije samoglasnik!\n");
		break;
}
return 0;
}
