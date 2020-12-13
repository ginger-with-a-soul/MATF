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
    // Alociramo prostor
    degrees.resize(V);

    // Postavljamo stepene na 0
    std::fill(degrees.begin(), degrees.end(), 0);
  }

  // Funkcija koja dodaje grane u -> v i v - > u u graf
  void add_edge(int u, int v)
  {
    degrees[u]++;
    degrees[v]++;
  }

  // Funkcija koja vraca 0 ako graf nije Ojlerov, 1 ako graf ima Ojlerov put, ali nema Ojlerov ciklus i 2 ako ima Ojlerov ciklus
  bool is_eulerian()
  {
    int count_odd = num_of_odd_vertices();

    return count_odd == 0;
  }

  // Funkcija koja broji koliko imamo cvorova neparnog stepena u grafu
  int num_of_odd_vertices()
  {
    // Broj cvorova neparnog stepena
    int count_odd = 0;

    // Ako imamo neki cvor sa ukupnim neparnim stepenom uvecavamo broj takvih cvorova
    for (int i = 0; i < V; i++)
      if (degrees[i] % 2)
        count_odd++;

    return count_odd;
  }

private:
  int V;
  std::vector<int> degrees;
};

int main ()
{
  int n, m;

  std::cin >> n >> m;

  Graph g(n);

  int x, y;

  for (int i = 0; i < m; i++) {
    std::cin >> x >> y;
    g.add_edge(x, y);
  }

/*  // Ciklus
  g.add_edge(0, 1);
  g.add_edge(1, 2);
  g.add_edge(2, 0);

  // Nije Ojlerov
  // g.add_edge(0, 1);
  // g.add_edge(1, 2);
  // g.add_edge(1, 4);
  // g.add_edge(2, 3);

  // Put
  // g.add_edge(0, 1);
  // g.add_edge(0, 2);
  // g.add_edge(0, 3);
  // g.add_edge(1, 2);
  // g.add_edge(1, 3);
  // g.add_edge(2, 3);
  // g.add_edge(2, 4);
  // g.add_edge(3, 4);*/

  bool eulerian = g.is_eulerian();

  std::cout << ((eulerian == true) ? ("DA") : ("NE")) << std::endl;

  return 0;
}
