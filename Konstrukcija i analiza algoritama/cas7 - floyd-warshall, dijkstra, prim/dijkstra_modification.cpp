#include <iostream>
#include <queue>
#include <vector>
#include <climits>

struct Graph {
	int size;
	std::vector<std::vector<std::pair<int, int>>> ajd_list;
	std::vector<bool> visited;
	std::vector<int> distances;
	std::vector<int> parents;
	std::vector<int> shortest_path;
};

void init_graph(Graph &g, int n){
	g.size = n;
	g.distances.resize(n, INT_MAX);
	g.ajd_list.reserve(n);
	g.visited.resize(n, false);
	g.shortest_path.resize(n, INT_MAX);
	g.parents.resize(n, -1);
}

void add_edge(Graph &g, int u, int v, int d){
	g.ajd_list[u].push_back(std::make_pair(v, d));
	g.ajd_list[v].push_back(std::make_pair(u, d));
}

struct comp {
	bool operator() (std::pair<int, int> x, std::pair<int, int> y){
		return x.second > y.second;
	}
};

void dijkstra(Graph &g, int u, int v){

	std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, comp> nodes;
	g.distances[u] = 0;
	g.shortest_path[u] = 0;

	std::pair<int, int> tmp = std::make_pair(u, g.distances[u]);
	nodes.push(tmp);

	while(!nodes.empty()){
		tmp = nodes.top();
		nodes.pop();

		if(g.visited[tmp.first]){
			continue;
		}

		g.visited[tmp.first] = true;

		for(auto &x : g.ajd_list[tmp.first]){
			if(g.distances[x.first] >= g.distances[tmp.first] + x.second && g.shortest_path[x.first] > g.shortest_path[tmp.first] + 1){
				g.distances[x.first] = g.distances[tmp.first] + x.second;
				g.shortest_path[x.first] = g.shortest_path[tmp.first] + 1;
				g.parents[x.first] = tmp.first;
				nodes.push(std::make_pair(x.first, g.distances[x.first]));
			}
		}
	}

	std::vector<int> path;

	while(g.parents[v] != -1){
		path.push_back(v);
		v = g.parents[v];
	}
	path.push_back(u);

	auto rbegin = path.rbegin();
	auto rend = path.rend();
	while(rbegin != rend){
		std::cout << *rbegin << " ";
		rbegin++;
	}
	std::cout << std::endl;

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

	dijkstra(g, 0, 8);

	exit(EXIT_SUCCESS);
}