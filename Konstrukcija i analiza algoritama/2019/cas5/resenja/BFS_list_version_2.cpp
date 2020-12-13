#include <iostream>
#include <vector>
#include <queue>

// BFS pretraga grafa koji je zadat pravom listom povezanosti
// Kako nemamo klase u ovom primeru, kao argumente saljemo listu susedstva i vector posecenih cvorova
void BFS(int u, std::vector<int> &adjacency_list, std::vector<bool> &visited)
{
  // Red koji koristimo za cuvanje cvorova grafa
  std::queue<int> nodes;

  // Dodajemo pocetni cvor iz koga krecemo
  nodes.push(u);

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

    // Kazemo da je trenutni cvor posecen
    visited[pom] = true;

    // Ispisujemo trenutni cvor
    std::cout << pom << " ";

    int n;

    // Ukoliko nam je sledeci element u listi manji od trenutnog, to znaci da krecemo sa nabrajanjem suseda za cvorove, i to znaci da smo dosli do poslednjeg cvora grafa
    // Njegovi susedi se u listi nalaze od pozicije adjacency_list[pom] do kraja liste. Zato razmatramo 2 slucaja, jedan kada imamo poslednji cvor u grafu i drugi gde imamo
    // ostale cvorove
    if (adjacency_list[pom + 1] < adjacency_list[pom])
      // Ukoliko je u pitanju poslednji cvor u grafu, idemo od adjacency_list[pom] do kraja liste
      n = adjacency_list.size();
    else
      // Ukoliko nije u pitanju poslednji cvor u grafu, idemo od adjacency_list[pom] do adjacency_list[pom + 1] gde pocinju susedi narednog cvora
      n = adjacency_list[pom + 1];

    for (int i = adjacency_list[pom]; i < n; i++)
      // Ukoliko nismo vec posetili cvor zelimo i njega da posetimo, pa ga dodajemo u red kako bi u nekoj od narednih iteracija bio obradjen
      if (!visited[adjacency_list[i]])
        nodes.push(adjacency_list[i]);
  }

  std::cout << "\n";
}

int main ()
{
  int v;

  std::cin >> v;

  std::vector<int> adjacency_list = { 4, 6, 7, 9, 1, 2, 2, 0, 3, 3 };

  std::vector<bool> visited;

  visited.resize(4);

  std::fill(visited.begin(), visited.end(), false);

  BFS(v, adjacency_list, visited);

  return 0;
}
