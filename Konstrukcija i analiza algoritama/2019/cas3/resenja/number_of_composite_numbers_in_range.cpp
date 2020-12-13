#include <iostream>
#include <vector>
#include <cmath>

#define MAX 10000

// Funkcija Eratostenovo sito za odredjivanje elemenata koji su prosti (slozeni)
void sieve_of_eratosthenes(std::vector<bool> &prime)
{
    prime[1] = true;

    for (int p = 2; p * p <= MAX; p++) {
        if (prime[p] == true) {
            for (int i = p * 2; i <= MAX; i += p)
                prime[i] = false;
        }
    }
}

// Rekurzivna funkcija koja kreira segmentno stablo segment_tree od niza brojeva array i niza bool vrednosti prime. Svaki element u prime govori da li je element na poziciji
// prime[i] prost ili ne. Mi formiramo stablo tako sto stavljamo 0 u stablo ukoliko je array[i] prost, a 1 inace. Na taj nacin svi listovi stabla koji odgovaraju slozenim
// brojevima cuvaju vrednost 1, a ostali 0. Ostatak stabla se gradi isto, pa tako svaki unutrasnji cvor cuva zapravo broj slozenih brojeva u segmentu koji poktriva.
// Parametar k predstavlja poziciju cvora unutar niza (njegov indeks), dok x i y oznacavaju krajeve intervala koje cvor obuhvata, na pocetku je taj interval ceo niz,
// a kroz rekurzvine pozive se polovi i svaki cvor pokriva manji deo pocetnog niza
void build_segment_tree (std::vector<int> &array, std::vector<int> &segment_tree, std::vector<bool> &prime, int k, int x, int y)
{
  // Ukoliko smo dosli do jednoclanog niza (list u stablu), nema vise polovnjenja intervala pa zavrsavamo rekurziju
  if (x == y) {
    // k je bas pozicija gde treba da smestimo nas element u stablu, i proveravamo da li je broj na poziciji array[x]/array[y] slozen ili ne
    segment_tree[k] = prime[array[x]] ? 0 : 1;
    return;
  }

  // Trazimo sredinu intervala koji smo pokrili na visem nivou, sada imamo njegov levi i desni deo koje pokrivaju potomci cvora sa viseg nivoa. Dakle ako imamo deo niza 1, 2, 3, 4
  // i roditeljski cvor C1 pokriva 1, 2, 3, 4 onda njegovi potomci C2 i C3 pokrivaju redom 1, 2 i 3, 4.
  int middle = (x + y) / 2;

  // Pozivamo rekurziju za kreiranje potomaka cvora (levo i desno)
  // Levi potomak je na poziciji 2 * k u odnosu na poziciju oca
  build_segment_tree(array, segment_tree, prime, 2 * k, x, middle);
  // Desni potomak je na poziciji 2 * k + 1 u odnosu na poziciju oca
  build_segment_tree(array, segment_tree, prime, 2 * k + 1, middle + 1, y);

  // Nakon sto smo kreirali oba sina, potrebno je odrediti koji broj se cuva u ocu, to je zbir brojeva potomaka (podsetiti se strukture stabla)
  // Ukoliko ne bismo imali ovu liniju, samo bi listovi imali neke vrednosti, unutrasnji cvorovi ne bi bili popunjeni na odgovarajuci nacin
  segment_tree[k] = segment_tree[2 * k] + segment_tree[2 * k + 1];
}

// Funkcija koja racuna broj slozenih brojeva u intervalu [a, b]. Funkcija radi isto kao funkcija za sumu, jer se u sustini i svodi na nju
int number_of_composite_in_interval(std::vector<int> &segment_tree, int k, int x, int y, int a, int b)
{
  // Ukoliko nema preklapanja segmenata vracamo 0
  if (a > y || b < x)
    return 0;

  // Ukoliko se ceo [x, y] nalazi unutar [a, b] vracamo sumu koju cuva cvor koji pokriva segment [x, y], samim tim i sumu segmenta [x, y]
  if (x >= a && y <= b)
    return segment_tree[k];

  // Delimo segment [x, y] na 2 podsegmenta i problem resavamo rekurzivno za njih
  int middle = (x + y) / 2;

  return number_of_composite_in_interval(segment_tree, 2 * k, x, middle, a, b) + number_of_composite_in_interval(segment_tree, 2 * k + 1, middle + 1, y, a, b);
}

