#include<stdio.h>
#include<stdlib.h>
#define MAX_LINIJA 81

void greska(){
	fprintf(stderr, "-1\n");
	exit(EXIT_FAILURE);
}

int main()
{
	FILE* ulaz;
	char linija[MAX_LINIJA];
	ulaz = fopen("knjiga.txt", "r");
	if(ulaz == NULL)
		greska();

	int brojac = 0;
	while(fgets(linija, MAX_LINIJA, ulaz) != NULL)
		brojac++;

	printf("%d\n", brojac);
	fclose(ulaz);
return 0;
}
