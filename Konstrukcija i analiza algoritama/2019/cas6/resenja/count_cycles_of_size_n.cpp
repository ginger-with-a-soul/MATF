#include <iostream>
#include <vector>
#include <algorithm>

// Klasa kojom cemo predstavljati graf
class Graph
{
public:
  // Konstruktor za graf koji samo prima broj cvorova grafa
  Graph(int V)
  {
    // Broj cvorova grafa je jednak prosledjenom argumentu
    this->V = V;
    // Alociramo mesto za V bool vrednosti koje ce cuvati posecene cvorove
    visited.resize(V);
    // Na pocetku nijedan cvor nije posecen
    /********* C++ deo *********/
    // Funkcija std::fill() prima iterator na pocetak kolekcije i kraj kolekcije i vrednost kojom treba popuniti celu kolekciju
    std:fill(visited.begin(), visited.end(), false);

    // Alociramo memoriju za V vectora, jer znamo da ce ih biti V, a svaki od njih cemo povecavati za po jedan element pomocu vector.push_back()
    adjacency_list.resize(V);

    num_of_cycles = 0;
  }

  // Dodajemo granu u -> v i v -> u, posto je graf neusmeren, mozemo to ovako da oznacimo
  void add_edge(int u, int v)
  {
    // Sused cvora v je cvor u
    adjacency_list[v].push_back(u);
    // Sused cvora u je cvor v
    adjacency_list[u].push_back(v);
  }

  // Obilazak grafa u dubinu
  void DFS(int u, int start, int n)
  {
    // Kazemo da je cvor koji trenutno obradjujemo vec posecen
    visited[u] = true;

    // Ako smo nasli put duzine n - 1 i dosli do cvora u proveravamo da li iz cvora u postoji grana ka cvoru iz koga smo krenuli, ako postoji super, imamo ciklus
    // inace nemamo ciklus i samo oznacavamo cvor u kao neoznacen zbog narednih iteracija i zavrsavamo rekurziju
    if (n == 0) {
      if (std::find(adjacency_list[u].begin(), adjacency_list[u].end(), start) != adjacency_list[u].end()) {
        num_of_cycles++;
      }

      visited[u] = false;

      return ;
    }

    // Uzimamo iteratore na pocetak i kraj kolekcije kako bismo prosli kroz sve susede
    // Ako obratimo paznju videcemo da uzimamo adjacency_list[u].begin() i adjacency_list[u].end(), odnosno uzimamo vector suseda cvora u i obradjujemo njih
    auto begin = adjacency_list[u].begin();
    auto end = adjacency_list[u].end();

    while (begin != end) {
      // Ako smo vec posetili cvor necemo ponovo u njega ici, trazimo neposecene cvorove. Za njih pozivamo DFS rekurzivno.
      // Ovde se krije i uslov izlaska iz rekurzije, jer kada nema vise cvorova koji nisu poseceni necemo ici dalje, tj necemo pozivati DFS ponovo
      // begin i end su iteratori (pokazivacke promenljive), pa da bismo dobili vrednost koju cuva begin moramo da ga dereferenciramo, i zato imamo *begin
      // Kao dodatne argumente saljemo jos cvor iz koga smo krenuli kao i n - 1, jer sa trazimo put za 1 manje duzine
      if (!visited[*begin])
        DFS(*begin, start, n - 1);
      // Krecemo se kroz kolekciju
      begin++;
    }

    // Nakon sto obidjemo sve susede cvora stavljamo na false visited[u] jer mozda postoji drugi ciklus koji sadrzi u, i on ce biti razmotren kasnije
    visited[u] = false;

  }

  int num_of_cycles_of_size_n(int n)
  {
    // Kada se vratimo iz DFS-a obisli smo sve cvorove u komponenti grafa, tako da idemo samo kroz sve cvorove i oni koji nisu oznaceni pripadaju nekoj komponenti koju nismo
    // obisli, pa obilazimo tu komponentu i uvecavamo broj komponenti
    for (int i = 0; i < V - (n - 1); i++) {
      // if (!visited[i]) {
        DFS(i, i, n - 1);
        visited[i] = true;
    }

    return num_of_cycles / 2;
  }

private:
  // Lista susedstva. Imamo vector vector-a, sto znaci za svaki od cvorova [0,V) imamo po jednu listu koja cuva susede odgovarajuceg cvora
  std::vector<std::vector<int>> adjacency_list;
  // Broj cvorova grafa
  int V;
  // Lista posecenih cvorova. Da ne bismo ulazili u beskonacnu rekurziju ne zelimo da obilazimo cvorove koje smo vec obisli na putu kojim smo krenuli, zato cuvamo listu
  // posecenih cvorova
  std::vector<bool> visited;
  // Promenljiva koja cuva broj ciklusa duzine n
  int num_of_cycles;
};

int main ()
{
  int n;

  std::cin >> n;

  Graph g(4);

  g.add_edge(0, 1);
  g.add_edge(0, 3);
  g.add_edge(1, 2);
  // g.add_edge(1, 4);
  g.add_edge(2, 3);
  g.add_edge(2, 3);
  // g.add_edge(3, 4);

  std::cout << g.num_of_cycles_of_size_n(n) << "\n";

  return 0;
}
