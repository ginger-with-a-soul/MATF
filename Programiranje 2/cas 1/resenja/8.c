#include<stdio.h>
#include<stdlib.h>

void greska(){
	fprintf(stderr, "-1\n");
	exit(EXIT_FAILURE);
}

int main(int argc, char* argv[])
{
  if(argc != 3)
    greska();

  int a, b;
  a = atoi(argv[1]);
  b = atoi(argv[2]);

  if(a > b)
    greska();

  while(a<=b)
    printf("%d ", a++);

  return 0;
}
