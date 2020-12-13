#include <iostream>
#include <vector>
#include <string>

void manacher (std::string &string, std::vector<int> &pom_vector)
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
  pom_vector.resize(pom.size());

  // Promenljiva koja ce da predstavlja ogledalo, recimo za string aba, ogledalo desnog a je levo a, jer ako imamo palindrom sve levo od njega je isto kao i
  // desno od njega, recimo abccba, onda je a pranjak od a, b od b, c od c
  int mirror;

  n = pom.size();

  // Idemo kroz nisku, ne uzimajuci u obzir prvi karakter jer je to specijalni karakter koji predstavlja pocetak stringa
  for (int i = 1; i < pom.size() - 1; i++) {
    // Na ovaj nacin odredjujemo parnjaka odredjenog karaktera, i onda uzimamo velicinu palindroma ciji je centar na poziciji mirror
    mirror = 2 * C - i;

    // Ukoliko je podstring koji trenutno razmatramo unutar trenutnog glavnog palindroma onda uzimamo minimum izmedju R - i i duzine palindroma
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

  // Uzimamo najvecu duzinu i poziciju gde je centar najduzeg palindroma
  int max = pom_vector[0], max_position = 0;

  // Duzina vektora
  n = pom_vector.size();

  // Idemo kroz niz i ako ima potrebe azuriramo max i max_position
  for (int i = 1; i < n; i++)
    if (pom_vector[i] > max) {
      max = pom_vector[i];
      max_position = i;
    }

  // for (char c : pom)
  //   std::cout << c << " ";
  // std::cout << std::endl;
  //
  // for (int x : pom_vector)
  //   std::cout << x << " ";
  //
  // std::cout << "\n";
}

// Funkcija koja ce prebrojavati na koliko nacina mozemo da podelimo pocetni string tako da svi delovi budu palindromi
int count (int i, int n, std::vector<int> &manacher_vector, std::vector<int> &result)
{
  // std::cout << i << ":\n";
  //
  // for (int x : result)
  //   std::cout << x << " ";
  //   std::cout << "\n";

  // Ako dodjemo do kraja niske vracamo samo 1
  if (i == n)
    return 1;

  // Ako dodjemo u situaciju da smo vec odredili result za neki element nema potrebe racunati to ponovo mozemo da iskoristimo informaciju koju smo izracunali
  if (result[i] != -1)
    return result[i];

  // Na pocetku je broj kombinacija 0, a zatim cemo izracunati koliko ih zapravo ima
  int sum = 0;

  // Krecemo se kroz podnisku niske s pocevsi od pozicije i rekurzivno pretrazujemo broj kombinacija
  for (int j = i; j < n; j++) {
    // Ako podniska s[i, j] jeste palindrom broj kombinacija se uvecava za broj K koji oznacava na koliko nacina mozemo nisku s[j + 1, n - 1] da podelimo
    // na zahtevani nacin
    // manacher_vector[i + j + 2] >= (j - i + 1) govori da li je niska s[i, j] palindrom ili ne, ako jeste imamo 1 * broj kombinacija u ostatku niske, inace 0
    sum += (manacher_vector[i + j + 2] >= (j - i + 1)) * count(j + 1, n, manacher_vector, result);
  }

  result[i] = sum;

  return sum;
}

int main ()
{
  // $#a#b#a#b#a#b#a#@

  // $#a#b#a#a#b#a#@
  std::string s = "ababa";

  // Vektor ciji ce i-ti element govoriti na koliko nacina mozemo da podelimo podnisku niske s s[i, n - 1] tako da svi podstringovi budu palindromi
  // Npr ako je result[2] == 3 to znaci da nisku s[2, n] mozemo podeliti na 3 nacina tako da zadovoljava dati uslov
  std::vector<int> result;

  // Velicina vektora result je ista kao i velicina niske
  result.resize(s.size());

  // Na pocetku su svi elementi -1
  std::fill(result.begin(), result.end(), -1);

  // Vektor koji se koristi u manacher-ovom algoritmu
  std::vector<int> manacher_vector;

  manacher(s, manacher_vector);

  std::cout << count(0, s.size(), manacher_vector, result) << std::endl;

  return 0;
}
