#include <iostream>
#include <vector>
#include <list>
#include <queue>
#include <algorithm>

// Struktura koja predstavlja cvor binarnog stabla
struct Node
{
    // Konstruktor koji pravi cvor stabla, oba sina su nullprt na pocetku
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

void BFS(Node *root, std::vector<int> &levels)
{
  std::queue<Node *> nodes;

  nodes.push(root);

  levels[root->key] = 0;

  int current_level = 0;

  Node *pom;

  while (nodes.size()) {
    pom = nodes.front();
    nodes.pop();

    if (pom->left) {
      levels[pom->left->key] = levels[pom->key] + 1;
      nodes.push(pom->left);
    }

    if (pom->right) {
      levels[pom->right->key] = levels[pom->key] + 1;
      nodes.push(pom->right);
    }

    if (levels[pom->key] != current_level) {
      std::cout << "\n";
      current_level++;
    }

    std::cout << pom->key << " ";
  }

}
int main ()
{
  Node *root = nullptr;

  std::vector<int> keys = {4, 3, 5, 7, 1, 9, 8, 6};

  for (int x : keys)
    add_node(&root, x);

  int n = *std::max_element(keys.begin(), keys.end());

  std::vector<int> levels(n);

  BFS(root, levels);

  std::cout << "\n";
  
  free_tree(root);

  return 0;
}
