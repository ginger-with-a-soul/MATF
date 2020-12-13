#include <stdio.h>

#define MAX 100

void ucitaj(int a[], int n);
void stampaj(int a[], int n);
int suma(int a[], int n);
float prosek(int a[], int n);
int minimum(int a[], int n);
int prva_pozicija_max_elementa(int a[], int n);

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

int suma(int a[], int n){
  int i = 0, suma1 = 0;
  for(i = 0;i<n;i++){
    suma1 += a[i];
  }
  return suma1;
}

float prosek(int a[], int n){
  return (float)suma(a, n)/n;
}

int minimum(int a[], int n){
  int i = 0, min = a[0];
  for( i = 0;i<n;i++){
    if(min>a[i]){
      min = a[i];
    }
  }
  return min;
}

int prva_pozicija_max_elementa(int a[], int n){
  int i = 0, pozicija = 0, max = a[0];
  for(i = 0;i<n;i++){
    if(max<a[i]){
     pozicija = i;
    }
  }
  return pozicija;
}

int main(){
  int n, a[MAX];
  scanf("%i", &n);
  if(n<1 || n>MAX){
    printf("-1\n");
    return -1;
  }
  
  ucitaj(a, n);
  stampaj(a, n);
  printf("\n");
  
  printf("%i\n",suma(a, n));
  
  printf("%.2f\n", prosek(a, n));
  
  printf("%i\n", minimum(a, n));
  
  printf("%i\n", prva_pozicija_max_elementa(a, n));
  
  
  return 0;
}