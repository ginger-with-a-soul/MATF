#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <climits>

struct Graph {
	int size;
	std::vector<std::vector<std::pair<int, int>>> adj_list;
	std::vector<bool> visited;
	std::vector<int> distances;
	int result;
};

void init_graph(Graph &g, int n){
	g.size = n;
	g.adj_list.reserve(n);
	g.distances.resize(n, INT_MAX);
	g.result = 0;
	g.visited.resize(n, false);
}

void add_edge(Graph &g, int u, int v, int d){
	g.adj_list[u].push_back(std::make_pair(v, d));
	g.adj_list[v].push_back(std::make_pair(u, d));
}

void dijkstra(Graph &g, int u, int v, int avoid){
	std::priority_queue<std::pair<int, int>> nodes;
	g.distances[u] = 0;
	std::pair<int, int> tmp = std::make_pair(u, g.distances[u]);
	
	nodes.push(tmp);

	while(!nodes.empty()){
		tmp = nodes.top();
		nodes.pop();

		if(g.visited[tmp.first]){
			continue;
		}
		g.visited[tmp.first] = true;

		for(auto &x : g.adj_list[tmp.first]){
			if(x.first == avoid){
				continue;
			}

			if(g.distances[x.first] > g.distances[tmp.first] + x.second){
				g.distances[x.first] = g.distances[tmp.first] + x.second;
				nodes.push(std::make_pair(x.first, g.distances[x.first]));
			}
		}
	}
	g.result += g.distances[v];
}

void through_node(Graph &g, int u, int v, int through){
	dijkstra(g, u, through, -1);
	g.distances.clear();
	g.distances.resize(g.size, INT_MAX);
	g.visited.clear();
	g.visited.resize(g.size, false);
	dijkstra(g, through, v, -1);
}

void avoid_node(Graph &g, int u, int v, int avoid){
	dijkstra(g, u, v, avoid);
}

int main(int argc, char** argv){

	Graph g;
	init_graph(g, 5);

	add_edge(g, 0, 1, 10);
	add_edge(g, 0, 2, 2);
	add_edge(g, 2, 4, 5);
	add_edge(g, 2, 3, 7);
	add_edge(g, 4, 3, 6);
	add_edge(g, 1, 3, 9);

	through_node(g, 0, 3, 4);
	// avoid_node(g, 0, 3, 2);

	std::cout << g.result << std::endl;

	exit(EXIT_SUCCESS);
}