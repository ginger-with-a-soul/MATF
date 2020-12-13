#include <stdio.h>

#define MAX 100

void ucitaj(int a[], int n);
void stampaj(int a[], int n);
void uvecaj(int a[], int n, int m);
void obrni(int a[], int n);
void rotiraj_ulevo(int a[], int n);
void rotiraj_za_k_mesta_ulevo(int a[], int n, int k);


void ucitaj(int a[], int n){
  int i = 0;
  for(i = 0;i<n;i++){
    scanf("%i", &a[i]);
  }
  
}

void stampaj(int a[], int n){
  int i = 0;
  for(i = 0;i<n;i++){
    printf("%i ", a[i]);
  }
}

void uvecaj(int a[], int n, int m){
  int i = 0;
  for(i = 0;i<n;i++){
    a[i] += m;
  }
  
}

void obrni(int a[], int n){
  int i = 0, j = n-1, z;
  for(i = 0, j = n-1;i<j;i++, j--){
    z = a[i];
    a[i] = a[j];
    a[j] = z;
  }
}

void rotiraj_ulevo(int a[], int n){
  int cuvar_prvog_elementa, i = 0;
  cuvar_prvog_elementa = a[0];
  for(i = 0;i<n;i++){
    a[i] = a[i+1];
  }
  a[n-1] = cuvar_prvog_elementa;
}

void rotiraj_za_k_mesta_ulevo(int a[], int n, int k){
  int cuvar_prvog_elementa, i = 0, j = 0;
  for(i = 0;i<k;i++){
    cuvar_prvog_elementa = a[0];
    for(j = 0;j<n;j++){
      a[j] = a[j+1];
    }
    a[n-1] = cuvar_prvog_elementa;
  }
}

int main(){
  
  int n, a[MAX], m, k;
  
  scanf("%i", &n);
  if(n<1 || n>100){
    printf("-1\n");
    return -1;
  }
  
  ucitaj(a, n);
  stampaj(a, n);
  printf("\n");
  
  scanf("%i", &m);
  uvecaj(a, n, m);
  stampaj(a, n);
  printf("\n");
  
  obrni(a, n);
  stampaj(a, n);
  printf("\n");
  
  rotiraj_ulevo(a, n);
  stampaj(a, n);
  printf("\n");
  
  scanf("%i", &k);
  if(k<0){
    printf("-1\n");
    return -1;
  }
  rotiraj_za_k_mesta_ulevo(a, n, k);
  stampaj(a, n);
  printf("\n");
  
  
return 0;
}