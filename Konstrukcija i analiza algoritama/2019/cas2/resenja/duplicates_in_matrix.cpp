#include <iostream>
#include <vector>

#define MAX 100

// Struktura cvor u kojoj cuvamo jedan cvor prefiksnog stabla
struct Node
{
  // Konstruktor za cvor
  Node()
  {
    // Broj pojavljivanja je 0, pa ce se za listove azurirati
    count = 0;
    // Oba potomka svakog cvora su nullptr, tj ne postoje dok ne dodjemo u situaciju da moramo da ih kreiramo
    nodes[0] = nodes[1] = nullptr;
  }

  // Prebrojava koliko se puta rec, u nasem slucaju red matrice javlja u stablu, samo ce listovi imati vrednost ove promenljive razlicitu od 0
  int count;
  // Nema potrebe ni za kakvim mapama, znamo da je matrica binarna, tako da sigurno imamo najvise 2 potomka
  Node *nodes[2];
};

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
    root->nodes[row[i]] = new Node();

  // Rekurzivno nastavljamo do lista
  add_row(root->nodes[row[i]], row, n, i + 1, number);
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

  Node *root = new Node();

  for (int i = 0;i < n; i++)
    add_row(root, matrix[i], n, 0, i + 1);

  return 0;
}
