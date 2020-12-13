#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>

// Struktura cvor u kojoj cuvamo jedan cvor prefiksnog stabla
struct Node
{
  // Konstruktor za cvor
  /********* C++ deo *********/
  // Konstruktor sluzi da mozemo da napravimo instancu sturkture, u C-u kada smo radili sa srtukturama isli smo Node node; node.is_leaf = false; U C++-u mozemo direktno prilikom
  // pravljenja cvora da stavimo promenljivu is_leaf na false
  Node()
  {
    is_leaf = false;
  }

  // Zbog specificnosti prefiksnog stabla, i cvor koji ima potomke moze da bude list (vazno je samo da predstavlja kraj reci), cuvamo informaciju o tome da li je cvor list, odnosno
  // da li se u njemu zavrsava neka rec
  bool is_leaf;
  // Mapa u kojoj cuvamo za svaki cvor njegove potomke, kljuc u mapi nam predstavlja karakter koji vodi ka cvoru potomku, a vrednost je bas taj cvor (pokazivacka promenljiva)
  /********* C++ deo *********/
  // Koristimo unordered_map zato sto je ona implementirana kao hes mapa, tako da su operacije u proseku O(1), kako za svaki cvor vazi da svaka grana iz njega predstavlja jedno
  // slovo, ovde ce uvek biti slozenost O(1)
  std::unordered_map<char, Node *> nodes;
};

// Funkcija za dodavanje reci u stablo, root je koren stabla, word rec koja se dodaje a i nam govori dokle u reci smo stigli
void add_word(Node *root, std::string &word, int i)
{
  // Ukoliko smo dosli do kraja reci, to znaci da je cvor u kome se trenutno nalazimo i list, tj predstavlja kraj reci, oznacavamo to i zavrsavamo rekurziju,
  // jer je cela rec dodata u stablo
  if (i == word.size()) {
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
    root->nodes[word[i]] = new Node();

  // Rekurzivno dodajemo naredno slovo reci u stablo, i kao trenutni "koren" saljemo odgovarajuci cvor
  add_word(root->nodes[word[i]], word, i + 1);
}

// Funckija koja proverava da li se rec nalazi u stablu. Vraca true ukoliko se nalazi, false inace. Funkcija je slicna funkciji za dodavanje reci
bool find_word(Node *root, std::string &word, int i)
{
  // Ukoliko smo dosli do cvora koji cuva kraj reci vracamo true, jer se rec nalazi u stablu
  if (i == word.size()) {
    // Primetimo da ovde NE SMEMO da vracamo true, jer mozda se rec iz stabla ne zavrsava ovde.
    // Neka u stablu imamo reci cod, i coder, cvorovi koji su listovi su cvor u koji ulazi D i cvor u koji ulazi R.
    // Sada zamislimo da trazimo rec cod, ukoliko u ovom if-u vracamo true a ne root->is_leaf, reci cemo da rec code postoji u stablu, sto nije tacno
    return root->is_leaf;
  }

  // Trazimo odgovarajuci cvor
  auto iterator = root->nodes.find(word[i]);

  // Ukoliko ga nema, znaci da rec ne postoji u stablu
  if (iterator == root->nodes.end())
    return false;

  // Ukoliko se i-to slovo nalazi u reci, vracamo ono sto nam vraca rekurzivni poziv za i + 1, ako je negde nadjena rec imacemo true, inace, u nekom od kasnijih rekurzivnih poziva samo
  // vratili false, pa cemo i sad to uraditi
  return find_word(root->nodes[word[i]], word, i + 1);
}

int main ()
{
  std::vector<std::string> words = {"cod", "coder", "coding", "codecs"};

  Node *root = new Node();

  for (std::string &s : words)
    add_word(root, s, 0);

  std::string s = "code";

  // boolalpha nam omogucava da pisemo true i false a ne 0 ili 1
  std::cout << std::boolalpha << find_word(root, s, 0) << std::endl;
}
