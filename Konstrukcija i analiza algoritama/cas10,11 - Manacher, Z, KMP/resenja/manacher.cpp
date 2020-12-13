#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

void manacher(std::string &string)
{
  // Ovo su karakteri koji ce da predstavljaju pocetak i kraj stringa.
  // Izmedju svaka 2 karaktera stringa string cemo da stavljamo # jer je to centar za palindrome parne duzine
  // Ako je string abba mi hocemo da dobijemo string $#a#b#b#a#@
  std::string pom = "$";

  // Racunamo velicinu niske
  int n = string.size();

  // Kreiramo pomocni string na odgovarajuci nacin
  for (int i = 0; i < n; i++) {
    pom += "#";
    pom += string[i];
  }

  pom += "#@";

  // C predstavlja centar (sredinu) trenutog palindroma koji razmatramo, a R njegov desni kraj
  int C = 1, R = 1;

  // Pomocni vektor u koji smestamo vrednosti najduzih palindroma ciji je centar odgovarajuca pozicija
  // Recimo ako je pom_vector[4] == 3 to znaci da je palindrom ciji je centar na poziciji 4 duzine 3, recimo aba
  std::vector<int> pom_vector(pom.size());

  // Promenljiva koja ce da predstavlja ogledalo, recimo za string aba, ogledalo desnog a je levo a, jer ako imamo palindrom sve levo od njega je isto kao i
  // desno od njega, recimo abccba, onda je a pranjak od a, b od b, c od c
  int mirror;

  n = pom.size();

  // Idemo kroz nisku, ne uzimajuci u obzir prvi karakter jer je to specijalni karakter koji predstavlja pocetak stringa
  for (int i = 1; i < pom.size() - 1; i++) {
    // Na ovaj nacin odredjujemo parnjaka odredjenog karaktera, i onda uzimamo velicinu palindroma ciji je centar na poziciji mirror
    mirror = 2 * C - i;

    // Ukoliko je podstring koji trenutno razmatramo unutar nekog veceg palindroma onda uzimamo minimum izmedju R - i i duzine palindroma
    // koja odgovara odgovarajucem "mirror" elementu
    if (i < R)
      pom_vector[i] = std::min(R - i, pom_vector[mirror]);

    // Poredimo karaktere levo i desno i onda kad god poklopimo povecavamo duzinu palindroma ciji je centar na poziciji i. Kad god poklopimo karaktere samo
    // dodajemo 1, medjutim # izmedju svaka 2 karaktera nam omogucavaju da se duzina zapravo uveca za 2
    while (pom[i + (pom_vector[i] + 1)] == pom[i - (pom_vector[i] + 1)])
      pom_vector[i]++;

    // Ako smo otisli van granica prethodnog palindroma poklapajuci odgovarajuce karaktere, onda cemo nadalje neki drugi plaindrom razmatrati kao "trenutni",
    // pa shodno tome pomeramo centar i desni kraj
    if (i + pom_vector[i] > R) {
      // Pomeramo centar trenutni
      C = i;
      // Pomeramo i desni kraj
      R = i + pom_vector[i];
    }
  }

  // // Uzimamo najvecu duzinu i poziciju gde je centar najduzeg palindroma
  // int max = pom_vector[0], max_position = 0;
  //
  // // Duzina vektora
  // n = pom_vector.size();
  //
  // // Idemo kroz niz i ako ima potrebe azuriramo max i max_position
  // for (int i = 1; i < n; i++)
  //   if (pom_vector[i] > max) {
  //     max = pom_vector[i];
  //     max_position = i;
  //   }

  // std::max_element vraca iterator na maksimalni element u nekoj kolekciji, od toga oduzimamo pocetak kolekcije da bismo zapravo dobili koja je to pozicija
  // tj indeks u kolekciji
  int max_position = std::max_element(pom_vector.begin(), pom_vector.end()) - pom_vector.begin();
  int max = pom_vector[max_position];

  // Rekonstruisemo string na osnovu duzine i pozicije centra, nalazimo pocetak i kraj, tj prvi i poslednji karakter koji pripadaju najduzoj palindromskoj
  // podnisci
  int start = max_position - max + 1;

  std::string result = "";

  int end = start + 2 * max;

  // Uzimamo svaki drugi karakter zbog #
  for (int i = start; i < end; i += 2)
    result += pom[i];

  std::cout << result << std::endl;
}

int main ()
{
  // $#a#b#a#b#a#b#a#@

  // $#a#b#a#a#b#a#@
  std::string s = "aaaaaaaaaacabaabad";

  manacher(s);

  return 0;
}
