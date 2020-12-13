#include <stdio.h>
#include <stdlib.h>

#define MAX_LINIJA 81

void greska();

void greska(){
  fprintf(stderr, "-1\n"); /*fprintf za argument ima mesto gde stampa
                            (u ovom slucaju to je izlaz za greske
                            ali moze da bude i neki nas fail (pokazivac na otvoreni fajl)).
                            Drugi argument je sta stampa*/
  exit(EXIT_FAILURE);
}

int main(){
  
  FILE *ulaz, *izlaz; /*promenljiva 'ulaz' u ovoj deklaraciji biva obelezena kao fajl.
                        Zbog toga nije potrebno staviti FILE *fopen(_,_),
                        kako i jeste normalna forma funkcije fopen*/
  
  ulaz = fopen("ulaz.txt", "r"); /*fopen je funkcija za otvaranje fajlova.
                                  Na prvom mestu navodi se mesto do fajla koji se otvara.
                                  Ako se a.out naseg programa i fajl koji se otvara                                         nalaze
                                  u istom folderu onda je dovoljno staviti samo ime fajla.
                                  Putanja: "..//ulaz.txt" se koristi za roditeljski fajl.
                                  Putanja: "//home//dimitrije//Desktop//cas 1//ulaz.txt" bi bila apsolutna putanja
                                  Na drugom mestu je mod otvaranja.
                                  Sa r je read, w write, rb i wb su analogni ali za slike*/
                                                                    
                                                                    
  if(ulaz == NULL){
    greska();
  }
  
  izlaz = fopen("//home//dimitrije//Desktop/cas 1//izlazi//izlaz1.txt", "w");
  
  if(ulaz == NULL){
    greska();
  }
  
  char mod;
  printf("Kucaj:\n1 za slovo po slovo prvi nacin\n2 slovo po slovo drugi nacin\n3 liniju po liniju\n");
  scanf("%c", &mod);
  
  if(mod == '1'){
    char c;
    while(fscanf(ulaz, "%c", &c) == 1){
      fprintf(izlaz, "%c", c);
    }                                   /*fscanf funckija skenira iz fajla.
                                        Argument joj je pokazivac na nas fajl odakle hocemo da cita
                                        a ne ime naseg fajla. Drugi argumenti su joj isti kao kod scanf.
                                        Ovo while ce se vrteti sve dok ne dodje do kraja fajla odakle se cita
                                        odnosno do EOFa koji ima vrednost -1 dok sve ostalo sto nije EOF ima vrednost 1*/
  }
  else if(mod == '3'){
    char linija[MAX_LINIJA];
    while(fgets(linija, MAX_LINIJA, ulaz) != NULL){ /*fgets funkcija upisuje string duzine koju mu mi odredimo iz
                                                    datoteke. Kao argument ima mesto gde upisuje, velicinu tog upisa
                                                    kao i mesto odakle cita taj upis*/
      fprintf(izlaz, "%s", linija);
    }
  }
  else if(mod == '2'){
    char c;
    while((c = fgetc(ulaz)) != EOF){
      fputc(c, izlaz); /*fgetc funkcija cita iz datoteke koja joj je
                        navedena pokazivacem dok fputc upisuje u datoteku koju hocemo.
                        Argument fputc je char koji upisuje i mesto gde ga upisuje*/
    }
  }
  else{
    greska();
  }
  
  fclose(ulaz);
  fclose(izlaz);
  
  return 0;
}