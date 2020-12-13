#include <iostream>
#include <vector>
#include <list>

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

// Funkcija za spiralni obilazak stabla po nivoima
void spiral_traversal(Node *root, bool leftToRight)
{
    // Red koji se koristi, koristimo listu jer kod nje takodje mozemo da uzimamo sa kraja i pocetka element i dodajemo na iste, alternativa deque
    std::list<Node *> nodes;

    // Dodajemo na kraj reda koren stabla
    nodes.push_back(root);

    // Odmah menjamo vrednost flega, jer krecemo od korena, i ako zelimo zaista da idemo sleva nadesno treba i fleg okrenuti na odgovarajuci nacin, prva iteracija petlje se izvrsava
    // za koren, i pretposlednja naredba menja fleg, ako je fleg true nakon prvog izvrsavanja postaje false i prvi nivo (nivoi idu od 0) se pise sdesna nalevo, a to ne zelimo
    leftToRight = !leftToRight;

    // Dok god imamo elemenata u redu
    while (nodes.size()) {
      // Velicina koju pamtimo da bismo znali koliko elemenata ispisujemo u koraku, zato sto u svakom koraku i dodajemo elemente, treba ispisati samo one koji su bili u redu na pocetku
      // iteracije spoljasnje petlje
      int n = nodes.size();

      // Dok god
      while (n) {
        // Ako treba sleva nadesno
        if (leftToRight) {
          // Uzimamo element sa pocetka reda
          Node *tmp = nodes.front();
          // Skidamo element sa pocetka reda, funkcija front() vraca element ali ga ne uklanja, mi zelimo da ga uklonimo
          nodes.pop_front();

          // Smanjujemo broj elemenata koje treba proveriti u ovoj iteraciji
          n--;

          // Ispisujemo vrednost cvora
          std::cout << tmp->key << " ";

          // Ukoliko ima levog sina dodajemo ga na KRAJ reda
          if (tmp->left)
            nodes.push_back(tmp->left);
          // Ukoliko ima desnog sina dodajemo ga na KRAJ reda
          if (tmp->right)
            nodes.push_back(tmp->right);
        }
        else {
          Node *tmp = nodes.back();
          nodes.pop_back();

          n--;

          std::cout << tmp->key << " ";

          // Ovde dodajemo prvo desnog pa levog sina jer dodajemo na pocetka, i kad dodje potreba da idemo sleva nadesno treba krenuti od levih ka desnim sinovima
          if (tmp->right)
          nodes.push_front(tmp->right);
          if (tmp->left)
            nodes.push_front(tmp->left);
        }
      }

      // Menjamo fleg da bismo rekli da idemo na drugu stranu
      leftToRight = !leftToRight;

      // Radi lepseg ispisa
      std::cout << "\n";
    }
}

int main ()
{
  Node *root = nullptr;

  std::vector<int> keys = {4,3,5,7,1,9,8,6};

  for (int x : keys)
    add_node(&root, x);

  spiral_traversal(root, true);

  free_tree(root);

  return 0;
}
