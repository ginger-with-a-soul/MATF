#include <iostream>
#include <vector>
#include <queue>

struct Graph {
	std::vector<std::vector<int>> ajd_list;
	int size;
	std::vector<bool> visited;
	std::vector<bool> colors;
};

void init_graph(Graph &g, int n){
	g.size = n;
	g.ajd_list.reserve(n);
	g.visited.resize(n, false);
	g.colors.resize(n);
}

void add_edge(Graph &g, int u, int v){
	g.ajd_list[u].push_back(v);
	g.ajd_list[v].push_back(u);
}

bool BFS(Graph &g, int u){
	g.visited[u] = true;
	std::queue<int> nodes;
	nodes.push(u);
	

	int tmp;
	bool color = true;
	g.colors[u] = color;

	while(!nodes.empty()){
		tmp = nodes.front();
		nodes.pop();

		auto begin = g.ajd_list[tmp].begin();
		auto end = g.ajd_list[tmp].end();

		while(begin != end){
			if(!g.visited[*begin]){
				g.visited[*begin] = true;
				g.colors[*begin] = !g.colors[tmp];
				nodes.push(*begin);
			}
			else if(g.colors[tmp] == g.colors[*begin]){
				std::cout << tmp << " " << *begin << std::endl;
				return false;
			}
			begin++;
		}
	}
	return true;
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


	std::cout << std::boolalpha << BFS(g, 0) << std::endl;

	exit(EXIT_SUCCESS);
}