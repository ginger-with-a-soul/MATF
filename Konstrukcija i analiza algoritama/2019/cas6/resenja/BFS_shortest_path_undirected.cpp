#include <iostream>
#include <vector>
#include <stack>
#include <queue>

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

    // Alociramo mesto za V int vrednosti koje ce cuvati posecene cvorove
    parents.resize(V);

    // Na pocetku je roditelj svakog od cvorova -1
    std::fill(parents.begin(), parents.end(), -1);
  }

  // Funkcija koja dodaje grane u -> v  i v -> u u graf (posto je neusmeren)
  void add_edge(int u, int v)
  {
    // Sused cvora u je cvor v
    adjacency_list[u].push_back(v);
    // Sused cvora v je cvor u
    adjacency_list[v].push_back(u);
  }

  // Obilazak grafa u sirinu
  void BFS(int u, int v)
  {
    // Red koji koristimo za cuvanje cvorova grafa
    std::queue<int> nodes;

    // Dodajemo pocetni cvor iz koga krecemo
    nodes.push(u);

    visited[u] = true;

    // Pomocna promenljiva u koju cemo smestati cvorove koje uzimamo iz reda
    int pom;

    // Idemo dok god imamo cvorova u redu
    while (!nodes.empty()) {
      // Uzimamo cvor sa pocetka reda
      /********* C++ deo *********/
      // Metod front() samo uzima element sa pocetka reda ali ga i ne uklanja
      pom = nodes.front();
      // Skidamo cvor sa pocetka reda
      /********* C++ deo *********/
      // Metod pop() skida element sa pocetka reda
      nodes.pop();

      // Ako je cvor koji trenutno razmatramo bas ciljni cvor znaci da smo nasli put od u do v, ujedno je taj put i najkraci
      if (pom == v) {
        return ;
      }

      // Uzimamo iteratore na pocetak i kraj vektora koji cuva susede trenutnog cvora
      auto begin = adjacency_list[pom].begin();
      auto end = adjacency_list[pom].end();

      while (begin != end) {
        // Ukoliko nismo vec posetili cvor zelimo i njega da posetimo, pa ga dodajemo u red kako bi u nekoj od narednih iteracija bio obradjen
        if (!visited[*begin]) {
          visited[*begin] = true;
          parents[*begin] = pom;
          nodes.push(*begin);
        }
        // Krecemo se kroz kolekciju
        begin++;
      }
    }
  }

  // Funkcija koja ispisuje najkraci put od cvor u do cvora v ukoliko on postoji
  void print_shortest_path(int u, int v)
  {
    // Koristimo strukturu stek, jer cemo mi zapravo uzimati roditelje cvorova unazad. Neka nam je ciljni cvor 7 a pocetni 0, i najkraci put medju njima 0 -> 3 -> 7.
    // Mi znamo da je roditelj cvora 7 3 a roditelj cvora 3 0. Tim redosledom ih i obilazimo. Da bismo imali ispis 0 -> 3 -> 7, smestamo na stek roditelje, i onda
    // ih skidamo sa steka i ispisujemo
    std::stack <int> path;

    // BFS koji ce popuniti listu roditelja
    BFS(u, v);

    if (parents[v] == -1) {
      std::cout << "Ne postoji put!" << std::endl;
      return ;
    }

    // Stavljamo krajnji cvor svakako u putanju
    path.push(v);

    // Dok ne naidjemo na cvor iz kog smo krenuli (znamo da je njegov roditelj -1), krecemo se kroz roditelje, odnosno idemo unazad, od v do u
    while (parents[v] != -1) {
      v = parents[v];
      path.push(v);
    }

    int n = path.size();

    int x;

    // Dok god ima elemenata na steku ispisujemo ih
    while (n) {
      // Uzimamo element sa vrha steka
      x = path.top();
      // Skidamo element sa vrha steka
      path.pop();
      // Ako nije poslednji (ciljni cvor v) ispisujemo x ->
      if (n > 1)
        std::cout << x << " -> ";
      // Inace ispisujemo samo posldenji cvor na putanji
      else
        std::cout << x << std::endl;
      n--;
    }
  }

private:
  // Lista susedstva. Imamo vector vector-a, sto znaci za svaki od cvorova [0,V) imamo po jednu listu koja cuva susede odgovarajuceg cvora
  std::vector<std::vector<int>> adjacency_list;
  // Broj cvorova grafa
  int V;
  // Lista posecenih cvorova. Da ne bismo ulazili u beskonacnu rekurziju ne zelimo da obilazimo cvorove koje smo vec obisli na putu kojim smo krenuli, zato cuvamo listu
  // posecenih cvorova
  std::vector<bool> visited;
  // Vektor koji cuva za svaki cvor cvor iz koga smo dosli u njega
  std::vector<int> parents;
};

int main ()
{
  Graph g(8);

  g.add_edge(0, 1);
  g.add_edge(0, 3);
  g.add_edge(1, 2);
  g.add_edge(3, 4);
  g.add_edge(3, 7);
  g.add_edge(4, 5);
  g.add_edge(4, 6);
  g.add_edge(4, 7);
  g.add_edge(5, 6);
  g.add_edge(6, 7);

  int u, v;

  std::cin >> u >> v;

  g.print_shortest_path(u, v);

  return 0;
}
