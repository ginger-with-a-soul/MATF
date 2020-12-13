#include <iostream>
#include <vector>

struct Graph {
	int node_num;
	std::vector<bool> visited;
	std::vector<std::vector<int>> adj_list;
	bool found = false;
	std::vector<int> path;
};

void init_graph(Graph &g, int n){
	g.node_num = n;
	g.visited.resize(n, false);
	g.adj_list.reserve(n);
}

void add_edge(Graph &g, int x, int y){
	g.adj_list[x].push_back(y);
}

void find_path(Graph &g, int u, int v){
	if(u == v){
		g.path.push_back(u);
		g.found = true;
		return;
	}
	g.visited[u] = true;
	g.path.push_back(u);

	auto begin = g.adj_list[u].begin();
	auto end = g.adj_list[u].end();

	while(begin != end){
		if(!g.visited[*begin] && !g.found){
			find_path(g, *begin, v);
		}
		begin++;
	}
	if(!g.found){
		g.path.pop_back();
	}
}

int main(int argc, char** argv){

	int n, u, v;
	std::cin >> n >> u >> v;

	Graph g;

	init_graph(g, n);

	add_edge(g, 0, 1);
	add_edge(g, 0, 2);
	add_edge(g, 1, 2);
	add_edge(g, 1, 3);
	add_edge(g, 2, 0);
	add_edge(g, 3, 4);
	add_edge(g, 4, 4);
	add_edge(g, 4, 2);

	find_path(g, u, v);

	if(g.found){
		std::cout << "Path found: ";
		for(auto x : g.path){
			std::cout << x << " ";
		}
	}
	else{
		std::cout << "Path not found!" << std::endl;
	}

	std::cout << std::endl;

	exit(EXIT_SUCCESS);
}