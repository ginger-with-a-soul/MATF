#include <iostream>
#include <vector>
#include <cmath>
#include <climits>

// Rekurzivna funkcija koja kreira segmentno stablo segment_tree od niza brojeva array, k predstavlja poziciju cvora unutar niza (njegov indeks), dok x i y oznacavaju krajeve intervala
// koje cvor obuhvata, na pocetku je taj interval ceo niz, a kroz rekurzvine pozive se polovi i svaki cvor pokriva manji deo pocetnog niza
void build_segment_tree(std::vector<int> &array, std::vector<int> &segment_tree, int k, int x, int y)
{
  // Ukoliko smo dosli do jednoclanog niza (list u stablu), nema vise polovnjenja intervala pa zavrsavamo rekurziju
  if (x == y) {
    // k je bas pozicija gde treba da smestimo nas element u stablu, a kako su x i y ista pozicija u nizu array mogli smo da uzmemo i array[y], nema razlike
    segment_tree[k] = array[x];
  	return ;
  }

  // Trazimo sredinu intervala koji smo pokrili na visem nivou, sada imamo njegov levi i desni deo koje pokrivaju potomci cvora sa viseg nivoa. Dakle ako imamo deo niza 1, 2, 3, 4
  // i roditeljski cvor C1 pokriva 1, 2, 3, 4 onda njegovi potomci C2 i C3 pokrivaju redom 1, 2 i 3, 4.
  int middle = (x + y) / 2;

  // Pozivamo rekurziju za kreiranje potomaka cvora (levo i desno)
  // Levi potomak je na poziciji 2 * k + 1 u odnosu na poziciju oca
  build_segment_tree(array, segment_tree, 2 * k + 1, x, middle);
  // Desni potomak je na poziciji 2 * k + 2 u odnosu na poziciju oca
  build_segment_tree(array, segment_tree, 2 * k + 2, middle + 1, y);

  // Nakon sto smo kreirali oba sina, potrebno je odrediti koji broj se cuva u ocu, to je vrednost potomka koji ima vecu vrednost
  // Ukoliko ne bismo imali ovu liniju, samo bi listovi imali neke vrednosti, unutrasnji cvorovi ne bi bili popunjeni na odgovarajuci nacin
  // Koristimo funkciju std::max koja vraca veci od svojih argumenata
  segment_tree[k] = std::max(segment_tree[2 * k + 1], segment_tree[2 * k + 2]);
}

// Nama je u ovom zadatku sustinski potrebno samo da odredimo sumu elemenata segmenta, posto gde god imamo paran broj imamo 1 u listu, tamo 
// gde su neparni brojevi u listovima su 0, tako da racunanjem proste sume ovih 0 i 1 dolazimo zapravo do broja parnih brojeva u segmentu
int max_element_in_segment(std::vector<int> &segment_tree, int x, int y, int a, int b, int k)
{
  // Ukoliko nema preklapanja segmenata vracamo MIN_INT jer su svi brojevi veci od tog broja
  // Kada imamo zbir i nema preklapanja doprinos tog segmenta je 0, ovde zelimo da kazemo da ovaj segment nije vazan za konacni rezultat
  if (x > b || y < a)
    return INT_MIN;

  // Ukoliko se ceo [x, y] nalazi unutar [a, b] vracamo maksimalni element u segmentu [x,y]
  if (x >= a && y <= b)
    return segment_tree[k];

  // Delimo segment [x, y] na 2 podsegmenta i problem resavamo rekurzivno za njih
  int middle = (x + y) / 2;

  return std::max(max_element_in_segment(segment_tree, x, middle, a, b, 2 * k + 1), max_element_in_segment(segment_tree, middle + 1, y, a, b, 2 * k + 2));
}

int main ()
{
  std::vector<int> array = { 1, 2, 3, 4, 5, 6, 7, 8 };

  int n = array.size();

  int height = ceil(log2(n));

  // Ukoliko indeksiranje ide od 0 imamo potrebu za jednim cvorom manje
  int size = 2 * pow(2, height) - 1;

  std::vector<int> segment_tree(size);

  build_segment_tree(array, segment_tree, 0, 0, n - 1);

  int a, b;

  std::cin >> a >> b;

  std::cout << max_element_in_segment(segment_tree, 0, n - 1, a, b, 0) << "\n";

  return 0;
}