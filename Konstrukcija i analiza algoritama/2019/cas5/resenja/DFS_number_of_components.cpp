#include <iostream>
#include <vector>

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

    // Na pocetku kazemo da nemamo nijednu komponentu
    number_of_components = 0;
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
  void DFS(int u)
  {
    // Kazemo da je cvor koji trenutno obradjujemo vec posecen
    visited[u] = true;

    // Uzimamo iteratore na pocetak i kraj kolekcije kako bismo prosli kroz sve susede
    // Ako obratimo paznju videcemo da uzimamo adjacency_list[u].begin() i adjacency_list[u].end(), odnosno uzimamo vector suseda cvora u i obradjujemo njih
    auto begin = adjacency_list[u].begin();
    auto end = adjacency_list[u].end();

    while (begin != end) {
      // Ako smo vec posetili cvor necemo ponovo u njega ici, trazimo neposecene cvorove. Za njih pozivamo DFS rekurzivno.
      // Ovde se krije i uslov izlaska iz rekurzije, jer kada nema vise cvorova koji nisu poseceni necemo ici dalje, tj necemo pozivati DFS ponovo
      // begin i end su iteratori (pokazivacke promenljive), pa da bismo dobili vrednost koju cuva begin moramo da ga dereferenciramo, i zato imamo *begin
      if (!visited[*begin])
        DFS(*begin);
      // Krecemo se kroz kolekciju
      begin++;
    }
  }

  int num_of_components()
  {
    // Kada se vratimo iz DFS-a obisli smo sve cvorove u komponenti grafa, tako da idemo samo kroz sve cvorove i oni koji nisu oznaceni pripadaju nekoj komponenti koju nismo
    // obisli, pa obilazimo tu komponentu i uvecavamo broj komponenti
    for (int i = 0; i < V; i++)
      if (!visited[i]) {
        number_of_components++;
        DFS(i);
      }

    return number_of_components;
  }

private:
  // Lista susedstva. Imamo vector vector-a, sto znaci za svaki od cvorova [0,V) imamo po jednu listu koja cuva susede odgovarajuceg cvora
  std::vector<std::vector<int>> adjacency_list;
  // Broj cvorova grafa
  int V;
  // Lista posecenih cvorova. Da ne bismo ulazili u beskonacnu rekurziju ne zelimo da obilazimo cvorove koje smo vec obisli na putu kojim smo krenuli, zato cuvamo listu
  // posecenih cvorova
  std::vector<bool> visited;
  // Promenljiva koja oznacava broj komponenti grafa
  int number_of_components;
};

int main ()
{
  Graph g(6);

  g.add_edge(0, 1);
  g.add_edge(0, 2);
  g.add_edge(1, 2);
  g.add_edge(2, 0);
  g.add_edge(2, 3);
  g.add_edge(3, 3);
  g.add_edge(4, 5);
  g.add_edge(4, 4);
  g.add_edge(5, 4);

  std::cout << g.num_of_components() << "\n";

  return 0;
}
