#include <iostream>
#include <map>
#include <string>
#include <vector>

// Struktura cvor u kojoj cuvamo jedan cvor prefiksnog stabla
struct Node
{
  // Rec koja se nalazi u cvoru, samo listovi ce imati ovu promenljivu postavljenu na neku rec, jer ostali cvorovi ne cuvaju reci vec njihove delove, u listu se rec zavrsava pa je tu
  // i cuvamo
  std::string word;
  // Ovde koristimo obicnu mapu, jer nam je bitan poredak
  /********* C++ deo *********/
  // Mapa je u C++ u implementirana kao balansirano binarno stablo (crveno-crna stabla), s toga je garantovano da svaka od operacija umetanja, brisanja i pretrage ima slozenost
  // O(logn) gde je n broj cvorova u stablu. Kako imamo binarno stablo pretrage, imamo i poredak, sto nama treba u ovom zadatku, jer zelimo da leksikografski sortiramo reci
  std::map<char, Node *> nodes;
};

Node *create_node()
{
  // Nepohodna je alokacija pomocu new Node(). U suprotnom kod koriscenja mape dolazi do segmentation fault-a
  Node *new_node = new Node();

  // Rec koju cuva svaki cvor je na pocetku prazna rec, a kasnije se ona dopuni kada dodjemo do lista
  new_node->word = "";

  // Vracamo cvor za koji smo alocirali memoriju
  return new_node;
}

// Funkcija za dodavanje reci u stablo, root je koren stabla, word rec koja se dodaje a i nam govori dokle u reci smo stigli
void add_word(Node *root, std::string &word, int i)
{
  // Ukoliko smo dosli do kraja reci, to znaci da je cvor u kome se trenutno nalazimo i list, tj predstavlja kraj reci, tako da postavljamo njegovu rec na trenutnu rec i
  // zavrsavamo rekurziju, jer je cela rec dodata u stablo
  if (i == (int)word.size()) {
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

void lexicographic(Node *root)
{
  // Kada dodjemo do cvora koji je list (to su samo oni cvorovi cija rec nije prazna niska) zelimo da ispisemo reci
  // Primetimo da se ovde ne zavrsava rekurzija, tj nemamo return, jer se moze desiti da je i unutrasnji cvor list i zelimo da nastavimo dalje. Primer: ana, anastasija
  // Da ovde imamo return, nakon ana bismo zavrsili poziv, a to necemo, hocemo da idemo dalje
  if (root->word != "")
    std::cout << root->word << std::endl;

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
    lexicographic(begin->second);
    // pomeramo se kroz vector
    begin++;
  }
}

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
  std::vector<std::string> words =
	{
		"lexicographic", "sorting", "of", "a", "set", "of", "keys", "can",
		"be", "accomplished", "with", "a", "simple", "trie", "based",
		"algorithm", "we", "insert", "all", "keys", "in", "a", "trie",
		"output", "all", "keys", "in", "the", "trie", "by", "means", "of",
		"preorder", "traversal", "which", "results", "in", "output", "that",
		"is", "in", "lexicographically", "increasing", "order", "preorder",
		"traversal", "is", "a", "kind", "of", "depth", "first", "traversal"
	};
  // std::vector<std::string> words = {"ana", "anastasija", "anastasijin", "anamarija", "anamarijin"};

  Node *root = create_node();

  for (std::string &s : words)
    add_word(root, s, 0);

  lexicographic(root);

  free_tree(root);

  return 0;
}
