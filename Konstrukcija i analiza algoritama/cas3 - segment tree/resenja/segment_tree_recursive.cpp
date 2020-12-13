#include <iostream>
#include <vector>
#include <cmath>


/***************************************** ALTERNATIVNA IMPLEMENTACIJE GDE INDEKSIRANJE KRECE OD 0 *****************************************/
// Rekurzivna funkcija koja kreira segmentno stablo segment_tree od niza brojeva array, k predstavlja poziciju cvora unutar niza (njegov indeks), dok x i y oznacavaju krajeve intervala
// koje cvor obuhvata, na pocetku je taj interval ceo niz, a kroz rekurzvine pozive se polovi i svaki cvor pokriva manji deo pocetnog niza
void build_segment_tree_alternative (std::vector<int> &array, std::vector<int> &segment_tree, int k, int x, int y)
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
  // Levi potomak je na poziciji 2 * k + 1 u odnosu na poziciju oca
  build_segment_tree_alternative(array, segment_tree, 2 * k + 1, x, middle);
  // Desni potomak je na poziciji 2 * k + 2 u odnosu na poziciju oca
  build_segment_tree_alternative(array, segment_tree, 2 * k + 2, middle + 1, y);

  // Nakon sto smo kreirali oba sina, potrebno je odrediti koji broj se cuva u ocu, to je zbir brojeva potomaka (podsetiti se strukture stabla)
  // Ukoliko ne bismo imali ovu liniju, samo bi listovi imali neke vrednosti, unutrasnji cvorovi ne bi bili popunjeni na odgovarajuci nacin
  segment_tree[k] = segment_tree[2 * k + 1] + segment_tree[2 * k + 2];
}

int main ()
{
  std::vector<int> array = { 1, 2, 3, 4, 5, 6, 7, 8 };

  int n = array.size();

  int height = ceil(log2(n));

  // int size = 2 * pow(2, height);

  // Ukoliko indeksiranje ide od 0 imamo potrebu za jednim cvorom manje
  int size = 2 * pow(2, height) - 1;

  std::vector<int> segment_tree(size);

  // Za indeksiranje od 0 jedino sto se menja je pocetna vrednost k odnosno pozicija korenog cvora u nizu
  build_segment_tree_alternative(array, segment_tree, 0, 0 , n - 1);

  for (int x : segment_tree)
    std::cout << x << " ";

  std::cout << "\n";

  return 0;
}
