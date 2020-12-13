#include <iostream>
#include <vector>

struct Graph {
	int nodes;
	std::vector<std::vector<int>> adj_list;
	std::vector<bool> visited;
	std::vector<int> parents;
	bool cycle_found = false;
};

void init_graph(Graph &g, int n){
	g.nodes = n;
	g.adj_list.reserve(n);
	g.visited.resize(n, false);
	g.parents.resize(n, 0);
}

void add_edge(Graph &g, int u, int v){
	g.adj_list[u].push_back(v);
	g.adj_list[v].push_back(u);
}

void DFS(Graph &g, int u){

	if(g.cycle_found){
		return;
	}

	g.visited[u] = true;

	auto begin = g.adj_list[u].begin();
	auto end = g.adj_list[u].end();

	while(begin != end){
		if(g.visited[*begin] && g.parents[u] != *begin){
			g.cycle_found = true;
			return;
		}
		g.parents[*begin] = u;
		if(!g.visited[*begin]){
			DFS(g, *begin);
		}

		begin++;
	}
	g.visited[u] = false;
}

int main(int argc, char** argv){

	Graph g;
	init_graph(g, 3);

	add_edge(g, 0, 1);
	add_edge(g, 2, 1);
	add_edge(g, 2, 0);

	DFS(g, 0);

	if(g.cycle_found){
		std::cout << "There IS a cycle!" << std::endl;
	}
	else{
		std::cout << "There ISN'T a cycle!" << std::endl;
	}

	exit(EXIT_SUCCESS);
}