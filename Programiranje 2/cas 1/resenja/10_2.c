#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 201

void greska();

int main(int argc, char** argv)
{
  if(argc != 3)
    greska();
  
  FILE* dat1 = fopen(argv[1], "r");
  FILE* dat2 = fopen(argv[2], "r");
  
  if(dat1 == NULL || dat2 == NULL)
    greska();
  
  char bafer1[MAX];
  char bafer2[MAX];
  int i = 1;

  while(fgets(bafer1, MAX, dat1) != NULL)
  {
		if(fgets(bafer2, MAX, dat2) != NULL){
			if(strcmp(bafer1, bafer2) != 0)
				printf("%d ", i);
		}
		else
			printf("%d ", i);
		i++;
  }
  while(fgets(bafer2, MAX, dat2) != NULL)
  {
    printf("%d ", i);
    i++;
  }
  
  fclose(dat1);
  fclose(dat2);
  
  return 0;
}

void greska()
{
  fprintf(stderr, "-1");
  exit(EXIT_FAILURE);
}
