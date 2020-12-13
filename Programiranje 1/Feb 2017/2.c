#include <stdio.h>
#include <string.h>

#define MAX_NISKI 100
#define MAX 101

int main(){
  
  int n, a, b, i = 0, j = 0, br = 0;
  char s1[MAX], s2[MAX];
  
  scanf("%s", s1);
  
  scanf("%i", &n);
  
  if(n<1 || n>MAX_NISKI){
    printf("-1\n");
    return -1;
  }
  
  a = strlen(s1);
  
  for(i = 0;i<n;i++){
    scanf("%s", s2);
    b = strlen(s2);
    if(a>b){
      break;
    }
    for(j = 0;j<a;j++){
      if(s1[j]==s2[j]){
        br++;
      }
    }
    if(br==a){
      printf("%s", s2);
      continue;
    }
    br = 0;
    for(j = 0;j<a;j++){
      if(s1[j]==s2[b-a+j]){
        br++;
      }
    }
    if(br==a){
      printf("%s", s2);
    }
    br = 0;
  }
  
  return 0;
}