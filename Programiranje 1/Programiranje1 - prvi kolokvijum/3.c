#include <stdio.h>
#include <ctype.h>

int main(){

	char s1, s2, g1, g2, i1, i2, i3;
	int  godina, indeks;
	scanf("%c%c%c%c%c%c%c", &s1, &s2, &g1, &g2, &i1, &i2, &i3);

	if(s1!='m' || (s2!='i' && s2!='a' && s2!='s' && s2!='r' && s2!='m' && s2!='p') || !isdigit(g1) || !isdigit(g2) || !isdigit(i1) || !isdigit(i2) || !isdigit(i3)){
		printf("-1\n");
		return -1;
	}

	if(g1>'1' && g2>'7'){
		godina = 1900 + (g1-'0')*10 + (g2-'0');
	}
	else{
		godina = 2000 + (g1-'0')*10 + (g2-'0');
	}


	if(i1=='0' && i2=='0'){
		indeks = i3-'0';
	}
	else if(i1=='0'){
		indeks = (i2-'0')*10 + (i3-'0');
	}
	else{
		indeks = (i1-'0')*100 + (i2-'0')*10 + (i3-'0');
	}


	if(s2=='i'){
		printf("informatika %i/%i\n", indeks, godina);
	}
	else if(s2=='a'){
		printf("astronomija %i/%i\n", indeks, godina);
	}
	else if(s2=='s'){
		printf("statistika %i/%i\n", indeks, godina);
	}
	else if(s2=='p'){
		printf("primenjena matematika %i/%i\n", indeks, godina);
	}
	else if(s2=='r'){
		printf("racunarstvo i informatika %i/%i\n", indeks, godina);
	}
	else{
		printf("teorijska matematika %i/%i\n", indeks, godina);
	}

return 0;
}
