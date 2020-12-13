#include <iostream>
#include <queue>
#include <cstring>

#define MAX 10

struct Node
{
    Node ()
    {

    }

    Node(int i, int j, int dist)
    {
        x = i;
        y = j;
        distance = dist;
    }

    // x koordinata
    int x;
    // y koordinata
    int y;
    // udaljenost od pocetnog cvora
    int distance;
};

bool allowed(int maze[][MAX], bool visited[][MAX], int i, int j, int n)
{
  // Proveravamo validnost poteza, ne smemo da izadjemo van granica lavirinta, niti smemo da pristupamo poljima koja se su vec posecena kao ni onima cija je vrednost 0, jer tu nema puta
  if (i >= 0 && i < n && j >= 0 && j < n && maze[i][j] == 1 && visited[i][j] == false)
    return true;

  return false;
}

void BFS (int maze[][MAX], int i, int j, int x, int y, int n)
{
  // Pravimo matricu u kojoj pamtimo za svako polje da li je vec poseceno
  bool visited [MAX][MAX];

  // Postavljamo sva polja na false, odnosno nijedno polje nije vec poseceno
  memset(visited, false, sizeof visited);

  // Red u koji smestamo svaki "cvor" na koji naidjemo
  std::queue<Node> nodes;

  // Dodajemo pocetni cvor u red i oznacavamo ga kao posecen
  nodes.push({i, j, 0});
  visited[i][j] = true;

  Node tmp;

  // Dok god ima cvorova u redu
  while (nodes.size()) {
    // Uzimamo element sa pocetka reda
    tmp = nodes.front();
    nodes.pop();

    // Ukoliko smo dosli do cilja ispisujemo duzinu puta i izlazimo iz programa
    if (tmp.x == x && tmp.y == y) {
      std::cout << tmp.distance << std::endl;
      return ;
    }

    // Proveravamo sve moguce kombinacije od neke pozicije, i ako je moguce ici na neku od pozicija, odgovarajuci cvor stavljamo u red, i oznacavamo da je posecen
    if (allowed(maze, visited, tmp.x - 1, tmp.y, n)) {
      nodes.push({tmp.x - 1, tmp.y, tmp.distance + 1});
      visited[tmp.x - 1][tmp.y] = true;
    }
    if (allowed(maze, visited, tmp.x + 1, tmp.y, n)) {
      nodes.push({tmp.x + 1, tmp.y, tmp.distance + 1});
      visited[tmp.x + 1][tmp.y] = true;
    }
    if (allowed(maze, visited, tmp.x, tmp.y - 1, n)) {
      nodes.push({tmp.x, tmp.y - 1, tmp.distance + 1});
      visited[tmp.x][tmp.y - 1] = true;
    }
    if (allowed(maze, visited, tmp.x, tmp.y + 1, n)) {
      nodes.push({tmp.x, tmp.y + 1, tmp.distance + 1});
      visited[tmp.x][tmp.y + 1] = true;
    }
  }
}

int main ()
{
  int mat[MAX][MAX] =
	{
		{ 1, 1, 1, 1, 1, 0, 0, 1, 1, 1 },
		{ 0, 1, 1, 1, 1, 1, 0, 1, 0, 1 },
		{ 0, 0, 1, 0, 1, 1, 1, 0, 0, 1 },
		{ 1, 0, 1, 1, 1, 0, 1, 1, 0, 1 },
		{ 0, 0, 0, 1, 0, 0, 0, 1, 0, 1 },
		{ 1, 0, 1, 1, 1, 0, 0, 1, 1, 0 },
		{ 0, 0, 0, 0, 1, 0, 0, 1, 0, 1 },
		{ 0, 1, 1, 1, 1, 1, 1, 1, 0, 0 },
		{ 1, 1, 1, 1, 1, 0, 0, 1, 1, 1 },
		{ 0, 0, 1, 0, 0, 1, 1, 0, 0, 1 },
	};

	BFS(mat, 0, 0, 7, 5, 10);

  return 0;
}
