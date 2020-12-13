#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(){
char c = getchar();
if(c>='a' && c<='z')
	printf("Uneti karakter je: %c\nASCII kod karaktera je: %d\nNjemu odgovarajuce veliko slovo je: %c\nNjegov ASCII kod je: %d\n", c, c, c-32, c-32);
else if(c>='A' && c<='Z')
	printf("Uneti karakter je: %c\nASCII kod karaktera je: %d\nNjemu odgovarajuce malo slovo je: %c\nNjegov ASCII kod je: %d\n", c, c, c+32, c+32);
else
	printf("Uneti karakter je: %c\nNjegov ASCII kod je: %d\n", c, c);
return 0;
}
