#include<stdio.h>
#include<stdlib.h>

#define MAX 51

void greska(){
  fprintf(stderr, "-1\n");
  exit(EXIT_FAILURE);
}

int main()
{
    FILE* ulaz;
    ulaz = fopen("imena.txt", "r");
    if(ulaz == NULL)
      greska();
    
    char ime[MAX], prezime[MAX];
    
    while(fscanf(ulaz, "%*d.%s%s%*f", ime, prezime) == 2){
      printf("%s %s\n", ime, prezime);
    }

    fclose(ulaz);
    return 0;
}
