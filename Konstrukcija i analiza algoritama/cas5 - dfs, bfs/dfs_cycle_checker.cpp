#include <iostream>
#include <vector>

struct Graph {
	int nodes;
	std::vector<std::vector<int>> adj_list;
	std::vector<bool> visited;
	bool cycle_found = false;
};

void init_graph(Graph &g, int n){
	g.adj_list.reserve(n);
	g.visited.resize(n, false);
	g.nodes = n;
}

void add_edge(Graph &g, int u, int v){
	g.adj_list[u].push_back(v);
}

void DFS(Graph &g, int u){
	g.visited[u] = true;

	auto begin = g.adj_list[u].begin();
	auto end = g.adj_list[u].end();

	while(begin != end){
		if(!g.visited[*begin]){
			DFS(g, *begin);
		}
		else{
			g.cycle_found = true;
			return;
		}

		begin++;
	}
	g.visited[u] = false;
}

int main(int argc, char** argv){

	Graph g;
	init_graph(g, 5);

	//add_edge(g, 0, 1);
	//add_edge(g, 1, 2);
	//add_edge(g, 2, 0);

	//add_edge(g, 0, 1);
	//add_edge(g, 0, 2);
	//add_edge(g, 2, 1);

	add_edge(g, 0, 1);
  	add_edge(g, 1, 0);
  	add_edge(g, 0, 4);
  	add_edge(g, 4, 0);
  	add_edge(g, 1, 2);
  	add_edge(g, 2, 1);
  	add_edge(g, 2, 4);
  	add_edge(g, 4, 2);
  	add_edge(g, 2, 3);
  	add_edge(g, 3, 2);
  	add_edge(g, 3, 4);
  	add_edge(g, 4, 3);

	DFS(g, 1);

	if(g.cycle_found){
		std::cout << "There IS a cycle!" << std::endl;
	}
	else{
		std::cout << "There ISN'T a cycle!" << std::endl;
	}

	exit(EXIT_SUCCESS);
}