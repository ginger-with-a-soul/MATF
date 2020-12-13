#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

// Strukutra Node koja predstavlja cvor segmentnog stabla. Svaki element cuva najveci zajednicki delilac u segmentu, najmanji broj u segmentu i brojac koji govori koliko puta se najmanji
// broj javlja
struct Node
{
  int counter;
  int greatest_common_divider;
  int min_element;
};

// Funckija koja pravi segmentno stablo
void build_segment_tree (std::vector<int> &array, std::vector<Node> &segment_tree, int k, int x, int y)
{
  // Ukoliko smo dosli do lista u stablo smestamo element koji ima brojac 1, ciji je najveci zajednicki delilac upravo broj array[x] jer je to ujedno i jedini broj i ciji je minimalni
  // element array[x] jer je to opet jedini broj u segmentu
  if (x == y) {
    segment_tree[k].counter = 1;
    segment_tree[k].greatest_common_divider = array[y];
    segment_tree[k].min_element = array[x];
    return ;
  }

  // Delimo segment
  int middle = (x + y) / 2;

  // Pozivamo rekurziju za oba potomka trenutnog cvora
  build_segment_tree(array, segment_tree, 2 * k, x, middle);
  build_segment_tree(array, segment_tree, 2 * k + 1, middle + 1, y);

  // Najveci zajednicki delilac u roditeljskom cvoru je najveci zajednicki delilac za najvece zajednicke delioce potomaka (znam da zvuci nakaradno ali kroz kod se vidi :))
  segment_tree[k].greatest_common_divider = std::__gcd(segment_tree[2 * k].greatest_common_divider, segment_tree[2 * k + 1].greatest_common_divider);

  // Trazimo sina koji ima manji minimalni element i njegov element postavljamo kao minimum u roditeljskom cvoru, a takodje brojac roditeljskog cvora je jednak brojacu onog potomka koji
  // cuva manji element
  if (segment_tree[2 * k].min_element < segment_tree[2 * k + 1].min_element) {
    segment_tree[k].min_element = segment_tree[2 * k].min_element;
    segment_tree[k].counter = segment_tree[2 * k].counter;
  }
  else if (segment_tree[2 * k + 1].min_element < segment_tree[2 * k].min_element) {
    segment_tree[k].min_element = segment_tree[2 * k + 1].min_element;
    segment_tree[k].counter = segment_tree[2 * k + 1].counter;
  }
  // Ukoliko oba potomka imaju isti minimalni element, brojac roditeljskog cvora je jednak njihovom zbiru, dok minimalni element mozemo uzeti iz bilo kog cvora
  else {
    segment_tree[k].min_element = segment_tree[2 * k].min_element;
    segment_tree[k].counter = segment_tree[2 * k].counter + segment_tree[2 * k + 1].counter;
  }
}

// Funckija koja vraca cvor koji cuva koliko ima brojeva koji dele sve brojeve iz [a, b]
Node get_number_of_dividers (std::vector<Node> &segment_tree, int k, int x, int y, int a, int b)
{
  Node result;

  // Ako nema preklapanja segmenata [x, y] i [a, b] onda samo kazemo da nemamo najveci zajednicki delilac, jer jednostavno nije vazan, ne utice na roditeljski cvor
  if (x > b || y < a) {
    result.greatest_common_divider = 0;
    result.min_element = 0;
    result.counter = 0;
    return result;
  }

  // Ukoliko se ceo segment [x, y] nalazi u segmentu [a, b] onda proveravamo da li je u tom cvoru minimalni element jednak najvecem zajednickom deliocu. Ako jeste vracamo cvor koji
  // je potpuno isti kao i odgovarajuci cvor stabla, inace vracamo cvor koji ima ista najveci zajednicki delilac i minimalni element, ali je brojac jednak 0

  if (x >= a && y <= b) {
    result.greatest_common_divider = segment_tree[k].greatest_common_divider;
    result.min_element = segment_tree[k].min_element;

    if (result.min_element != result.greatest_common_divider)
      result.counter = 0;
    else
      result.counter = segment_tree[k].counter;

    return result;
  }
  // Delimo segment
  int middle = (x + y) / 2;

  // Uzimamo levog i desnog potomka i podatke iz njih
  Node left = get_number_of_dividers(segment_tree, 2 * k, x, middle, a, b);
  Node right = get_number_of_dividers(segment_tree, 2 * k + 1, middle + 1, y, a, b);

  // Ukoliko su nam oba segmenta vazna (odnosno njihov najveci zajednicki sadrzalac je veci od 0) odredjujemo najmanji broj u intervalima koje oni cuvaju, najveci zajednicki delilac
  // i brojac.
  if (left.greatest_common_divider && right.greatest_common_divider) {
    // Trazimo najveci zajednicki delilac za cvorove potomke
    result.greatest_common_divider = std::__gcd(left.greatest_common_divider, right.greatest_common_divider);
    // Trazimo manji od dva minimalna elementa koja se cuvaju u sinovima
    int min = std::min(left.min_element, right.min_element);

    // Ukoliko minimalni element nije jednak najvecem zajednickom deliocu, znaci da ne postoji broj u odgovarajucem segmentu koji deli sve ostale, pa kazemo da je najveci zajednicki
    // delilac jednak 0, tj ne postoji
    if (result.greatest_common_divider != min) {
      result.greatest_common_divider = 0;
      result.counter = 0;
      result.min_element = 0;
    }
    // Ako postoji najveci zajednicki delilac, azuriramo najmanju vrednost koja se nalazi u segmentu koji cuva cvor kao i brojac tog elemeta
    else {
      // Ako oba potomka imaju istu vrednost minimalnog elementa, taj element je minimalan i za roditeljski cvor, i brojac je jednak zbiru brojaca levog i desnog potomka
      if (left.min_element == right.min_element) {
        result.min_element = left.min_element;
        result.counter = left.counter + right.counter;
      }
      // Ako levi potomak ima manji element, onda je najmanji element segmenta jednak njemu i brojac je jednak njegovom brojacu
      else if (left.min_element < right.min_element) {
        result.min_element = left.min_element;
        result.counter = left.counter;
      }
      // Ako desni potomak ima manji element, onda je najmanji element segmenta jednak njemu i brojac je jednak njegovom brojacu
      else {
        result.min_element = right.min_element;
        result.counter = right.counter;
      }
    }

    std::cout << "result " << result.greatest_common_divider << " " << result.min_element << " " << x << " " << y << " " << "\n";
    return result;
  }
  // Ukoliko samo levi segment ulazi u rezultat vracamo samo njega
  else if (left.greatest_common_divider)
    return left;
  // Ukoliko samo desni segment ulazi u rezultat vracamo samo njega
  else if (right.greatest_common_divider)
    return right;
}

int main ()
{
  std::vector<int> array = { 5, 2, 3, 4, 6, 4, 7, 8 };

  int n = array.size();

  int height = ceil(log2(n));

  int size = 2 * pow(2, height);

  std::vector<Node> segment_tree (size);

  build_segment_tree(array, segment_tree, 1, 0, n - 1);

  // for (Node &n : segment_tree)
  //   std::cout << n.min_element << " " << n.greatest_common_divider << " " << n.counter << std::endl;

  Node result = get_number_of_dividers(segment_tree, 1, 0, n - 1, 0, 3);

  std::cout << result.counter << " " << result.greatest_common_divider << " " << result.min_element << std::endl;

  result = get_number_of_dividers(segment_tree, 1, 0, n - 1, 1, 4);

  std::cout << result.counter << " " << result.greatest_common_divider << " " << result.min_element << std::endl;
}
