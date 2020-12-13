#include<stdio.h>

int main(int argc, char* argv[])
{

  int i, j;
  for(i=1; i<argc; i++)
  {
    //-abc
    if(argv[i][0] == '-')
    {
      for(j=1; argv[i][j] != '\0'; j++)
        printf("%c ", argv[i][j]);
    }
  }

  return 0;
}
