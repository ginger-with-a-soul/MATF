#include<stdio.h>
#include<stdlib.h>

void greska()
{
  fprintf(stderr, "-1\n");
  exit(EXIT_FAILURE);
}

/*Funkcija koja alocira niz 
 * i vraca pokazivac na prvi 
 * element niza
 */
int* alociraj1(int n){
  int* a = malloc(n * sizeof(int));
  if(a == NULL)
    greska();
  return a;
}

/*Funkcija koja alocira niz 
 *cija se adresa prosledjuje 
 * kao argument funkciji*/
void alociraj2(int** a, int n){
  *a = malloc(n * sizeof(int));
  if(*a == NULL)
    greska();
}

int main(){

  int i, n;
  int *a;

  //Ucitavamo dimenziju niza
  scanf("%d", &n);
  if(n <= 0)
    greska();
  
  //Alociramo prostor 
  a = (int*)malloc(n*sizeof(int));
  if(a == NULL)
    greska();
  
  /*
   II nacin:
   a = alociraj1(n);
   */
  
  /*
   * III nacin:
      alociraj2(&a, n);
   */
  
  //Ucitavamo elemente
  for(i=0; i<n; i++)
    scanf("%d", &a[i]);
  
  //Ispisujemo rezultat
  for(i=n-1; i >= 0; i--)
    printf("%d ", a[i]);
  printf("\n");
  
  //Oslobadjamo prethodno alocirani niz
  free(a);
  
  return 0;

}
