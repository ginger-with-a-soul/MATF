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
  // Nepohodna je alokacija pomocu new Node(). U suprotnom kod koriscenja mape dolazi do segmentation fault-a
  Node *new_node = new Node();

  // Inicijalno cvor nije list
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

// Funkcija koja proverava da li se data rec moze izdeliti na reci iz drveta sa korenom root
bool word_break(Node *root, std::string &word)
{
  // Duzina reci
  int n = word.size();

  // Vector bool promenljivih koji nam kaze sledece:
  // - ako je valid[i] == true, to znaci da se prvih i karaktera niske word moze naci u drvetu, tj da se word[0...i-1] moze izdeliti na ispravan nacin
  // - ako je valid[i] == false, to znaci da se prvih i karaktera niske word NE moze naci u drvetu, tj NE moze se deo word[0...i-1] izdeliti na odgovarajuci nacin
  std::vector<bool> valid(n);

  // Na pocetku pretpostavimo da prvi karakter moze da se nadje u stablu
  valid[0] = true;

  Node *tmp;

  // Idemo kroz rec
  for (int i = 0;i < n;i++) {
    // Ukoliko se prvih i karaktera moze naci u stablu, idemo od i + 1-og karaktera pa na dalje da vidimo da li se i ostatak niske moze naci u stablu
    if(valid[i]) {
      // Krecemo uvek od korena stabla
      tmp = root;
      // Idemo od i + 1-og karaktera do kraja niske i trazimo odgovarajuce karaktere u stablu
      for (int j = i;j < n;j++) {
        // Provera da li se karakter nalazi na putu kojim smo krenuli (ili kojim krecemo ako smo u korenu)
        auto iterator = tmp->nodes.find(word[j]);

        // Ukoliko nema puta izlazimo iz unutrasnje petlje
        if (iterator == tmp->nodes.end())
          break;

        // Inace, ukoliko put postoji krecemo se njim
        tmp = tmp->nodes[word[j]];

        // Ukoliko dodjemo do lista, to znaci da smo dosli do kraja neke reci u stablu, samim tim nemamo gde dalje, ali znamo da smo uspeli da poklopimo sve karaktere iz te reci
        // sa karakterima iz niske koju pokusavamo da izdelimo, da nije tako izasli bismo sa break; ranije
        // S obzirom da smo uspeli da poklopimo sve karaktere date reci, nemamo gde dalje da idemo, ali znamo i da smo uspeli prvih j + 1 karaktera da poklopimo, tj karaktere od 0
        // do j, zato zelimo da pretragu nastavimo od j + 1-og karaktera
        if (tmp->is_leaf) {
          valid[j + 1] = true;
        }

        // Ukoliko smo dosli do kraja niske koju pokusavamo da izdelimo, znaci da ona moze biti izdeljena na reci iz stabla i vracamo true
        if (j == n - 1)
          return true;
      }
    }
  }

  // Ukoliko dodjemo do ovde, znaci da niska word ne moze biti izdeljena na reci iz stabla pa vracamo false
  return false;
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
  std::vector<std::string> words = { "this", "th", "is", "famous", "word", "break", "b", "r", "e", "a", "k", "br", "bre", "brea", "ak", "prob", "lem" };

  // std::vector<std::string> words = { "word", "br", "k", "b", "ea", "pr", "oblem" };

	Node* root = create_node();

	for (std::string &s: words) {
		add_word(root, s, 0);
	}

	std::string str = "wordbreakproblem";

	if (word_break(root, str)) {
		std::cout << "String can be segmented\n";
	}
  else {
		std::cout << "String can't be segmented\n";
	}

  free_tree(root);

  return 0;
}
