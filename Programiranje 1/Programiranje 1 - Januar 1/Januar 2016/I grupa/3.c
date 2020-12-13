#include <stdio.h>

#define MAX 100

int main(){
  int n, m, i[MAX], j[MAX], k, br = 0, v, r, a, b, mina = 0, z = 0;
  
  scanf("%i %i", &n, &m);
  
  if(n<1 || m<1 || n>MAX || m>MAX){
    printf("-1\n");
    return -1;
  }
  
  scanf("%i", &k);
  
  if(k<1 || k>m*n){
    printf("-1\n");
    return -1;
  }
  
  for(br = 0;br<k;br++){
    scanf("%i %i", &i[br], &j[br]);
    if(i[br]<0 || j[br]<0 || i[br]>=n || j[br]>=m){
      printf("-1\n");
      return -1;
    }
  }
  
  scanf("%i %i", &v, &r);
  
  for(a = v-1;a<=v+1;a++){
    for(b = r-1;b<=r+1;b++){
      for(z = 0;z<br;z++){
        if(a==i[br] || b==j[br]){
          mina++;
        }
      }
    }
  }
  
  for(br = 0;br<k;br++){
    if(i[br]==v && j[br]==r){
      printf("\nMINA\n");
      return 1;
    }
  }
  
  printf("\n%i\n", mina);
  
  return 0;
}