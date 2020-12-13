/*graph is bipartite if its vertexes can be grouped in a way that
every vertex of the first group is connected only to vertexes of the
second group and vice versa*/

#include <iostream>
#include <vector>

struct Graph {
	int nodes;
	std::vector<std::vector<int>> adj_list;
	std::vector<bool> visited;
	std::vector<bool> colors;
	bool is_bipartite = true;
};

void init_graph(Graph &g, int n){
	g.adj_list.reserve(n);
	g.nodes = n;
	g.visited.resize(n, false);
	g.colors.resize(n, 0);
}

void add_edge(Graph &g, int u, int v){
	g.adj_list[u].push_back(v);
	g.adj_list[v].push_back(u);
}

void DFS(Graph &g, int u, bool color){

	if(!g.is_bipartite){
		return;
	}

	g.visited[u] = true;
	if(color){
		g.colors[u] = 1;
	}

	auto begin = g.adj_list[u].begin();
	auto end = g.adj_list[u].end();

	while(begin != end){
		if(g.visited[*begin] && g.colors[*begin] == g.colors[u]){
			g.is_bipartite = false;
			return;
		}

		if(!g.visited[*begin]){
			DFS(g, *begin, !color);
		}

		begin++;
	}
}

int main(int argc, char** argv){

	Graph g;
	init_graph(g, 7);

	add_edge(g, 0, 1);
	add_edge(g, 0, 4);
	add_edge(g, 2, 1);
	add_edge(g, 2, 3);
	add_edge(g, 2, 4);
	add_edge(g, 6, 1);
	add_edge(g, 6, 4);
	add_edge(g, 5, 4);
	add_edge(g, 5, 3);
	//add_edge(g, 0, 2);

	DFS(g, 0, true);

	std::cout << std::boolalpha << g.is_bipartite << std::endl;

	exit(EXIT_SUCCESS);
}