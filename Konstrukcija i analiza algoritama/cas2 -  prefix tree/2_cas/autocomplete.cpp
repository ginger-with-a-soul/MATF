#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>

// Struktura cvor u kojoj cuvamo jedan cvor prefiksnog stabla
struct Node
{
  // Zbog specificnosti prefiksnog stabla, i cvor koji ima potomke moze da bude list (vazno je samo da predstavlja kraj reci), cuvamo informaciju o tome da li je cvor list, odnosno
  // da li se u njemu zavrsava neka rec
  bool is_leaf;
  // Rec koja se nalazi u cvoru, samo listovi ce imati ovu promenljivu postavljenu na neku rec, jer ostali cvorovi ne cuvaju reci vec njihove delove, u listu se rec zavrsava pa je tu
  // i cuvamo
  std::string word;
  // Mapa u kojoj cuvamo za svaki cvor njegove potomke, kljuc u mapi nam predstavlja karakter koji vodi ka cvoru potomku, a vrednost je bas taj cvor (pokazivacka promenljiva)
  std::unordered_map<char, Node *> nodes;
};

Node *create_node()
{
  // Nepohodna je alokacija pomocu new Node(). U suprotnom kod koriscenja mape dolazi do segmentation fault-a
  Node *new_node = new Node();

  // Za svaki cvor na pocetku kazemo da nije list
  new_node->is_leaf = false;

  // Rec koju cuva svaki cvor je na pocetku prazna rec, a kasnije se ona dopuni kada dodjemo do lista
  new_node->word = "";

  // Vracamo cvor za koji smo alocirali memoriju
  return new_node;
}

// Funkcija za dodavanje reci u stablo, root je koren stabla, word rec koja se dodaje a i nam govori dokle u reci smo stigli
void add_word(Node *root, std::string &word, int i)
{
  // Ukoliko smo dosli do kraja reci, to znaci da je cvor u kome se trenutno nalazimo i list, tj predstavlja kraj reci, tako da postavljamo njegovu rec na trenutnu rec, i kazemo da je 
  // cvor zapravo list jer smo stigli do kraja reci
  if (i == (int)word.size()) {
    root->word = word;
    root->is_leaf = true;
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

// Funkcija vraca pokazivac na cvor u kome se zavrsava odgovarajuci prefiks, tj ispod koga se nalaze sve trazene reci
Node *autocomplete(Node *root, std::string &prefix, int i)
{
  // Ako smo dosli do kraja prefiksa znaci da smo nasli trazeni cvor i vracamo pokazivac na isti
  if (i == prefix.size())
    return root;

  // Posto znamo koje nam slovo naredno treba jer se krecemo kroz trazeni prefix, proveravamo da li postoji odgovarajuci potomak
  auto iterator = root->nodes.find(prefix[i]);

  // Ukoliko ne postoji vracamo nullptr sto znaci da ne postoji nijedna rec sa trazenim prefiksom
  if (iterator == root->nodes.end())
    return nullptr;

  // U suprotnom se spustamo niz stablo dok ne dodjemo do kraja prefiska, saljemo odgovarajuceg potomka i azuriramo i kako bismo uzeli naredni karakter prefiksa
  return autocomplete(root->nodes[prefix[i]], prefix, i + 1);
}

// Funkcija za ispisivanje svih potomaka nekog cvora (svih reci koje se nalaze ispod cvora, tj imaju zajednicki prefiks)
void print(Node *root)
{
  // Ako dodjemo do lista znaci da se tu nalazi neka rec pa ispisujemo istu
  if (root->is_leaf)
    std::cout << root->word << std::endl;

  // Uzimamo iteratore na pocetak i kraj kolekcije potomaka, kako bismo prosli kroz sve potomke cvora
  auto begin = root->nodes.begin();
  auto end = root->nodes.end();

  // Krecemo se kroz sve potomke cvora rezukrzivno i svaki put kad naidjemo na list ispisacemo rec koju on cuva
  while (begin != end) {
    print(begin->second);
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
  std::vector<std::string> words = { "ana", "anica", "anicin", "anin", "anamarija", "anastasija", "anastasijin", "anamarijin" };

  Node *root = new Node();

  std::string prefix = "ana";

  for (std::string &s : words)
    add_word(root, s, 0);

  Node *tmp = autocomplete(root, prefix, 0);

  print(tmp);

  free_tree(root);

  return 0;
}
