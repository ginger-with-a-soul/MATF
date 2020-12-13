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
  // Mapa u kojoj cuvamo za svaki cvor njegove potomke, kljuc u mapi nam predstavlja karakter koji vodi ka cvoru potomku, a vrednost je bas taj cvor (pokazivacka promenljiva)
  /********* C++ deo *********/
  // Koristimo unordered_map zato sto je ona implementirana kao hes mapa, tako da su operacije u proseku O(1), kako za svaki cvor vazi da svaka grana iz njega predstavlja jedno
  // slovo, ovde ce uvek biti slozenost O(1)
  std::unordered_map<char, Node *> nodes;
};

Node *create_node()
{
  // Kada se radi sa unordered_map alokacija se MORA vrsiti pomocu new. Ukoliko se koristi malloc dolazi do odredjenih problema (floating point exception).
  Node *new_node = new Node();

  // Inicjalno cvor nije list
  new_node->is_leaf = false;

  return new_node;
}

// Funkcija za dodavanje reci u stablo, root je koren stabla, word rec koja se dodaje a i nam govori dokle u reci smo stigli
void add_word(Node *root, std::string &word, int i)
{
  // Ukoliko smo dosli do kraja reci, to znaci da je cvor u kome se trenutno nalazimo i list, tj predstavlja kraj reci, oznacavamo to i zavrsavamo rekurziju,
  // jer je cela rec dodata u stablo
  if (i == (int)word.size()) {
    root->is_leaf = true;
    return ;
  }

  // Trazimo cvor (granu) niz koju void odgovarajuce slovo reci, recimo da nam je rec KUCA i da imamo granu iz korena niz koju ide K, a zatim iz odgovarjuceg cvora granu niz koju ide U
  // trazimo u odgovarajucem cvoru granu niz koju void C, dakle u mapi trazimo par ciji je kljuc bas slovo C (i-to slovo reci word)
  /********* C++ deo *********/
  // Metod find() pokusava da nadje element mape ciji je kljuc i-to slovo reci word, kao povratnu vrednost vraca pokazivac na odgovarajuci element ukoliko on psotoji ili pokazivac na
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

// Funckija koja trazi najduzi zajednicki prefiks u skupu reci
// U string LCP cemo smestati najduzi prefiks
void LCP(Node *root, std::string &LCP)
{
  // Spustamo se niz stablo sve dok ne dodjemo do prvog lista ili dok god cvor ima samo jednog potomka, to nam je znak da sve reci imaju isti prefiksnog
  // Primetimo da moramo da imamo proveru i da li je cvor list.
  // Zamislimo da imamo reci ana, anastasija, anastasijin, ukoliko se krecemo dok cvor ima samo jednog sina otici cemo skroz do anastasij, a prefiks je samo ana, jer nama je jedna rec
  // upravo ana
  while(root && !root->is_leaf && root->nodes.size() == 1) {

    // Uzimamo jedini element iz mape, njegov kljuc je upravo karakter koji nam treba, za recimo rec ANA, to ce redom biti A, N, A
    // Promenljiva element je pokazivacka
    auto element = root->nodes.begin();

    // Uzimamo karakter i dodajemo ga stringu koji predstavlja najduzi zajednicki prefiks
    LCP += element->first;

    // Novi cvor koji se razmatra je prvi i jedini element mape, odnosno jedini cvor kako kome postoji grana
    root = element->second;
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
  std::vector<std::string> words = {"code", "coder", "coding", "codable", "codec", "codecs", "coded",
		"codeless", "codec", "codecs", "codependence", "codex", "codify",
		"codependents", "codes", "code", "coder", "codesign", "codec",
		"codeveloper", "codrive", "codec", "codecs", "codiscovered"};

  // Probati ovaj skup reci i izbaciti uslov u petlji !root->is_leaf
  //std::vector<std::string> words = {"ana", "anastasija", "anastasijin"};

  Node *root = create_node();

  for (std::string &s : words)
    add_word(root, s, 0);

  std::string lcp = "";

  LCP(root, lcp);

  std::cout << lcp << std::endl;

  free_tree(root);

  return 0;
}
