#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>

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
void find_max_occuring_word(Node *root, std::string &max_occuring_word, int &max)
{
  // Ukoliko smo dosli do lista (samo list ima rec koja je razlicita od ""), proveravamo da li se ova rec javlja najvise puta do sad i ako da azuriramo max_occuring_word
  // Kao i u slucaju leksikografskog poretka nastavljamo dalje
  // Primetimo da promenljiva max mora da bude poslata kao referenca (ili pokazivac), jer mi zelimo da azuriramo globalni maksimum.
  // Recimo da imamo reci anamarija, anastasija, anastasija, imacemo "odvojen" max za obe grane iz cvora koji cuva ana. Ovaj cvor se grana u dva potomka anamarija i anastasija
  // Svaki od potomaka rekurzivnim pozivom dobija max = 0, i ako nije poslata promenljiva preko pokazivaca, kada dodjemo u cvor koji cuva rec anamarija max ce biti 0, ali i Kada
  // dodjemo u cvor gde je rec anastasija imacemo isti slucaj, sto je problem. Onaj cvor u koji poslednji udjemo ce azurirati vrednost promenljive max_occuring_word na rec koju
  // on cuva, sto mi ne zelimo, jer to moze da proizvede nedefinisano ponasanje
  if (root->word != "") {
    std::cout << root->word << " " << max << "\n";
    if (root->count > max) {
      max = root->count;
      max_occuring_word = root->word;
    }
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
    find_max_occuring_word(begin->second, max_occuring_word, max);
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
  std::vector<std::string> words = {"code", "coder", "coding", "codable", "codec", "codecs", "coded",
		"codeless", "codec", "codecs", "codependence", "codex", "codify",
		"codependents", "codes", "code", "coder", "codesign", "codec",
		"codeveloper", "codrive", "codec", "codecs", "codiscovered"};

  // Obrisati & kod &max u funkciji find_max_occuring_word i pokrenuti sa ovim skupom reci
  // std::vector<std::string> words = {"anamarija", "anastasija", "anastasija"};

  Node *root = create_node();

  for (std::string &s : words)
    add_word(root, s, 0);

  std::string most_occurences_word = "";

  int max = 0;

  find_max_occuring_word(root, most_occurences_word, max);

  std::cout << most_occurences_word << std::endl;

  free_tree(root);
  
  return 0;
}
