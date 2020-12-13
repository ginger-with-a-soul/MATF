#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>
#include <queue>

// Struktura cvor u kojoj cuvamo jedan cvor prefiksnog stabla
struct Node
{
  // Rec koja se nalazi u cvoru, samo listovi ce imati ovu promenljivu postavljenu na neku rec, jer ostali cvorovi ne cuvaju reci vec njihove delove, u listu se rec zavrsava pa je tu
  // i cuvamo
  std::string word;
  // Promenljiva koja cuva broj pojavljivanja odgovarajuce reci, kad god udjemo u list uvecavamo ovu promenljivu za njega i na taj nacin azuriramo broj pojavljivanja reci
  int count;
  // Mapa u kojoj cuvamo za svaki cvor njegove potomke, kljuc u mapi nam predstavlja karakter koji vodi ka cvoru potomku, a vrednost je bas taj cvor (pokazivacka promenljiva)
  /********* C++ deo *********/
  // Koristimo unordered_map zato sto je ona implementirana kao hes mapa, tako da su operacije u proseku O(1), kako za svaki cvor vazi da svaka grana iz njega predstavlja jedno
  // slovo, ovde ce uvek biti slozenost O(1)
  std::unordered_map<char, Node *> nodes;
};

Node *create_node()
{
  // Nepohodna je alokacija pomocu new Node(). U suprotnom kod koriscenja mape dolazi do segmentation fault-a
  Node *new_node = new Node();

  // Rec koju cuva svaki cvor je na pocetku prazna rec, a kasnije se ona dopuni kada dodjemo do lista
  new_node->word = "";

  // Svaka rec se na pocetku javlja 0 puta, kako budemo stizali u listove, azuriracemo brojace
  new_node->count = 0;

  // Vracamo cvor za koji smo alocirali memoriju
  return new_node;
}

// Funkcija za dodavanje reci u stablo, root je koren stabla, word rec koja se dodaje a i nam govori dokle u reci smo stigli
void add_word(Node *root, std::string &word, int i)
{
  // Ukoliko smo dosli do kraja reci, to znaci da je cvor u kome se trenutno nalazimo i list, tj predstavlja kraj reci, tako da postavljamo njegovu rec na trenutnu rec, azuriramo
  // broj pojavljivanja te reci i zavrsavamo rekurziju, jer je cela rec dodata u stablo
  if (i == (int)word.size()) {
    root->count++;
    root->word = word;
    return ;
  }

  // Trazimo cvor (granu) niz koju void odgovarajuce slovo reci, recimo da nam je rec KUCA i da imamo granu iz korena niz koju ide K, a zatim iz odgovarjuceg cvora granu niz koju ide U
  // trazimo u odgovarajucem cvoru granu niz koju void C, dakle u mapi trazimo par ciji je kljuc bas slovo C (i-to slovo reci word)
  /********* C++ deo *********/
  // Metod fin pokusava da nadje element mape ciji je kljuc i-to slovo reci word, kao povratnu vrednost vraca pokazivac na odgovarajuci element ukoliko on psotoji ili pokazivac na
  // kraj mape ukoliko odgovarajuceg elementa nema. Kljucna rec auto nam zamenjuje tip (od C++11 standarda), ukoliko ne znamo tip promenljive ili kao u ovo slucaju ne zelimo da pisemo
  // dugacak i naporan naziv (u ovom slucaju std::unordered_map<char, Node*>::iterator) stavimo auto i onda ce kompajler sam utvrditi tip promenljive
  auto iterator = root->nodes.find(word[i]);

  // Ukoliko element ne postoji, zelimo da ga dodamo u stablo. Ako imamo K->U zelimo da nakon U dodamo i C. Zato pravimo novi cvor sa odgovarajucom oznakom
  if (iterator == root->nodes.end())
    // Ukoliko element sa kljucem word[i] u mapi ne postoji bice kreiran i njegova vrednost ce biti novi napravljeni cvor
    root->nodes[word[i]] = create_node();

  // Rekurzivno dodajemo naredno slovo reci u stablo, i kao trenutni "koren" saljemo odgovarajuci cvor
  add_word(root->nodes[word[i]], word, i + 1);
}

// Funckija koja pronalazi rec koja je javlja maksimalan broj puta, rec se smesta u promenljivu max_occuring_word, a max broji maksimalan broj pojavljivanja
void put_words_into_heap(Node *root, auto &heap)
{
  // Ukoliko smo dosli do lista (samo list ima rec koja je razlicita od "")
  // Kao i u slucaju leksikografskog poretka nastavljamo dalje
  if (root->word != "") {
    heap.push(root);
  }

  // Uzimamo pokazivace na pocetak i kraj liste
  /********* C++ deo *********/
  // Metod begin() vraca iterator (pokazivacka promenljiva) na pocetak kolekcije (vector, list, map, unordered_map...) dok end() vraca pokazivac na jedan element iza poslednjeg.
  // Ako imamo vector 1,2,3,4,5 begin() vraca pokazivac na 1, a end() pokazivac na neki element van vector-a, ali ne na 5, zato se uvek ide dok je begin != end
  auto begin = root->nodes.begin();
  auto end = root->nodes.end();

  // Objasnjenje zasto != je iznad
  while (begin != end)
  {
    // Pozivamo rekurziju za drugi element para iz mape odnosno za odgovarajuci cvor
    put_words_into_heap(begin->second, heap);
    // pomeramo se kroz vector
    begin++;
  }
}

struct comparator
{
  bool operator()(Node *n1, Node *n2)
  {
    return n1->count < n2->count;
  }
};

void free_tree(Node *root)
{
  if (root == nullptr)
    return ;

  // Prvo oslobadjamo sva podstabla datog korena
  for (auto &p : root->nodes)
    free_tree(p.second);

  // A nakon toga i sam koren. Alokacija je vrsena pomocu new pa oslobadjanje mora pomocu delete
  delete root;
}

int main ()
{
  std::vector<std::string> words = {"code", "coder", "coding", "codable", "codec", "codecs", "coded",
		"codeless", "codec", "codecs", "codependence", "codex", "codify",
		"codependents", "codes", "code", "coder", "codesign", "codec",
		"codeveloper", "codrive", "codec", "codecs", "codiscovered"};

  Node *root = create_node();

  for (std::string &s : words)
    add_word(root, s, 0);

  /********* C++ deo *********/
  // std::priority_queue sluzi za implementaciju heap-a. Kao prvi parametarski argument (argumenti izmedju <>) dobija tip podataka koje cuva, kao drugi kolekciju koja se nalazi
  // "ispod haube", a kao treci argument dobija funkcijski objekat, funkciju i slicno sto odgovara uredjenju elemenata, tj nesto sto poredi elemente tipa koji se smestaju u heap, Node * u nasem
  // slucaju. Za vise informacija https://en.cppreference.com/w/cpp/container/priority_queue ili nakon casa mozete doci da razjasnimo
  std::priority_queue<Node *, std::vector<Node *>, comparator> heap;

  put_words_into_heap(root, heap);

  int k = 3;

  Node *tmp;

  while (k && heap.size())
  {
    tmp = heap.top();
    heap.pop();

    std::cout << tmp->word << " occurs " << tmp->count << " times " << std::endl;
    k--;
  }

  free_tree(root);
  
  return 0;
}
