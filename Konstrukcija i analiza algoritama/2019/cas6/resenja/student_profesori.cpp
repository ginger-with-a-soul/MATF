#include <iostream>
#include <vector>
#include <queue>
#include <numeric>

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

    // Imamo V cvorova pa nam je vektor ulazinh stepena velicine V
    in_degrees.resize(V);
    // Na pocetku svi cvorovi imaju ulazni stepen 0
    std::fill(in_degrees.begin(), in_degrees.end(), 0);
  }

  // Funkcija koja dodaje granu u -> v u graf, i menja ulazni stepen cvora
  void add_edge(int u, int v)
  {
    // Sused cvora u je cvor v
    adjacency_list[u].push_back(v);

    // Kada dodamo granu u -> v znaci da se ulazni stepen cvora v povecava za 1
    in_degrees[v]++;
  }

  bool topological_sorting(std::vector<int> &result)
  {
    // Red koji koristimo za cuvanje cvorova koje treba obraditi
    std::queue<int> nodes;

    // Odmah dodamo sve cvorove ciji je ulazni stepen 0
    for (int i = 0; i < V; i++)
      if (!in_degrees[i]) {
        nodes.push(i);
      }
    // Pomocni cvor u koji smestamo ono sto izvucemo iz reda
    int tmp;

    while (nodes.size()) {
      // Uzimamo cvor sa pocetka reda
      tmp = nodes.front();

      // Skidamo cvor sa pocetka reda
      nodes.pop();

      // Dodajemo cvor koji se trenutno razmatra u rezultat
      result.push_back(tmp);

      // Prolazimo kroz sve cvorove koji su susedni cvoru tmp, smanjujemo im ulazni stepen, i onda ako je neki dosao do ulaznog stepena 0, znaci da smo obisli sve njegove
      // susede tako da se i on moze dodati na kraj reda
      for (int node : adjacency_list[tmp]) {
        in_degrees[node]--;

        if (!in_degrees[node])
          nodes.push(node);
      }
    }

    return std::accumulate(in_degrees.begin(), in_degrees.end(), 0) == 0;
  }

private:
  // Lista susedstva. Imamo vector vector-a, sto znaci za svaki od cvorova [0,V) imamo po jednu listu koja cuva susede odgovarajuceg cvora
  std::vector<std::vector<int>> adjacency_list;
  // Broj cvorova grafa
  int V;
  // Lista posecenih cvorova. Da ne bismo ulazili u beskonacnu rekurziju ne zelimo da obilazimo cvorove koje smo vec obisli na putu kojim smo krenuli, zato cuvamo listu
  // posecenih cvorova
  std::vector<bool> visited;
  // Struktura stek u koju cemo smestati cvorove grafa
  std::vector<int> in_degrees;
};

int main ()
{
  int n, k, x;

  // Ucitavamo broj profesora
  std::cin >> n;

  // Pravimo graf sa n cvorova
  Graph g(n);

  for (int i = 0; i < n; i++) {
    std::cin >> k;

    // Ucitavamo profesore ciji su potpisi neophodni da bi se dobio potpis profesora i i dodajemo grane (x - 1) -> i, jer imamo usmerenu granu od profesora x - 1
    // ciji je potpis neophodan da bi profesor i dao potpis. x - 1 jer numeracija profesora krece od 1
    for(int j = 0; j < k; j++) {
      std::cin >> x;
      g.add_edge(x - 1, i);
    }
  }

  std::vector<int> result;

  if (g.topological_sorting(result)) {
    std::cout << "DA\n";

    for (int x : result)
      std::cout << x << "\n";
  }
  else
    std::cout << "NE\n";

  return 0;
}