// Funkcija koja azurira stablo, tj odgovarajucem listu dodaje vrednost difference, koja ce ili smanjiti ili povecati vrednost u listu za 1
void update_tree(std::vector<int> &segment_tree, int k, int x, int y, int index, int difference)
{
  // Ukoliko smo dosli do lista (to je bas onaj cvor koji treba azurirati), azuriramo mu vrednost i zavrsavamo rekurziju
  if (x == y) {
    segment_tree[k] += difference;
    return ;
  }

  // Delimo segment na 2 dela
  int middle = (x + y) / 2;

  // Usmeravamo pretragu, ne zelimo da idemo i levo i desno, vec biramo kuda cemo na osnovu toga gde nam je trazeni cvor
  // Ukoliko je sredina segmenta desno od pozicije elementa u pocetnom nizu array, onda znaci da treba da idemo levo, inace idemo desno
  if (index <= middle)
    update_tree(segment_tree, 2 * k, x, middle, index, difference);
  else
    update_tree(segment_tree, 2 * k + 1, middle + 1, y, index, difference);

  // Nakon azuriranja lista trebalo bi azurirati i sve cvorove koji su na putu od korena do njega jer su se automatski i njihove vrednosti izmenile
  segment_tree[k] = segment_tree[2 * k] + segment_tree[2 * k + 1];
}

// Funkcija koja azurira odgovarajuci element u nizu array, i onda poziva funkciju update_tree() koja ce azurirati i stablo.
// Imamo 4 varijante prilikom promene elementa u nizu. Ili su i stara i nova vrednost proste ili su obe slozene pa se ne menja nista sustinski u stablu.
// Ukoliko je stara vrednost prost broj a nova slozeni onda se suma u svim cvorovima na putu od korena do toga lista povecava za 1, u suprotnom se smanjuje
void update_array(std::vector<int> &array, std::vector<int> &segment_tree, std::vector<bool> prime, int index, int new_value)
{
  // Promenljiva koja ce imati vrednost -1 ili 1 u slucaju da treba menjati stablo, inace necemo ni pozivati funkciju za promenu stabla, jer nema potrebe (stablo se ne menja)
  int difference;

  int old_value = array[index];

  array[index] = new_value;

  if ((prime[old_value] && prime[new_value]) || (!prime[old_value] && !prime[new_value]))
    return ;

  if (prime[old_value] && !prime[new_value])
    difference = 1;
  else
    difference = -1;

  update_tree(segment_tree, 1, 0, array.size() - 1, index, difference);
}

int main ()
{
  std::vector<int> array = { 1, 12, 3, 5, 17, 9 };

  std::vector<bool> prime(MAX);

  /********* C++ deo *********/
  // Funkcija std::fill() prima iterator na pocetak kolekcije i kraj kolekcije i vrednost kojom treba popuniti celu kolekciju
  std::fill(prime.begin(), prime.end(), true);

  sieve_of_eratosthenes(prime);

  int n = array.size();

  int height = ceil(log2(n));

  int size = 2 * pow(2, height);

  std::vector<int> segment_tree(size);

  build_segment_tree(array, segment_tree, prime, 1, 0 , n - 1);

  std::cout << number_of_composite_in_interval(segment_tree, 1, 0, n - 1, 0, 4) << std::endl;

  update_array(array, segment_tree, prime, 3, 6);

  std::cout << number_of_composite_in_interval(segment_tree, 1, 0, n - 1, 0, 4) << std::endl;

  return 0;
}
