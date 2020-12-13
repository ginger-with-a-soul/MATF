#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <algorithm>
#include <stack>

struct Graph {
	int size;
	std::vector<std::vector<std::pair<int, int>>> adj_list;
	std::vector<bool> visited;
	std::vector<int> distances;
	std::vector<int> parents;
	std::stack<int> path;
};

void init_graph(Graph &g, int n){
	g.size = n;
	g.adj_list.reserve(n);
	g.distances.resize(n, INT_MAX);
	g.parents.resize(n, -1);
	g.visited.resize(n, false);
}

void add_edge(Graph &g, int u, int v, int d){
	g.adj_list[u].push_back(std::make_pair(v, d));
	g.adj_list[v].push_back(std::make_pair(u, d));
}

struct comp {
	bool operator() (const std::pair<int, int> &x, const std::pair<int, int> &y){
		return x.second > y.second;
	}
};

void dijkstra(Graph &g, int u, int v){
	std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, comp> nodes;
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
			if(g.distances[x.first] > g.distances[tmp.first] + x.second){
				g.distances[x.first] = g.distances[tmp.first] + x.second;
				g.parents[x.first] = tmp.first;
				nodes.push(std::make_pair(x.first, g.distances[x.first]));
			}
		}
	}

	std::cout << g.distances[v] << std::endl;
	while(g.parents[v] != -1){
		g.path.push(v);
		v = g.parents[v];
	}

	g.path.push(u);

	while(!g.path.empty()){
		std::cout << g.path.top() << " ";
		g.path.pop();
	}

	std::cout << std::endl;
	
}

int main(int argc, char** argv){

	Graph g;
	init_graph(g, 5);

	add_edge(g, 0, 4, 99);
	add_edge(g, 0, 1, 1);
	add_edge(g, 1, 2, 10);
	add_edge(g, 2, 3, 20);
	add_edge(g, 3, 4, 20);

	dijkstra(g, 0, 4);

	exit(EXIT_SUCCESS);
}