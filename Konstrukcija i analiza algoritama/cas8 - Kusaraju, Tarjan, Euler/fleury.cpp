/*
Pretpostavimo da graf jeste Ojlerov. Graf ima Ojlerov put ako ima tacno dva
cvora neparnog stepena. Graf je Ojlerov ciklus ako su mu svi cvorovi koji su
povezani parnog stepena. Moramo da pazimo da pretragu krecemo iz cvora koji
je povezan a ne izolovan.

Flerijev algoritam vrsi ispis Ojlerovog puta/ciklusa. Ako je u pitanju put,
nasu pretragu moramo da krenemo od jednog cvora neparnog stepena i zavrsicemo
u drugom cvoru neparnog stepena. Ako je u pitanju ciklus, bitno je samo da ne
krenemo od izolovanog cvora i Flerijev algoritam garantuje da cemo se vratiti u
cvor iz kog smo krenuli.

Prvo prebrojimo cvorove neparnog stepena, ako ih nema, onda krecemo pretragu od
bilo kog cvora koji ima stepen razlicit od nula (znaci da nije izolovan cvor).
Inace, posto smo pp. da je graf Ojlerov, krecemo pretragu od nekog cvora neparnog
stepena.

Prolazimo kroz listu suseda tog cvora i gledamo da li smemo da izbrisemo granu.
Granu smemo da izbrisemo ako je ona poslednja iz naseg cvora, inace, izbrisemo granu,
pokrenemo dfs i vidimo da li je ta grana koju smo izbrisali bila most do nekog cvora.
Bila je most ako taj cvor posle dfs-a nije posecen. Vratimo granu koju smo izbrisali.

PAZITI NA BREAK; KOD PRINT_EULER'S PATH
*/

#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>


struct Graph {
	int size;
	std::vector<std::vector<int>> adj_list;
	std::vector<bool> visited;
	std::vector<int> degrees;
};

void init_graph(Graph &g, int n){
	g.size = n;
	g.adj_list.reserve(n);
	g.visited.resize(n, false);
	g.degrees.resize(n, 0);
}

void add_edge(Graph &g, int u, int v){
	g.adj_list[u].push_back(v);
	g.adj_list[v].push_back(u);
	g.degrees[u] += 1;
	g.degrees[v] += 1;
}

void remove_edge(Graph &g, int u, int v){
	g.adj_list[u].erase(std::find(g.adj_list[u].begin(), g.adj_list[u].end(), v));
	g.adj_list[v].erase(std::find(g.adj_list[v].begin(), g.adj_list[v].end(), u));
}

void DFS(Graph &g, int u){
	g.visited[u] = true;

	auto begin = g.adj_list[u].begin();
	auto end = g.adj_list[u].end();

	while(begin != end){
		if(!g.visited[*begin]){
			DFS(g, *begin);
		}
		begin++;
	}
}

bool edge_is_valid(Graph &g, int u, int v){
	if(g.adj_list[u].size() == 1){
		return true;
	}

	remove_edge(g, u, v);	g.degrees[u]--; g.degrees[v]--;

	std::fill(g.visited.begin(), g.visited.end(), false);

	DFS(g, u);

	add_edge(g, u, v);

	if(!g.visited[v]){
		return false;
	}
	else{
		return true;
	}
}

void print_eulerian(Graph &g, int u){
	for(auto v : g.adj_list[u]){
		if(edge_is_valid(g, u, v)){
			std::cout << u << " -> " << v;
			std::cout << std::endl;
			remove_edge(g, u, v);
			print_eulerian(g, v);
			break;
		}
	}
}


void fleury(Graph &g){
	int count_odd = std::count_if(g.degrees.begin(), g.degrees.end(), [](const int x){return x % 2;});
	int start;

	if(count_odd == 2){
		start = *std::find_if(g.degrees.begin(), g.degrees.end(), [](const int x){return x % 2;});
		print_eulerian(g, start);
	}
	else{
		start = *std::find_if(g.degrees.begin(), g.degrees.end(), [](const int x){return x > 0;});
		print_eulerian(g, start);
	}
}

int main(int argc, char** argv){

	Graph g;

	init_graph(g, 5);

  	// Put
  	// add_edge(g, 0, 1);
  	// add_edge(g, 0, 2);
  	// add_edge(g, 1, 2);
  	// add_edge(g, 2, 3);
	 
  	// Ciklus
  	// add_edge(g, 0, 1);
  	// add_edge(g, 1, 2);
  	// add_edge(g, 2, 0);
	 
  	add_edge(g, 0, 1);
  	add_edge(g, 0, 2);
  	add_edge(g, 0, 3);
  	add_edge(g, 1, 2);
  	add_edge(g, 1, 3);
  	add_edge(g, 2, 3);
  	add_edge(g, 2, 4);
  	add_edge(g, 3, 4);

  	fleury(g);;

	exit(EXIT_SUCCESS);
}