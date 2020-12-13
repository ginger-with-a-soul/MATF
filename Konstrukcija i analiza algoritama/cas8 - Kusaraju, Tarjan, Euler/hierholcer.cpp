/*
Hierholcerov algoritam: pretpostavimo da graf ima Ojlerov ciklus i da je usmeren.
Ako ima ciklus onda nije vazno iz kog cvora pokrecemo ali ako ima put onda je
vazno da algoritam pokrenemo iz cvora cija izlazni stepen je veci od ulaznig
(a zavrsice se u cvoru kome je ulazni stepen veci od izlaznog).

Koristimo stek na koji stavljamo trenutnu putanju kojom prolazimo, i jedan vektor
gde cuvamo nas Ojlerov put/ciklus. Nalazimo cvor iz kojeg treba da krenemo, dodajemo
ga na stek i vrtimo sve dok stek nije prazan. Ako iz naseg trenutnog cvora postoji
neka grana, dodajemo nas cvor na stek (na pocetku ce se dogoditi da prvi element imamo
dva puta na steku). Zatim uzimamo suseda naseg cvora koji ima najveci indeks, pamtimo
ga i skidamo tu granu a on postaje nas novi cvor. Ako nas trenutni cvor nema suseda,
dodajemo ga u nas Ojlerov put, on postaje ono sto imamo na vrhu steka a vrh steka skidamo.
Na kraju vektor za Ojlerov put ispisujemo od kraja.
*/

#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>


struct Graph {
	int size;
	std::vector<std::vector<int>> adj_list;
	std::vector<int> eulerian_path;
	std::vector<int> degrees;
	std::stack<int> stack;
};

void init_graph(Graph &g, int n){
	g.size = n;
	g.adj_list.reserve(n);
	g.degrees.resize(n, 0);
}

void add_edge(Graph &g, int u, int v){
	g.adj_list[u].push_back(v);
	g.degrees[u] += 1;
	g.degrees[v] -= 1;
}

void hierholzer(Graph &g, int u){

	g.stack.push(u);

	int tmp;

	while(!g.stack.empty()){
		if(g.adj_list[u].size()){
			g.stack.push(u);
			tmp = u;

			u = g.adj_list[u].back();
			g.adj_list[tmp].pop_back();
		}
		else{
			g.eulerian_path.push_back(u);
			u = g.stack.top();
			g.stack.pop();
		}
	}

	auto rbegin = g.eulerian_path.rbegin();
	auto rend = g.eulerian_path.rend();

	while(rbegin != rend){
		std::cout << *rbegin << " ";
		rbegin++;
	}

}

int main(int argc, char** argv){

	Graph g;

  	init_graph(g, 5);

  	add_edge(g, 0, 1);
  	add_edge(g, 1, 2);
  	add_edge(g, 1, 3);
  	add_edge(g, 2, 0);
  	add_edge(g, 3, 4);
  	add_edge(g, 4, 1);

  	// add_edge(g, 0, 1);
  	// add_edge(g, 0, 2);
  	// add_edge(g, 1, 1);
  	// add_edge(g, 1, 3);
  	// add_edge(g, 1, 3);
  	// add_edge(g, 2, 0);
  	// add_edge(g, 2, 1);
  	// add_edge(g, 2, 4);
  	// add_edge(g, 3, 2);
  	// add_edge(g, 3, 5);
  	// add_edge(g, 4, 5);
  	// add_edge(g, 5, 2);

	int start = *std::find_if(g.degrees.begin(), g.degrees.end(), [](const int x){return x > 0;});

  	hierholzer(g, start);

	exit(EXIT_SUCCESS);
}