#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>

void greska()
{
  fprintf(stderr, "-1\n");
  exit(EXIT_FAILURE);
}

int provera_razlomka(char* razlomak){
  int i, crte = 0;
  
  /*
   * -Proveravamo da li su svi karakteri cifre ili / i
   *  ako nisu, vracamo 0.
   * -Pamtimo koliko puta se pojavila razlomacka crta
   */
  for(i=0; razlomak[i]; i++)
  {
    if(!isdigit(razlomak[i]) && razlomak[i] != '/')
      return 0;
    
    if(razlomak[i] == '/')
      crte++;
  }
  
  /*
   * - Vracamo nulu ukoliko se razlomacka crta javlja na prvom mestu,
   *   na poslednjem mestu, ako se ne pojavljuje uopste ili ukoliko se
   *   pojavljuje vise od jednom.
   */
  if(razlomak[0] == '/' || razlomak[i-1] == '/' || crte != 1)
    return 0;

  /*Razlomak je ispravan - vracamo 1*/
  return 1;
}

int main(int argc, char* argv[])
{
  int i, brojilac, imenilac;
  
  //Provera ispravnosti svih argumenata
  for(i=1; i<argc; i++)
  {
    if(!provera_razlomka(argv[i]))
      greska();
  }
  
  //Ispis rezultata:
  for(i=1; i<argc; i++){
    sscanf(argv[i], "%d/%d", &brojilac, &imenilac);
    printf("%.2f ", (float)brojilac/imenilac);
  }
  printf("\n");
  
}
