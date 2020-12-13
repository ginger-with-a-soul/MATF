#include<stdio.h>
#include<stdlib.h>

#define MAX_LINIJA 81

void greska(){
	fprintf(stderr, "-1\n");
	exit(EXIT_FAILURE);
}

int main()
{
	FILE* ulaz, *izlaz;
	char linija[MAX_LINIJA];

	ulaz = fopen("1_ulaz.txt", "r");
	if(ulaz == NULL)
		greska();

	izlaz = fopen("izlaz.txt", "w");
	if(izlaz == NULL)
		greska();
	
	/*obrada ulaza*/
	//char c;
	//karakter po karakter I nacin
	//while(fscanf(ulaz, "%c", &c) == 1)
	//	fprintf(izlaz, "%c", c);
	
	//karakter po karakter II nacin
	//fgetc(fajl) -- getchar()	
	//while((c = fgetc(ulaz)) != EOF){
	//	fputc(c, izlaz);
	//}

	//linija po linija
	//while(fgets(linija, MAX_LINIJA, ulaz) != NULL)
	//	fputs(linija, izlaz);

	while(fgets(linija, MAX_LINIJA, ulaz) != NULL)
		fprintf(izlaz, "%s", linija);

	fclose(ulaz);
	fclose(izlaz);
	return 0;
}
