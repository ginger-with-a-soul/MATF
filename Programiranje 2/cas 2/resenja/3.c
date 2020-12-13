#include<stdio.h>
#include<stdlib.h>

void greska()
{
  fprintf(stderr, "-1\n");
  exit(EXIT_FAILURE);
}

int main(int argc, char* argv[]){

  if(argc != 2)
    greska();
  
  int i, n, alocirano;
  int *a;
  
  //Citamo korak k i proveravamo gresku
  int k = atoi(argv[1]);
  if(k <= 0)
    greska();
  
  //Alociramo pocetnih k mesta 
  a = (int*)malloc(k*sizeof(int));
  if(a == NULL)
    greska();
  
  alocirano = k;
  //Orvaramo fajl brojevi.txt za citanje
  FILE* ulaz = fopen("brojevi.txt", "r");
  if(ulaz == NULL)
    greska();
  
  //Ucitavamo elemente
  i = 0;
  while(1){
    
    if(i == alocirano){
        //Popunili smo sva mesta u alociranom nizu --> treba da alociramo dodatni prostor
        alocirano += k;
        /*Funkcija realloc kao drugi argument prima UKUPAN prostor koji nam je potreban,
         a ne dodatni prostor, tako da iz tog razloga prvo uvecavamo vrednost promenljive
         alocirano, a zatim pozivamo funkciju realloc.*/
        a = realloc(a, alocirano*sizeof(int));
        if(a == NULL)
          greska();
    }
    fscanf(ulaz, "%d", &a[i]);
    if(a[i] == 0)
      break;
    i++;
  }
  
  n = i;
  
  //Racunamo srednji element
  float srednji;
  if(n%2 == 0)
    srednji = (a[n/2-1] + a[n/2])/2.0;
  else
    srednji = a[n/2];
  
  //Ispisujemo rezultat
  for(i=0; i<n; i++)
    if(a[i] > srednji)
      printf("%d ", a[i]);
  printf("\n");
  
  //Oslobadjamo prethodno alocirani niz
  free(a);
 
  //Zatvaramo datoteku
  fclose(ulaz);
  return 0;

}
