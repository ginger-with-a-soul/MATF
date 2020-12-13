/* jednom kad udjemo u cvor, garantovano imamo najkrace rastojanje
od pocetnog do onog u koji smo usli. Dajkstrin algoritam radi samo za grane pozitivne
tezine*/

/* ako zelimo najkraci put do neka dva cvora, onda nadjemo najkrace puteve do svih cvorova
a onda ispisemo samo onaj koji zelimo*/

/*krenemo od naseg cvora za koji zelimo da nadjemo najkrace puteve, kazemo da smo ga posetili
i stavimo da je udaljenost od njega 0. Zatim u red sa prioritetom (poredjan rastuce) stavimo
nas prvi cvor i sve dok je elemenata u redu vrtimo. Ako smo vec bili u cvoru, samo nastavimo u
petlji. Inace, kazemo da smo bili u tom cvoru i proverimo da li je udaljenost od njegovih
suseda manja od udaljenosti do naseg trenutnog cvora + cene puta do naseg suseda. Ako jeste,
azuriramo je na novu cenu puta do suseda i stavimo ga u red.*/

#include <iostream>
#include <queue>
#include <vector>
#include <climits>

struct Graph {
	int size;
	std::vector<std::vector<std::pair<int, int>>> ajd_list;
	std::vector<bool> visited;
	std::vector<int> distances;
};

void init_graph(Graph &g, int n){
	g.size = n;
	g.ajd_list.reserve(n);
	g.visited.resize(n, false);
	g.distances.resize(n, INT_MAX);
}

void add_edge(Graph &g, int u, int v, int d){
	g.ajd_list[u].push_back(std::make_pair(v, d));
	g.ajd_list[v].push_back(std::make_pair(u, d));
}


void dijkstra(Graph &g, int u){

	std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>> nodes;

	
	g.distances[u] = 0;

	std::pair<int, int> tmp;

	nodes.push(std::make_pair(u, g.distances[u]));

	while(!nodes.empty()){
		tmp = nodes.top();
		nodes.pop();

		if(g.visited[tmp.first]){
			continue;
		}

		g.visited[tmp.first] = true;

		for(auto &x : g.ajd_list[tmp.first]){
			if(g.distances[x.first] > x.second + g.distances[tmp.first]){
				g.distances[x.first] = x.second + g.distances[tmp.first];
				nodes.push(std::make_pair(x.first, g.distances[x.first]));
			}
		}

	}

	for(int i = 0; i < g.size; i++){
		std::cout << u << " -> " << i << ": " << g.distances[i] << std::endl;
	}

}

int main(int argc, char** argv){

	Graph g;
	init_graph(g, 9);

	add_edge(g, 0, 1, 4);
	add_edge(g, 0, 7, 8);
	add_edge(g, 1, 7, 11);
	add_edge(g, 1, 2, 8);
	add_edge(g, 7, 8, 7);
	add_edge(g, 7, 6, 1);
	add_edge(g, 6, 8, 6);
	add_edge(g, 6, 5, 2);
	add_edge(g, 8, 2, 2);
	add_edge(g, 2, 3, 7);
	add_edge(g, 2, 5, 4);
	add_edge(g, 5, 3, 14);
	add_edge(g, 5, 4, 10);
	add_edge(g, 3, 4, 9);

	dijkstra(g, 0);

	exit(EXIT_SUCCESS);
}