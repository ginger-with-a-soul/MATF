#include <stdio.h>
#include <string.h>

#define MAX 101
#define MAX_NISKI 100

int main(){
  char s1[MAX], s2[MAX], niz[MAX_NISKI];
  int n, i = 0, a, b, c, pref = 0, suf = 0, j = 0;
  scanf("%s", s1);
  
  a = strlen(s1);
  
  if(a > MAX){
    printf("-1\n");
    return -1;
  }

  
  scanf("%i", &n);
  if(n<1 || n>MAX_NISKI){
    printf("-1\n");
    return -1;
  }
  
  
  for(i = 0;i<n;i++){
    scanf("%s", s2);
    b = strlen(s2);
    c = b - a;
    
    if(b > MAX){
      printf("-1\n");
      return -1;
    }
    
    if(a > b){
      break;
    }
    
    pref = 1;
    suf = 1;
    
    for(j = 0;j<a;j++){
      if(s1[j] != s2[j]){
        pref = 0;
        break;
      }

    }
    
    for(j = 0;j<a;j++){
      if(s1[j] != s2[c+j]){
        suf = 0;
        break;
      }
    }
    
    if(suf || pref){
      printf("%s\n", s2);
    }
  }
  
  
  return 0;
}