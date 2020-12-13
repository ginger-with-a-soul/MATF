#include <iostream>
#include <vector>
#include <algorithm>

struct Graph {
	int node;
	std::vector<std::vector<int>> ajd_list;
	std::vector<bool> visited;
	std::vector<int> path;
	std::vector<int> tmp_path;
	bool found = false;
};

void init_graph(Graph &g, int n){
	g.ajd_list.reserve(n);
	g.node = n;
	g.visited.resize(n, false);
	g.path.resize(n);
}

void add_edge(Graph &g, int u, int v){
	g.ajd_list[u].push_back(v);
}

void DFS(Graph &g, int u, int v){
	if(u == v){
		g.found = true;
		if(g.tmp_path.size() < g.path.size()){
			g.path.resize(g.tmp_path.size());
			std::copy_n(g.tmp_path.begin(), g.tmp_path.size(), g.path.begin());
			g.path.push_back(v);
		}
		return;
	}

	g.visited[u] = true;
	g.tmp_path.push_back(u);

	auto begin = g.ajd_list[u].begin();
	auto end = g.ajd_list[u].end();

	while(begin != end){
		if(!g.visited[*begin]){
			DFS(g, *begin, v);
		}

		begin++;
	}

	g.tmp_path.pop_back();
	g.visited[u] = false;
}

int main(int argc, char** argv){

	Graph g;

	init_graph(g, 5);

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

  	// add_edge(g, 0, 1);
  	// add_edge(g, 0, 4);
  	// add_edge(g, 1, 2);
  	// add_edge(g, 2, 4);
  	// add_edge(g, 2, 3);
  	// add_edge(g, 3, 4);
	DFS(g, 0, 2);

	if(g.found){
		std::cout << "Minimum path is: ";
		for(auto x : g.path){
			std::cout << x << " ";
		}
		std::cout << std::endl;
	}
	else{
		std::cout << "Path doesn't exist!" << std::endl;
	}

	exit(EXIT_SUCCESS);
}