#include <iostream>
#include <vector>
#include <cmath>
#include <climits>

// Napravicemo strukturu Node koja predstavlja cvor prefiksnog stabla, i u njoj cuvamo najvecu i drugu najvecu vrednost iz tog segmenta koji cvor pokriva
struct Node
{
  int largest;
  int second_largest;
};

// Rekurzivna funkcija koja kreira segmentno stablo segment_tree od niza brojeva array, k predstavlja poziciju cvora unutar niza (njegov indeks), dok x i y oznacavaju krajeve intervala
// koje cvor obuhvata, na pocetku je taj interval ceo niz, a kroz rekurzvine pozive se polovi i svaki cvor pokriva manji deo pocetnog niza
void build_segment_tree (std::vector<int> &array, std::vector<Node> &segment_tree, int k, int x, int y)
{
  // Ukoliko smo dosli do jednoclanog niza (list u stablu), nema vise polovnjenja intervala pa zavrsavamo rekurziju
  if (x == y) {
    // Kazemo da je najveca vrednost u segmentu koji pokriva list (samo taj 1 cvor) bas vrednost array[x]/array[y], a druga najveca je INT_MIN, jer se svaka vrednost sigurno veca od nje
    segment_tree[k].largest = array[x];
    segment_tree[k].second_largest = INT_MIN;
    return ;
  }

  // Trazimo sredinu intervala koji smo pokrili na visem nivou, sada imamo njegov levi i desni deo koje pokrivaju potomci cvora sa viseg nivoa. Dakle ako imamo deo niza 1, 2, 3, 4
  // i roditeljski cvor C1 pokriva 1, 2, 3, 4 onda njegovi potomci C2 i C3 pokrivaju redom 1, 2 i 3, 4.
  int middle = (x + y) / 2;

  // Pozivamo rekurziju za kreiranje potomaka cvora (levo i desno)
  // Levi potomak je na poziciji 2 * k u odnosu na poziciju oca
  build_segment_tree(array, segment_tree, 2 * k, x, middle);
  // Desni potomak je na poziciji 2 * k + 1 u odnosu na poziciju oca
  build_segment_tree(array, segment_tree, 2 * k + 1, middle + 1, y);

  // Potrebno je azurirati najvecu i drugu najvecu vrednost u segmentu koji cvor pokriva
  // Najveca je jednaka max(left->largest, rigth->largest), a druga najveca je min(max(left->largest, right->second_largest), max(left->second_largest, right->largest))
  // Ovde je u pitanju min zato sto je max jednak vecem od dva largest elementa koji se cuva u node->largest
  /********* C++ deo *********/
  // Funkcije std::max(el, el) i std::min(el, el) vracaju veci odnosno manji od dva prosledjena elementa
  segment_tree[k].largest = std::max(segment_tree[2 * k].largest, segment_tree[2 * k + 1].largest);

  segment_tree[k].second_largest = std::min(std::max(segment_tree[2 * k].largest, segment_tree[2 * k + 1].second_largest),
                                            std::max(segment_tree[2 * k].second_largest, segment_tree[2 * k + 1].largest));
}

