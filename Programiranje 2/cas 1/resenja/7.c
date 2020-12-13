#include<stdio.h>

int main(int argc, char* argv[]){

  //Stampamo broj argumenata komandne linije
  printf("%d\n", argc);
  int i;
  
  //Stampamo sve argumente
  for(i=0; i<argc; i++)
    printf("%d. %s\n", i+1, argv[i]);
  
  return 0;
}
