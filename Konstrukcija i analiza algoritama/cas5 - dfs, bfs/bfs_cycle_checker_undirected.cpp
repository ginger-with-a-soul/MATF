#include <iostream>
#include <vector>
#include <queue>

struct Graph {
	int nodes;
	std::vector<std::vector<int>> ajd_list;
	std::vector<bool>visited;
	std::vector<int> parents;
};

void init_graph(Graph &g, int n){
	g.nodes = n;
	g.ajd_list.reserve(n);
	g.visited.resize(n, false);
	g.parents.resize(n);
}

void add_edge(Graph &g, int u, int v){
	g.ajd_list[u].push_back(v);
	g.ajd_list[v].push_back(u);
}

bool BFS(Graph &g, int u){
	std::queue<int> nodes;
	g.visited[u] = true;
	nodes.push(u);

	int tmp;

	while(!nodes.empty()){
		tmp = nodes.front();
		nodes.pop();

		auto begin = g.ajd_list[tmp].begin();
		auto end = g.ajd_list[tmp].end();


		while(begin != end){
			if(!g.visited[*begin]){
				g.visited[*begin] = true;
				g.parents[*begin] = tmp;
				nodes.push(*begin);
			}
			else if(g.parents[tmp] != *begin){
				return true;
			}
			begin++;
		}
	}

	return false;
}

int main(int argc, char** argv){

	Graph g;
	init_graph(g, 7);

	add_edge(g, 0, 1);
	add_edge(g, 0, 2);
	add_edge(g, 1, 2);
	add_edge(g, 1, 3);
	add_edge(g, 1, 6);
	add_edge(g, 3, 4);
	add_edge(g, 4, 4);
	add_edge(g, 4, 2);
	add_edge(g, 5, 0);
	add_edge(g, 5, 6);
	
	std::cout << std::boolalpha << BFS(g, 0) << std::endl;

	exit(EXIT_SUCCESS);
}