/* Kosaradzov algoritam se koristi za odredjivanje komp. jake povezanosti
usmerenog grafa.
Ako zelimo da vidimo da li je graf jako povezan onda pratimo 3 koraka:
	1. pokreni dfs i vidi da li mozes da dodjes do svih cvorova, ako ne, onda sigurno
	nije jako povezan
	2. obrni usmerenje svih grana i pokreni dfs iz istog cvora kao u koraku 1
	3. ako opet mozes da dodjes do svih cvorova, onda jeste jako povezan

TRANAZITIVNOST : ako iz svakog cvora mogu da dodjem do pocetnog
				 ako iz pocetnog cvora mogu da dodjem do svakog
			T -> iz svakog cvora mogu da dodjem do svakog
*/

#include <iostream>
#include <vector>
#include <algorithm>


struct Graph {
	int size;
	std::vector<std::vector<int>> adj_list1;
	std::vector<std::vector<int>> adj_list2;
	std::vector<bool> visited;
	int nodes_visited;
};

void init_graph(Graph &g, int n){
	g.size = n;
	g.adj_list1.reserve(n);
	g.adj_list2.reserve(n);
	g.visited.resize(n, false);
	g.nodes_visited = 0;
}

void add_edge(Graph &g, int u, int v){
	g.adj_list1[u].push_back(v);
	g.adj_list2[v].push_back(u);
}

void DFS(Graph &g, int u, int started){

	g.visited[u] = true;
	g.nodes_visited += 1;

	std::vector<int>::iterator begin;
	std::vector<int>::iterator end;

	if(!started){
		begin = g.adj_list1[u].begin();
		end = g.adj_list1[u].end();
	}
	else{
		begin = g.adj_list2[u].begin();
		end = g.adj_list2[u].end();
	}

	while(begin != end){
		if(!g.visited[*begin]){
			DFS(g, *begin, started);
		}

		begin++;
	}

}

void kosaraju(Graph &g, int u){
	DFS(g, u, 0);
	if(g.nodes_visited == g.size){
		g.visited.clear();
		g.visited.resize(g.size, false);
		g.nodes_visited = 0;
		DFS(g, u, 1);
		if(g.nodes_visited == g.size){
			std::cout << "Graph IS strongly connected!" << std::endl;
		}
		else{
			std::cout << "Graph IS NOT strongly connected!" << std::endl;
		}
	}
	else{
		std::cout << "Graph IS NOT strongly connected!" << std::endl;
	}
}

int main(int argc, char** argv){

	Graph g;
	init_graph(g, 5);

	add_edge(g, 0, 1);
	add_edge(g, 1, 2);
	add_edge(g, 2, 3);
	add_edge(g, 2, 4);
	add_edge(g, 3, 0);
	add_edge(g, 4, 2);
	//add_edge(g, 4, 5);
	
	kosaraju(g, 0);

	exit(EXIT_SUCCESS);
}