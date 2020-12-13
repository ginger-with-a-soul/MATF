#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>


struct Graph {
	int size;
	std::vector<std::vector<int>> adj_list;
	std::vector<bool> visited;
};

void init_graph(Graph &g, int n){
	g.size = n;
	g.adj_list.reserve(n);
	g.visited.resize(n, false);
}

void add_edge(Graph &g, int u, int v){
	g.adj_list[u].push_back(v);
}

int main(int argc, char** argv){

	Graph g;
	init_graph(g, );

	add_edge(g, , );

	exit(EXIT_SUCCESS);
}