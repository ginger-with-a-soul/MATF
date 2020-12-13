#include <iostream>
#include <vector>

// Moguci broj potomaka, ASCII tabela ima 128 karaktera
#define CHAR_SIZE 128

// Struktura cvor u kojoj cuvamo jedan cvor prefiksnog stabla
struct Node
{
  // Konstruktor za cvor
  /********* C++ deo *********/
  // Konstruktor sluzi da mozemo da napravimo instancu sturkture, u C-u kada smo radili sa srtukturama isli smo Node node; node.is_leaf = false; U C++-u mozemo direktno prilikom
  // pravljenja cvora da stavimo promenljivu is_leaf na false, i sve potencijalne potomke cvora na NULL
	Node()
	{
		isLeaf = false;

    for (int i = 0; i < CHAR_SIZE; i++)
			nodes[i] = nullptr;
	}

  // Zbog specificnosti prefiksnog stabla, i cvor koji ima potomke moze da bude list (vazno je samo da predstavlja kraj reci), cuvamo informaciju o tome da li je cvor list, odnosno
  // da li se u njemu zavrsava neka rec
  bool isLeaf;
  // Niz u kome cem o cuvati potomke datog cvora, ukoliko potomak na nekoj poziciji ne postoji, imacemo nullptr na toj poziciji
	Node *nodes[CHAR_SIZE];
};

// Funkcija za dodavanje reci u stablo, root je koren stabla, word rec koja se dodaje
void add_word(Node *root, std::string &word)
{
  // Prolazimo kroz celu rec i proveravamo da li postoji potomak ka kome vodi grana sa oznakom i-tog karaktera niske word
	for (int i = 0; i < word.length(); i++)
	{
    // Ukoliko nema grane kojom void i-ti karakter niske word (samim tim nema ni tog potomka) dodajemo granu (cvor)
		if (root->nodes[word[i]] == nullptr)
			root->nodes[word[i]] = new Node();

    // Krecemo se niz odgovarajucu granu, tj preko odgovarajuceg cvora
		root = root->nodes[word[i]];
	}

  // Na kraju, dosli smo do kraja reci, pa nam bas ovaj cvor predstavlja list
	root->isLeaf = true;
}

// Funckija koja proverava da li se rec nalazi u stablu. Vraca true ukoliko se nalazi, false inace. Funkcija je slicna funkciji za dodavanje reci
bool find_word(Node *root, std::string &word)
{
  // Ukoliko trazimo u praznom stablu vracamo odmah false
	if (root == nullptr)
		return false;

  // Idemo kroz rec i krecemo se niz odgovarajuce grane, ukoliko one postoje, ukoliko neka grana ne postoji to znaci da se i-ti karakter reci ne nalazi u stablu, tj nema ni reci,
  // pa vracamo false
	for (int i = 0; i < word.length(); i++)
	{
		root = root->nodes[word[i]];

		if (root == nullptr)
			return false;
	}

  // Na kraju kada prodjemo kroz celu rec koju smo trazili
	return root->isLeaf;
}

int main ()
{
  std::vector<std::string> words = {"cod", "coder", "coding", "codecs"};

  Node *root = new Node();

  for (std::string &s : words)
    add_word(root, s);

  std::string s = "code";

  // boolalpha nam omogucava da pisemo true i false a ne 0 ili 1
  std::cout << std::boolalpha << find_word(root, s) << std::endl;
}
