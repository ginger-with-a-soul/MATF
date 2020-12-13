#include <iostream>
#include <stack>
#include <vector>
#include <unordered_map>

// Struktura koja predstavlja cvor binarnog stabla
struct Node
{
    Node ()
    {
      left = right = nullptr;
    }
    int key;
    Node *left;
    Node *right;
};

// Funkcija za dodavanje cvora u stablo. Obratiti paznju na **, menjamo strukturu stabla i moramo da saljemo pokazivac na njega da bismo to mogli
void add_node(Node **root, int key)
{
    if (*root == nullptr) {
      *root = new Node();
      (*root)->key = key;
      return ;
    }

    if ((*root)->key > key)
      add_node(&(*root)->left, key);
    else
      add_node(&(*root)->right, key);
}

// Funkcija za oslobadjanje stabla
void free_tree(Node *root)
{
  if (root == nullptr)
    return ;

  free_tree(root->left);
  free_tree(root->right);

  // delete a ne free() zato sto je memorija alocirana sa new (new Node())
  delete root;
}

void print_tree(Node *root)
{
  if (root == nullptr)
    return ;

  print_tree(root->left);
  print_tree(root->right);
  std::cout << root->key << " ";
}

// Funkcija koja proverava da li je dati cvor list
bool is_leaf(Node* node)
{
	return (node->left == nullptr && node->right == nullptr);
}

void print_path_iterative(Node* leaf_node, std::unordered_map<Node*, Node*> map)
{
	// Pomocni cvor koji cemo koristiti da idemo kroz mapu
	Node *tmp = leaf_node;

	// Dok ne dodjemo do korena (za njega vazi da mu je ptac zapravo null, nema ga)
	while (map[tmp] != nullptr) {
		std::cout << tmp->key << " -> ";
		// Pomocni cvor postaje otac prethodnog pomocnog, i na taj nacin se krecemo ka korenu
		tmp = map[tmp];
	}

	std::cout << tmp->key;
	std::cout << "\n";
}

// Modifikacija funkcije za iteraitvni postorder obilazak stabla
void postorder_iterative(Node* root)
{
	// Pravimo stek za smestanje cvorova koje obilazimo
	std::stack<Node*> stk;

	// Dodajemo koren na stek
	stk.push(root);

	// Mapa koja ce cuvati cvor i njegovog oca
	std::unordered_map<Node *, Node *> map;

	// Dodajemo u mapu koren i njegovog oca stavljamo na null, jer on ne postoji
	map[root] = nullptr;

	// Pomocna promenljiva u koju cemo smestati cvorove koje skidamo sa steka
	Node *tmp;

	while (stk.size()) {
		// Uzimamo cvor sa vrha steka i uklanjamo ga sa steka
		tmp = stk.top();
		stk.pop();

		// Ukoliko je cvor koji trenutno obradjujemo list, ispisemo putanju od njega do korena
		if (is_leaf(tmp))
			print_path_iterative(tmp, map);

		// Ukoliko cvor ima desnog sina dodamo u mapu njegovog sina i postavimo odgovarajuci cvor za oca
		if (tmp->right) {
			map[tmp->right] = tmp;
			stk.push(tmp->right);
		}

		// Ukoliko cvor ima levog sina dodamo u mapu njegovog sina i postavimo odgovarajuci cvor za oca
		if (tmp->left) {
			map[tmp->left] = tmp;
			stk.push(tmp->left);
		}
	}
}

int main()
{
  Node *root = nullptr;

  std::vector<int> keys = {4,3,5,7,1,9,8,6};

  for (int x : keys)
    add_node(&root, x);

  postorder_iterative(root);

	free_tree(root);

  return 0;
}
