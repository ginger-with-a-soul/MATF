#include <stdio.h>

#define MAX 50

void izdvoj(int* s, int n, int* pn, int* nn, int *bp, int *bn);

void izdvoj(int* s, int n, int* pn, int* nn, int *bp, int *bn){
  int i = 0;
  for(i = 0;i<n;i++){
    if(s[i]%2){
      nn[(*bn)++] = s[i];
    }
    else{
      pn[(*bp)++] = s[i];
    }
  }
}

int main(){
  int s[MAX], pn[MAX], nn[MAX];
  int n, i = 0, bp = 0, bn = 0;
  scanf("%i", &n);
  if(n<1 || n>MAX){
    printf("-1\n");
    return -1;
  }
  
  for(i = 0;i<n;i++){
    scanf("%i", &s[i]);
  }
  
  izdvoj(s, n, pn, nn, &bp, &bn);
  
  for(i = 0;i<bp;i++){
    printf("%i ", pn[i]);
  }
  
  printf("\n");
  
  for(i = 0;i<bn;i++){
    printf("%i ", nn[i]);
  }
  
  printf("\n");
  
  return 0;
}