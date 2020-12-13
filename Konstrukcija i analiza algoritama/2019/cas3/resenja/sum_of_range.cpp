#include <iostream>
#include <vector>
#include <cmath>

// Rekurzivna funkcija koja kreira segmentno stablo segment_tree od niza brojeva array, k predstavlja poziciju cvora unutar niza (njegov indeks), dok x i y oznacavaju krajeve intervala
// koje cvor obuhvata, na pocetku je taj interval ceo niz, a kroz rekurzvine pozive se polovi i svaki cvor pokriva manji deo pocetnog niza
void build_segment_tree (std::vector<int> &array, std::vector<int> &segment_tree, int k, int x, int y)
{
  // Ukoliko smo dosli do jednoclanog niza (list u stablu), nema vise polovnjenja intervala pa zavrsavamo rekurziju
  if (x == y) {
    // k je bas pozicija gde treba da smestimo nas element u stablu, a kako su x i y ista pozicija u nizu array mogli smo da uzmemo i array[y], nema razlike
    segment_tree[k] = array[x];
    return;
  }

  // Trazimo sredinu intervala koji smo pokrili na visem nivou, sada imamo njegov levi i desni deo koje pokrivaju potomci cvora sa viseg nivoa. Dakle ako imamo deo niza 1, 2, 3, 4
  // i roditeljski cvor C1 pokriva 1, 2, 3, 4 onda njegovi potomci C2 i C3 pokrivaju redom 1, 2 i 3, 4.
  int middle = (x + y) / 2;

  // Pozivamo rekurziju za kreiranje potomaka cvora (levo i desno)
  // Levi potomak je na poziciji 2 * k u odnosu na poziciju oca
  build_segment_tree(array, segment_tree, 2 * k, x, middle);
  // Desni potomak je na poziciji 2 * k + 1 u odnosu na poziciju oca
  build_segment_tree(array, segment_tree, 2 * k + 1, middle + 1, y);

  // Nakon sto smo kreirali oba sina, potrebno je odrediti koji broj se cuva u ocu, to je zbir brojeva potomaka (podsetiti se strukture stabla)
  // Ukoliko ne bismo imali ovu liniju, samo bi listovi imali neke vrednosti, unutrasnji cvorovi ne bi bili popunjeni na odgovarajuci nacin
  segment_tree[k] = segment_tree[2 * k] + segment_tree[2 * k + 1];
}

// Funkcija koja racuna sumu elemenata u intervalu [a, b], x i y predstavljaju krajeve pocetnog niza, k nam govori o poziciji cvora, a segment_tree[k] je suma elemenata koje cuva
// cvor na poziciji k
// Postoje 3 varijante, ili se segmenti [x,y] (koji se menja) i [a,b] ne preklapaju, onda svi elementi iz segmenta [x,y] nisu vazni za sumu pa kad dodjemo do cvora koji pokriva
// takav segment vracamo samo 0, ne doprinosi sumi ni na koji nacin. Druga opcija je da se ceo segment [x, y] nalazi unutar segmenta [a, b] onda vracamo segment_tree[k] jer bas
// taj cvor cuva sumu elemenata iz segmenta [x, y] a on ceo doprinosi sumi. I poslednja varijanta je da se segmenti preklapaju, onda delimo segment [x, y] na dva dela i idemo
// rekurzvino. Ono sto se desava je da neki od delova pokriva prvi slucaj, neki drugi slucaj pa se onda tako resavaju. Jos jedna mogucnost je da se oba podsegmenta preklapaju sa
// [a, b] pa onda njih rekurzivno razbijamo (Na casu detaljnije objasnjenje)
int sum_of_segment(std::vector<int> &segment_tree, int x, int y, int a, int b, int k)
{
  // Ukoliko nema preklapanja segmenata vracamo 0
  if (x > b || y < a)
    return 0;

  // Ukoliko se ceo [x, y] nalazi unutar [a, b] vracamo sumu koju cuva cvor koji pokriva segment [x, y], samim tim i sumu segmenta [x, y]
  if (x >= a && y <= b)
    return segment_tree[k];

  // Delimo segment [x, y] na 2 podsegmenta i problem resavamo rekurzivno za njih
  int middle = (x + y) / 2;

  return sum_of_segment(segment_tree, x, middle, a, b, 2 * k) + sum_of_segment(segment_tree, middle + 1, y, a, b, 2 * k + 1);
}

int main ()
{
  std::vector<int> array = { 1, 2, 3, 4, 5, 6, 7, 8 };

  int n = array.size();

  int height = ceil(log2(n));

  int size = 2 * pow(2, height);

  std::vector<int> segment_tree(size);

  build_segment_tree(array, segment_tree, 1, 0 , n - 1);

  std::cout << sum_of_segment(segment_tree, 0, n - 1, 0, 2, 1) << "\n";

  return 0;
}
