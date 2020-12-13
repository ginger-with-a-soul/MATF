#include <iostream>
#include <vector>
#include <queue>

struct Graph {
	int size;
	std::vector<std::vector<int>> adj_list;
	std::vector<bool> visited;
	int num_of_nodes = 0;
	int level;
	std::vector<int> node_level;
};

void init_graph(Graph &g, int n){
	g.size = n;
	g.adj_list.reserve(n);
	g.visited.resize(n, false);
	g.node_level.resize(n, 0);
}

void add_edge(Graph &g, int u, int v){
	g.adj_list[u].push_back(v);
}

void BFS(Graph &g, int u){

	int current_level = 0;

	std::queue<int> nodes;
	g.visited[u] = true;
	nodes.push(u);
	
	int tmp;

	while(!nodes.empty()){
		tmp = nodes.front();
		nodes.pop();

		auto begin = g.adj_list[tmp].begin();
		auto end = g.adj_list[tmp].end();

		if(g.node_level[tmp] == g.level){
			g.num_of_nodes += 1;
		}

		while(begin != end){
			if(!g.visited[*begin]){
				g.visited[*begin] = true;
				g.node_level[*begin] = g.node_level[tmp] + 1;
				nodes.push(*begin);
			}

			begin++;
		}
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
	
	BFS(g, 0);

	std::cout << g.num_of_nodes << std::endl;

	exit(EXIT_SUCCESS);
}