// Funkcija koja ce nalaziti koji je najveci proizvod u intervalu [a, b]. To cemo raditi tako sto cemo naci maksimalna 2 elementa u tom intervalu, sto radimo slicno kao sto racunamo
// sumu elemenata u intervalu
Node find_max_product_in_segment (std::vector<Node> &segment_tree, int k, int x, int y, int a, int b)
{
  Node result;
  result.largest = INT_MIN;
  result.second_largest = INT_MIN;

  // Ukoliko nema preklapanja vracamo cvor kome su i largest i second_largest jednaki INT_MIN
  if (a > y || b < x) {
    return result;
  }

  if (x >= a && y <= b)
    return segment_tree[k];

  // Delimo interval na 2 dela
  int middle = (x + y) / 2;

  // Pozivamo rekurzvino funkciju za levu i desnu polovinu segmenta, i dobijamo 2 najveca broja iz njih. Zatim na osnovu tih vrednosti odredjujemo najveci i drugi najveci element u
  // cvoru segment_tree[k]
  Node left = find_max_product_in_segment(segment_tree, 2 * k, x, middle, a, b);
  Node right = find_max_product_in_segment(segment_tree, 2 * k + 1, middle + 1, y, a, b);

  // Potrebno je azurirati najvecu i drugu najvecu vrednost u segmentu koji cvor pokriva
  // Najveca je jednaka max(left->largest, rigth->largest), a druga najveca je min(max(left->largest, right->second_largest), max(left->second_largest, right->largest))
  // Ovde je u pitanju min zato sto je max jednak vecem od dva largest elementa koji se cuva u node->largest
  /********* C++ deo *********/
  // Funkcije std::max(el, el) i std::min(el, el) vracaju veci odnosno manji od dva prosledjena elementa
  result.largest = std::max(left.largest, right.largest);

  result.second_largest = std::min(std::max(left.largest, right.second_largest),
                                            std::max(left.second_largest, right.largest));

  return result;
}

// Funkcija koja ce azurirati stablo na odgovarajuci nacin
void update_tree(std::vector<Node> &segment_tree, int k, int x, int y, int index, int new_value)
{
  // Ukoliko smo dosli do lista do kog smo zeleli da dodjemo, azuriramo njegove vrednosti
  if (x == y) {
    segment_tree[k].largest = new_value;
    segment_tree[k].second_largest = INT_MIN;
    return ;
  }

  // Delimo segment na 2 dela
  int middle = (x + y) / 2;

  // Kako zelimo tacno jedan list da azuriramo usmeravamo pretragu
  if (index <= middle)
    update_tree(segment_tree, 2 * k, x, middle, index, new_value);
  else
    update_tree(segment_tree, 2 * k  + 1, middle + 1, y, index, new_value);

  // Potrebno je azurirati najvecu i drugu najvecu vrednost u segmentu koji cvor pokriva
  // Najveca je jednaka max(left->largest, rigth->largest), a druga najveca je min(max(left->largest, right->second_largest), max(left->second_largest, right->largest))
  // Ovde je u pitanju min zato sto je max jednak vecem od dva largest elementa koji se cuva u node->largest
  /********* C++ deo *********/
  // Funkcije std::max(el, el) i std::min(el, el) vracaju veci odnosno manji od dva prosledjena elementa
  segment_tree[k].largest = std::max(segment_tree[2 * k].largest, segment_tree[2 * k + 1].largest);

  segment_tree[k].second_largest = std::min(std::max(segment_tree[2 * k].largest, segment_tree[2 * k + 1].second_largest),
                                            std::max(segment_tree[2 * k].second_largest, segment_tree[2 * k + 1].largest));
}

// Funkcija koja azurira odgovarajuci element u nizu array, i onda poziva funkciju update_tree() koja ce azurirati i stablo.
void update_array(std::vector<int> &array, std::vector<Node> &segment_tree, int index, int new_value)
{
  array[index] = new_value;

  update_tree(segment_tree, 1, 0, array.size() - 1, index, new_value);
}

int main ()
{
  std::vector<int> array = { 1, 3, 4, 2, 5 };

  int n = array.size();

  int height = ceil(log2(n));

  int size = 2 * pow(2, height);

  std::vector<Node> segment_tree(size);

  build_segment_tree(array, segment_tree, 1, 0, n - 1);

  Node result = find_max_product_in_segment(segment_tree, 1, 0, n - 1, 0, 2);

  std::cout << result.largest * result.second_largest << std::endl;

  update_array(array, segment_tree, 1, 6);

  result = find_max_product_in_segment(segment_tree, 1, 0, n - 1, 0, 2);

  std::cout << result.largest * result.second_largest << std::endl;

  return 0;
}
