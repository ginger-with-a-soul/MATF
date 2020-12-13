#include <iostream>
#include <vector>
#include <cstdlib>

// Moguci broj potomaka, ASCII tabela ima 128 karaktera
#define CHAR_SIZE 128

// Struktura cvor u kojoj cuvamo jedan cvor prefiksnog stabla
struct Node
{
  // Zbog specificnosti prefiksnog stabla, i cvor koji ima potomke moze da bude list (vazno je samo da predstavlja kraj reci), cuvamo informaciju o tome da li je cvor list, odnosno
  // da li se u njemu zavrsava neka rec
  bool is_leaf;
  // Niz u kome cem o cuvati potomke datog cvora, ukoliko potomak na nekoj poziciji ne postoji, imacemo nullptr na toj poziciji
  Node *nodes[CHAR_SIZE];
};

Node *create_node()
{
  // Ovde alokacija moze pomocu malloc() posto imamo niz fiksne duzine (128)
	Node *new_node = (Node *)malloc(sizeof(Node));

  // Inicijalno nijedan cvor nije list
	new_node->is_leaf = false;

  // Za svaki cvor kazemo da nema nijednog potomka na pocetku, a onda kasnije kreiramo potomke po potrebi
	for (int i = 0; i < CHAR_SIZE; i++)
    // Ne postoji nijedan potomak, tj svi su null
		new_node->nodes[i] = nullptr;

	return new_node;
}

// Funkcija za dodavanje reci u stablo, root je koren stabla, word rec koja se dodaje
void add_word(Node *root, std::string &word)
{
  // Duzina reci
	int n = word.length();

  	// Prolazimo kroz celu rec i proveravamo da li postoji potomak ka kome vodi grana sa oznakom i-tog karaktera niske word
	for (int i = 0; i < n; i++)
	{
    // Ukoliko nema grane kojom void i-ti karakter niske word (samim tim nema ni tog potomka) dodajemo granu (cvor)
		if (root->nodes[(int)word[i]] == nullptr)
			root->nodes[(int)word[i]] = create_node();

    // Krecemo se niz odgovarajucu granu, tj preko odgovarajuceg cvora
		root = root->nodes[(int)word[i]];
	}

  // Na kraju, dosli smo do kraja reci, pa nam bas ovaj cvor predstavlja list
	root->is_leaf = true;
}

// Funckija koja proverava da li se rec nalazi u stablu. Vraca true ukoliko se nalazi, false inace. Funkcija je slicna funkciji za dodavanje reci
bool find_word(Node *root, std::string &word)
{
  // Ukoliko trazimo u praznom stablu vracamo odmah false
	if (root == nullptr)
		return false;

  // Duzina reci
	int n = word.length();
  
  // Idemo kroz rec i krecemo se niz odgovarajuce grane, ukoliko one postoje, ukoliko neka grana ne postoji to znaci da se i-ti karakter reci ne nalazi u stablu, tj nema ni reci,
  // pa vracamo false
	for (int i = 0; i < n; i++)
	{
		root = root->nodes[(int)word[i]];

		if (root == nullptr)
			return false;
	}

  // Na kraju kada prodjemo kroz celu rec koju smo trazili
	return root->is_leaf;
}

void free_tree(Node *root)
{
  if (root == nullptr)
    return ;

  // Prvo oslobadjamo sva podstabla datog korena
  for (auto &node : root->nodes)
    free_tree(node);

  // A nakon toga i sam koren. Alokacija je vrsena pomocu malloc() pa oslobadjanje mora pomocu free()
  free(root);
}

int main ()
{
  std::vector<std::string> words = {"cod", "coder", "coding", "codecs"};

  Node *root = create_node();

  for (std::string &s : words)
    add_word(root, s);

  std::string s = "code";

  // boolalpha nam omogucava da pisemo true i false a ne 0 ili 1
  std::cout << std::boolalpha << find_word(root, s) << std::endl;

  free_tree(root);

  return 0;
}
