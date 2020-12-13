#include <iostream>
#include <vector>

struct Graph {
	int nodes;
	std::vector<std::vector<int>> ajd_list;
	std::vector<bool> visited;
	int level;
	int nodesAtLevel = 0;
};

void init_graph(Graph &g, int n){
	g.ajd_list.reserve(n);
	g.nodes = n;
	g.visited.resize(n, false);
}

void add_edge(Graph &g, int u, int v){
	g.ajd_list[u].push_back(v);
}

void DFS(Graph &g, int u, int currentLevel){
	if(currentLevel == g.level && !g.visited[u]){
		g.nodesAtLevel += 1;
	}

	g.visited[u] = true;

	auto begin = g.ajd_list[u].begin();
	auto end = g.ajd_list[u].end();

	while(begin != end){
		if(!g.visited[*begin]){
			DFS(g, *begin, currentLevel + 1);
		}

		begin++;
	}
}

int main(int argc, char** argv){

	Graph g;
	init_graph(g, 8);

	int i;
	std::cin >> g.level;

	add_edge(g, 0, 1);
	add_edge(g, 0, 4);
	add_edge(g, 0, 7);
	add_edge(g, 4, 6);
	add_edge(g, 4, 5);
	add_edge(g, 4, 2);
	add_edge(g, 7, 3);
	
	DFS(g, 0, 0);

	std::cout << g.nodesAtLevel << std::endl;

	exit(EXIT_SUCCESS);
}