 #include <iostream>
#include <vector>

#define MAX 100

// Struktura cvor u kojoj cuvamo jedan cvor prefiksnog stabla
struct Node
{
  // Prebrojava koliko se puta rec, u nasem slucaju red matrice javlja u stablu, samo ce listovi imati vrednost ove promenljive razlicitu od 0
  int count;
  // Nema potrebe ni za kakvim mapama, znamo da je matrica binarna, tako da sigurno imamo najvise 2 potomka
  Node *nodes[2];
};

Node *create_node()
{
  // Ovde moze alokacija pomocu malloc-a, jer imamo niz fiksne duzine 2.
  Node *new_node = (Node *)malloc(sizeof(Node));

  // Na pocetku za svaki red kazemo da se ne javlja nijednom, ovaj parametar ce biti azuriran u listovima kako budemo dolazili do kraja redova
  new_node-> count = 0;

  // Na pocetku cvor nema ni levog ni desnog sina
  new_node->nodes[0] = new_node->nodes[1] = nullptr;

  return new_node;
}

// Funckija za dodavanje reda u stablo, row je red koji se dodaje, n je njegova duzina, i pozicija u redu do koje smo stigli, number je redni broj reda, kako bismo znali koji reda
// je duplikat
void add_row(Node *root, int row[MAX], int n, int i, int number)
{
  // Ukoliko smo dosli do kraja reda azuriramo broj pojavljivanja tog reda u stablu (i samim tim matrici). Ukoliko je broj pojavljivanja > 1 onda prijavljujemo duplikat
  // Kako smo dodali ceo red, sam cvor je list pa zavrsavamo rekurziju
  if (i == n) {
    root->count++;

    if (root->count > 1)
      std::cout << "Duplicate row: #" << number << std::endl;

    return ;
  }

  // Ukoliko nemamo odgovarajuci cvor u stablu moramo da ga kreiramo
  if (root->nodes[row[i]] == nullptr)
    root->nodes[row[i]] = create_node();

  // Rekurzivno nastavljamo do lista
  add_row(root->nodes[row[i]], row, n, i + 1, number);
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
  int matrix[MAX][MAX] = {
    {1, 0, 0, 1, 0},
		{0, 1, 1, 0, 0},
		{1, 0, 0, 1, 0},
		{0, 0, 1, 1, 0},
		{0, 1, 1, 0, 0}
  };

  int n = 5;

  Node *root = create_node();

  for (int i = 0; i < n; i++)
    add_row(root, matrix[i], n, 0, i + 1);

  free_tree(root);
  
  return 0;
}
