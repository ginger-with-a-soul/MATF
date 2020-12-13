#include <iostream>
#include <vector>
#include <algorithm>

// Funkcija pomocu koje dodajemo element u stablo. Dodajemo element na odgovaraucem indeksu, i uvecavamo vrednosti svih cvorova na koje on utice
void add_to_tree(std::vector<int> &fenwick_tree, int n, int index, int value)
{
  // Uvecavamo indeks za 1 jer nam u stablu indeksiranje krece od 1, a u pocetnom nizu od 0
  index++;

  // Krecemo se dok ne dodjemo do poslednjeg cvora stabla, tj kraja niza
  while (index <= n) {
    // Odgovarajuci cvor uvecavamo
    fenwick_tree[index] += value;

    // Pomeramo indeks na sledecu vrednost indeksa na koju utice promena prethodne vrednosti
    index += index & -index;
  }
}

// Ova funkcija racuna sumu svih vrednosti [0, index - 1)
int sum_to_index(std::vector<int> &fenwick_tree, int index)
{
  int sum = 0;

  // Krecemo se uz stablo tj kroz nizs
  while (index > 0) {
    // Dodajemo na sumu odgovarajuci element
    sum += fenwick_tree[index];
    // Pomeramo indeks na odgovarajuci nacin
    index -= index & -index;
  }

  return sum;
}

// Funkcija convert ce od niza elemenata napraviti niz indeksa. Ako smo imali niz { 1, -5, 6, 2 } on ce postati { 2, 1, 4, 3 }
void convert(std::vector<int> &array, int n)
{
  // Uzimamo pomocni niz u koji smestamo nas niz
  std::vector<int> pom(array.begin(), array.end());

  // Sortiramo niz rastuce
  /********* C++ deo *********/
  // Funkcija std::sort sortira kolekciju elemenata, a kao argumente dobija pocetak, kraj kolekcije i eventualno funkciju bool compare(<T> el1, <T> el2) gde <T> predstavlja bilo koji tip
  // Ukoliko je prosledjena funkcija ona se koristi za sortiranje inace je sortiranje po default-u u rastucem poretku
  std::sort(pom.begin(), pom.end());

  // Krecemo se kroz niz elemenata i dodeljujemo odgovarajuci indeks elementu
  /********* C++ deo *********/
  // Funkcija std::lower_bound() prima pocetak kolekcije, kraj kolekcije, i jedan element. Kao rezultat vraca pokazivac na prvi element koji nije manji (veci ili jednak) datom elementu
  // Za nase potrebe mi dobijamo pokazivac na element array[i] u sortiranom nizu, a nakon toga pomocu std::distance trazimo koliko je on daleko od pocetka
  // Funkcija std::distance() vraca udaljenost elementa iz kolekcije od pocetka kolekcije. Kao argumente dobija iterator na pocetak (begin()) i iterator (pokazivac) na element za koji
  // se trazi udaljenost (kod nas povratna vrednost funkcije std::lower_bound()). Dodajemo 1, jer ako je nas element na pocetku kolekcije std::distance vraca 0, a mi indeksiranje zelimo
  // od 1.
  for (int i = 0; i < n; i++) {
    array[i] = std::distance(pom.begin(), std::lower_bound(pom.begin(), pom.end(), array[i])) + 1;
  }
}

int main ()
{
  std::vector<int> array = { 7, -90, 100, 1 };

  int n = array.size();

  int max = *std::max_element(array.begin(), array.end());

  std::vector<int> fenwick_tree(n + 1);

  std::fill(fenwick_tree.begin(), fenwick_tree.end(), 0);

  int result = 0;

  convert(array, n);

  for (int i = n - 1; i >= 0; i--) {
    result += sum_to_index(fenwick_tree, array[i]);

    add_to_tree(fenwick_tree, n, array[i] - 1, 1);
  }

  std::cout << result << std::endl;

  return 0;
}
