#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_REC 21

void greska()
{
    fprintf(stderr, "-1\n");
    exit(EXIT_FAILURE);
}

int main(int argc, char* argv[])
{
    /*Provera broja argumenata komendne linije*/
    if(argc != 2)
      greska();
    
    /*Otvaramo fajl koji se zadaje kao prvi argument komandne linije*/
    FILE* ulaz = fopen(argv[1], "r");
    if(ulaz == NULL)
      greska();
    
    /*
     * Deklarisemo promenljive koje cemo koristiti za funkciju getline.
     * Kada koristimo ovu funkciju ne moramo da vodimo racuna o alokaciji prostora za
     * cuvanje ucitane linije - ova funkcija ce to uraditi za nas. 
     * Ako je pozovemo sa:
     *      getline(&linija, &duzina_linije, ulaz)
     * -Ako linija ima vrednost NULL i ako je *duzina_linije = 0, onda ce ova funkcija
     * odraditi potrebnu alokaciju i u promenljivu duzina_linije upisati koliko 
     * memorije je bilo potrebno za smestanje ucitane linije.
     * -Ako je linija neki pokazivac koji je prethodno vec alociran, onda ce funkcija getline
     * ucitavati u tu memoriju i po potrebi odraditi realokaciju i azurirati vrednost promenlive
     * duzina_linije
     * 
     * Po potpisu funkcije getline:
     * ssize_t getline(char **lineptr, size_t *n, FILE *stream);
     * mozemo videti da je drugi argument size_t*. Ovaj tip najcesce odgovara tipu unsigned long*. 
     * Jedna opcija je da se deklarise:
     * unsigned_long duzina_linije = 0;
     * Druga opcija je da se deklarise
     * size_t duzina_linije = 0;
     * Funkciji zatim treba proslediti adresu ove promenljive, kako bi tu mogao da se upise broj
     * ucitanih karaktera
     * 
     * Treci argument je fajl iz kog se cita
     */
    char* linija = NULL;
    unsigned long duzina_linije = 0;
    
    
    int procitano, k, brojac;
    int n;
    char rec[MAX_REC], uneta_rec[MAX_REC];
    
    /*Ucitavamo rec koju zelimo da trazimo, kao i potreban broj pojavljivanja te reci*/
    scanf("%d%s", &n, uneta_rec);
    if(n < 0)
      greska();
    
    /*Citamo liniju po liniju koriscenjem funkcije getline */
    while(getline(&linija, &duzina_linije, ulaz) != EOF)
    {
      /*Vracamo brojace na 0*/
      procitano = 0;
      brojac = 0;
      
      /* Pomeramo se rec po rec po samoj liniji i proveravamo da li je 
       * tekuca rec jednaka unetoj reci i ako jeste, uvecavamo odgovarajuci brojac
       * 
       * Ovo radimo koriscenjem funkcije sscanf.
       * Za razliku od fscanf-a i scanf-a koji imaju mehanizam da se zapamti gde se stalo sa citanjem
       * i da se pri sledecem pozivu citanje nastavlja od tog mesta, ovako nesto ne postoji kod
       * sscanf-a i iz tog razloga, sami moramo da obezbedimo da nam ovo citranje radi ispravno.
       * 
       * Ako pozovemo 
       * sscanf("cao svima", "%s%n", rec, &broj);
       * U promenljivoj rec ce biti smesteno "cao", a u promenljivu broj 3
       * Znaci, sa ovim %n mozemo da sacuvamo koliko karaktera je obradjeno tekucim pozivom sscanf-a.
       * Tako da ako sledeci put pozovemo sa:
       * sscanf("cao svima" + 3, "%s%n", reci, &broj);
       * zapravo vrsimo poziv:
       * sscanf(" svima", "%s%n", reci, &broj);
       * u ovom slucaju, u promenljivu rec ce biti upisano "svima", a u broj 6 
       *                            (racuna se i ona belina koja je preskocena)
       * 
       * Tako da cemo mi imati promenljivu procitano, koju na pocetku ove petlje postavljamo na 0,
       * a zatim je povecavamo za broj procitanih karaktera i u svakoj iteraciji petlje citamo sa 
       * linija + procitano
       */
      while(sscanf(linija + procitano, "%s%n", rec, &k) != EOF)
      {
        procitano += k;
        if(strcmp(rec, uneta_rec) == 0)
          brojac++;
      }
      
      /*
       * Ako je brojac jednak trazenom broju pojavljivanja,
       * ispisujemo tekucu liniju na standardni izlaz
       */
      if(brojac == n)
        printf("%s", linija);
    }
    
    fclose(ulaz);
    free(linija);
	return 0;
}
