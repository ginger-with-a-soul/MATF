#include <iostream>
#include <stack>
#include <vector>

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

void postorder_iterative(Node* root)
{
	// Kreiramo stek na koji smestamo inicijalne cvorove stabla redom kojim ih obilazimo
	std::stack<Node*> stk;
  // Stavljamo koren na stek
	stk.push(root);

	// Kreiramo stek na kome cuvamo cvorove u redosledu kojim treba da budu ispisani
	std::stack<int> out;

	// Dok ne obidjemo sve cvorove
	while (!stk.empty())
	{
		// Uzimamo cvor sa vrha steka
		Node *curr = stk.top();

    // Brisemo cvor sa vrha steka
		stk.pop();

    // Stavljamo cvor na vrh steka za ispis
		out.push(curr->key);

    // Stavljamo levog sina ukoliko postoji
		if (curr->left)
			stk.push(curr->left);

    // Stavljamo desnog sina ukoliko postoji
    if (curr->right)
    stk.push(curr->right);
	}

	// Idemo kroz stek za ispis elemenata i ispisujemo ih redom
	while (!out.empty())
	{
		std::cout << out.top() << " ";
		out.pop();
	}
}

int main()
{
  Node *root = nullptr;

  std::vector<int> keys = {4,3,5,7,1,9,8,6};

  for (int x : keys)
    add_node(&root, x);

  print_tree(root);

  std::cout << std::endl;

  postorder_iterative(root);

  std::cout << std::endl;

  free_tree(root);

	return 0;
}
