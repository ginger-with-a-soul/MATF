#include <iostream>
#include <vector>
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

    // Imamo V cvorova pa nam je vektor ulaznih stepena velicine V
    in_degrees.resize(V);
    // Na pocetku svi cvorovi imaju ulazni stepen 0
    std::fill(in_degrees.begin(), in_degrees.end(), 0);

    // Imamo V cvorova pa nam je vektor pozicija u topoloskom sortiranju velicine V
    position_in_topological_sorting.resize(V);
    // Na pocetku su svi na poziciji -1
    std::fill(in_degrees.begin(), in_degrees.end(), 0);
  }

  // Funkcija koja dodaje granu u -> v u graf, i menja ulazni stepen cvora
  void add_directed_edge(int u, int v)
  {
    // Sused cvora u je cvor v
    adjacency_list[u].push_back(v);

    // Kada dodamo granu u -> v znaci da se ulazni stepen cvora v povecava za 1
    in_degrees[v]++;

    // Kreiramo par (u, v) kao indikator da grana u -> v postoji u grafu
    std::pair<int, int> p(u ,v);

    edges.push_back(p);
  }

  // Funkcija koja dodaje grane u -> v i v -> u u graf
  void add_undirected_edge(int u, int v)
  {
    // Kreiramo par (u, v) i njega cemo smestiti u vektor neusmerenih grana
    std::pair<int, int> p(u, v);

    undirected_edges.push_back(p);
  }

  void topological_sorting()
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

    // Cvor koji je prvi u topoloskom sortiranju imati vrednost 0, a onda ce se ostali uvecavati
    int position_in_topological_sort = 0;

    while (nodes.size()) {
      // Uzimamo cvor sa pocetka reda
      tmp = nodes.front();

      // Skidamo cvor sa pocetka reda
      nodes.pop();

      // Postavljamo poziciju cvora u topoloskom sortiranju na odgovarajucu vrednost
      position_in_topological_sorting[tmp] = position_in_topological_sort;

      // Uvecavamo poziciju koja ce biti dodeljena ostalim elementima
      position_in_topological_sort++;

      // Prolazimo kroz sve cvorove koji su susedni cvoru tmp, smanjujemo im ulazni stepen, i onda ako je neki dosao do ulaznog stepena 0, znaci da smo obisli sve njegove
      // susede tako da se i on moze dodati na kraj reda
      for (int node : adjacency_list[tmp]) {
        in_degrees[node]--;

        if (!in_degrees[node])
          nodes.push(node);
      }
    }
  }

  // Modifikacija DFS-a koja proverava da li usmereni graf ima ciklus (zadatak sa 5. casa)
  bool DFS(int u)
  {
    // Kazemo da je cvor koji trenutno obradjujemo vec posecen
    visited[u] = true;

    // Uzimamo iteratore na pocetak i kraj kolekcije kako bismo prosli kroz sve susede
    // Ako obratimo paznju videcemo da uzimamo adjacency_list[u].begin() i adjacency_list[u].end(), odnosno uzimamo vector suseda cvora u i obradjujemo njih
    auto begin = adjacency_list[u].begin();
    auto end = adjacency_list[u].end();

    while (begin != end) {
      // Ako smo dosli do cvora koji smo vec posetili na trenutnom putu onda znaci da imamo ciklus i vracamo true. Obratiti paznju na deo NA TRENUTNOM PUTU,
      //kako imamo rekurziju i ako nam je graf 0 -> 1, 1 -> 2, 0 -> 2 on nema ciklus. Jedan put je 0 -> 1 -> 2 a drugi 0 -> 1 -> 2.
      // Da gledamo uopsteno da li je cvor posecen a ne NA TRENUTNOM PUTU onda bismo kada idemo 0 -> 2 naisli na cvor koji je vec posecen i onda bi bilo da imamo ciklus,
      // zato svaki put kada zavrsimo rekurzivni poziv kazemo da je cvor u neposecen, tj visited[u] = false;
      if (visited[*begin]) {
        return true;
      }
      // Ako nam neki rekurzivi poziv vrati true to znaci da smo u nekom podgrafu nasli ciklus pa samo vracamo true
      else if (DFS(*begin)) {
        return true;
      }

      // Krecemo se kroz kolekciju
      begin++;
    }

    // Objasnjenje gore
    visited[u] = false;
    // Nemamo ciklus na ovom putu, ako na nekom drugom putu naidjemo na ciklus to cemo u while petlji detektovati i vratiti true
    return false;
  }

  void assign_directions()
  {
    topological_sorting();

    // Prolazimo kroz vektor neusmerenih grana
    for (auto p : undirected_edges)
      // Ako je u pre v u topoloskom redosledu dodajemo granu u -> v
      if (position_in_topological_sorting[p.first] < position_in_topological_sorting[p.second]) {
        add_directed_edge(p.first, p.second);
        // Dodajemo odgovarajucu granu u vektor dodatih grana
        std::pair<int, int> tmp(p.first, p.second);
        added_edges.push_back(tmp);
      }
      // Inace dodajemo granu v -> u
      else {
        add_directed_edge(p.second, p.first);
        // Dodajemo odgovarajucu granu u vektor dodatih grana
        std::pair<int, int> tmp(p.second, p.first);
        added_edges.push_back(tmp);
      }

    // Koristimo modifikaciju DFS-a sa 5. casa da proverimo da li imamo ciklus, tj da li smo ispravno usmerili neusmeren grane
    if (DFS(0))
      std::cout << "Has a cycle\n";
    else
      std::cout << "Doesn't have a cycle\n";

    // Ispisujemo sve grane koje smo dobili
    std::cout << "All edges:\n";
    // Prolazimo kroz listu svih grana kako bismo proverili da li zaista nemamo cikluse
    for (auto p : edges)
      std::cout << p.first << " -> " << p.second << std::endl;

    // Ispisujemo samo one grane koje smo dodali
    std::cout << "Added edges:\n";
    // Prolazimo kroz listu svih grana kako bismo proverili da li zaista nemamo cikluse
    for (auto p : added_edges)
      std::cout << p.first << " -> " << p.second << std::endl;
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
  // Vektor koji cuva poziciju svakog cvora u topoloskom sortiranju
  std::vector<int> position_in_topological_sorting;
  // Vektor koji ce cuvati sve grane, sluzi samo za proveru resenja, da vidimo da li smo dobili graf bez ciklusa
  std::vector<std::pair<int, int>> edges;
  // Vektor koji ce cuvati neusmerene grane, da bismo nakon topoloskog sortiranja mogli da ih usmerimo
  std::vector<std::pair<int, int>> undirected_edges;
  // Vektor koji ce cuvati samo grane koje smo dodali, sluzi samo za proveru resenja, da vidimo da li smo dobili graf bez ciklusa i da vidimo koje su to grane dodate
  std::vector<std::pair<int, int>> added_edges;
};

int main ()
{
  Graph g(6);

  g.add_directed_edge(0, 1);
  g.add_directed_edge(0, 5);
  g.add_directed_edge(1, 2);
  g.add_directed_edge(1, 3);
  g.add_directed_edge(1, 4);
  g.add_directed_edge(2, 3);
  g.add_directed_edge(2, 4);
  g.add_directed_edge(3, 4);

  g.add_undirected_edge(0, 2);
  g.add_undirected_edge(0, 3);
  g.add_undirected_edge(4, 5);

  g.assign_directions();

  return 0;
}
