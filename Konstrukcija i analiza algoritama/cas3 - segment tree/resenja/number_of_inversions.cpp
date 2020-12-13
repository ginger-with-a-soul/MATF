/* Osnovna ideja: Zamislimo da zapravo imamo niz svih brojeva [1, max] gde je max najveci element u nizu array. I onda idemo kroz niz i za svaki element array[i] stavljamo 1
na odgovarajucu poziciju (onu koja bi odgovarala bas tom elementu u stablu) u stablu. U svakoj iteraciji petlje koja ide kroz elemente niza array trazimo koliko elemenata iz intervala
[array[i] + 1, max] imamo vec u stablu. Sta time dobijamo? Broj koji dobijemo zapravo govori koliko vecih elemenata je vec smesteno u stablo, tj koliko vecih elemenata ima manji indeks
od i-tog elementa niza array. */
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

// Funkcija koja ce vracati broj onih elemenata koji su veci od array[i] a vec su u stablu. Dakle funkcija koja racunu sumu elemenata iz intervala [array[i] + 1, max]
int count_inversions_in_segment(std::vector<int> &segment_tree, int k, int x, int y, int a, int b)
{
  // Ukoliko nema preklapanja segmenata vracamo 0
  if (x > b || y < a)
    return 0;

  // Ukoliko se ceo [x, y] nalazi unutar [a, b] vracamo sumu koju cuva cvor koji pokriva segment [x, y], samim tim i sumu segmenta [x, y]
  if (x >= a && y <= b)
    return segment_tree[k];

  // Delimo segment [x, y] na 2 podsegmenta i problem resavamo rekurzivno za njih
  int middle = (x + y) / 2;

  return count_inversions_in_segment(segment_tree, 2 * k, x, middle, a, b) + count_inversions_in_segment(segment_tree, 2 * k + 1, middle + 1, y, a, b);
}

// Funkcija koja ce samo dodati odgovarajuci element u stablo. Ako je array[i] = 12 onda cemo na poziciju gde bi trebalo da bude smesten broj 12 u stablu koje ima brojeve [1, max]
// smestiti broj 1, sto oznacava broj 12 se javlja u nizu array. Promenljiva index zapravo predstavlja array[i], tj odgovarajucu poziciju gde treba smestiti element
void add_element_to_tree(std::vector<int> &segment_tree, int k, int x, int y, int index)
{
  // Ukoliko dodjemo do lista, na poziciju k  ustablu stavljamo 1, jer je bas to pozicija gde treba staviti oznaciti da se array[i] javlja
  if (x == y) {
    segment_tree[k] = 1;
    return ;
  }

  // Delimo segment na 2 dela
  int middle = (x + y) / 2;

  // Usmeravamo pretragu u jednu stranu jer samo jedan element dodajemo. Ekvivalentno je kao da azuriramo zapravo element stabla pa usmeravamo pretragu
  if (index <= middle)
    add_element_to_tree(segment_tree, 2 * k, x, middle, index);
  else
    add_element_to_tree(segment_tree, 2 * k + 1, middle + 1, y, index);

  // Azuriramo sve cvorove na putu od korena do lista koji je izmenjen

  segment_tree[k] = segment_tree[2 * k] + segment_tree[2 * k + 1];
}

int main ()
{
  // std::vector<int> array = { 3, 5, 1, 4, 6, 2, 4, 7, 8, 2, 3, 4 };

  std::vector<int> array = { 8, 4, 2, 1 };

  int n = array.size();

  /********* C++ deo *********/
  // Funckija max_element() vraca iterator(pokazivac) na element koji je zapravo maksimalan element u kolekciji. Ukoliko kolekcija nije primitivnog tipa (int, float, double, bool...)
  // moramo svoj komparator za odgovarajuci tip da definisemo, kao operator() sa casa 2
  int max = *std::max_element(array.begin(), array.end());

  int height = ceil(log2(max));

  int size = 2 * pow(2, height);

  std::vector<int> segment_tree(size);

  /********* C++ deo *********/
  // Funkcija std::fill() prima iterator na pocetak kolekcije i kraj kolekcije i vrednost kojom treba popuniti celu kolekciju
  std::fill(segment_tree.begin(), segment_tree.end(), 0);

  int result = 0;

  for (int i = 0; i < n; i++) {
      result += count_inversions_in_segment(segment_tree, 1, 1, max, array[i] + 1, max);

      add_element_to_tree(segment_tree, 1, 1, max, array[i]);
  }

  std::cout << result << std::endl;

  return 0;
}
