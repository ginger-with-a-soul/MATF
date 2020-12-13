#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <climits>

struct Graph {
	int size;
	std::vector<std::vector<std::pair<int, int>>> adj_list;
	std::vector<bool> visited;
	std::vector<int> parents;
	std::priority_queue<std::pair<int, int>> nodes;
	std::vector<int> sh_path;
	std::vector<int> distances;
	std::stack<int> path;
};

void init_graph(Graph &g, int n){
	g.size = n;
	g.parents.resize(n, -1);
	g.adj_list.reserve(n);
	g.distances.resize(n, INT_MAX);
	g.visited.resize(n, false);
	g.sh_path.resize(n, INT_MAX);
}

void add_edge(Graph &g, int u, int v, int d){
	g.adj_list[u].push_back(std::make_pair(v, d));
	g.adj_list[v].push_back(std::make_pair(u, d));
}

void dijkstra(Graph &g, int u, int v){
	g.distances[u] = 0;
	g.sh_path[u] = 0;
	std::pair<int, int> tmp = std::make_pair(u, g.distances[u]);

	g.nodes.push(tmp);

	while(!g.nodes.empty()){
		tmp = g.nodes.top();
		g.nodes.pop();

		if(g.visited[tmp.first]){
			continue;
		}

		g.visited[tmp.first] = true;

		auto begin = g.adj_list[tmp.first].begin();
		auto end = g.adj_list[tmp.first].end();

		while(begin != end){
			if(g.distances[(*begin).first] >= g.distances[tmp.first] + (*begin).second && g.sh_path[(*begin).first] > g.sh_path[tmp.first] + 1){
				g.distances[(*begin).first] = g.distances[tmp.first] + (*begin).second;
				g.sh_path[(*begin).first] = g.sh_path[tmp.first] + 1;
				g.parents[(*begin).first] = tmp.first;
				g.nodes.push(std::make_pair((*begin).first, g.distances[(*begin).first]));
			}
			begin++;
		}
	}

	while(g.parents[v] != -1){
		g.path.push(v);
		v = g.parents[v];
	}

	g.path.push(u);

	while(!g.path.empty()){
		std::cout << g.path.top() << " ";
		g.path.pop();
	}

	std::cout << std::endl << "Shortest path: " << g.sh_path[v] << std::endl;

}

int main(int argc, char** argv){

	Graph g;
	init_graph(g, 9);

	add_edge(g, 0, 1, 4);
  	add_edge(g, 0, 7, 8);
  	add_edge(g, 1, 7, 11);
  	add_edge(g, 1, 2, 8);
  	add_edge(g, 2, 8, 3);
  	add_edge(g, 2, 3, 7);
  	add_edge(g, 7, 8, 7);
  	add_edge(g, 7, 6, 1);
  	add_edge(g, 8, 6, 6);
  	add_edge(g, 2, 5, 4);
  	add_edge(g, 6, 5, 2);
  	add_edge(g, 3, 5, 14);
  	add_edge(g, 3, 4, 9);
  	add_edge(g, 4, 5, 10);

	dijkstra(g, 0, 5);

	exit(EXIT_SUCCESS);
}