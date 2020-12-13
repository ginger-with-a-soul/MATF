#include <stdio.h>
#include <string.h>

#define MAX 101

int orf(char rnk[]);

int orf(char rnk[]){
  int  i = 0;
  if(strstr(rnk, "AUG") != NULL){
    i++;
  }
  return i;
}

int main(){
  
  char rnk[MAX];
  int i = 0, ret = 0;
  
  while(scanf("%s", rnk) != EOF){
    for(i = 0;rnk[i];i++){
      if(rnk[i] != 'A' && rnk[i] != 'U' && rnk[i] != 'C' && rnk[i] != 'G'){
        printf("\n-1 ");
        ret = -1;
        break;
      }
    }
    if(ret == 0){
      printf("\n%i\n ", orf(rnk));
    }
  }
  
  
  
  return 0;
}