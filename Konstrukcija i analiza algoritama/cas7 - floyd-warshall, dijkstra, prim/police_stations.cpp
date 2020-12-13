#include <iostream>
#include <vector>
#include <queue>
#include <climits>

struct Graph {
	int size;
	std::vector<std::vector<int>> ajd_list;
	std::vector<bool> visited;
	std::vector<int> distances;
	std::vector<int> police_stations;
	std::priority_queue<std::pair<int, int>> nodes;
};

void init_graph(Graph &g, int n){
	g.size = n;
	g.ajd_list.reserve(n);
	g.visited.resize(n, false);
	g.distances.resize(n, INT_MAX);
}

void add_edge(Graph &g, int u, int v){
	g.ajd_list[u].push_back(v);
	g.ajd_list[v].push_back(u);
}

void add_police_station(Graph &g, int u){
	g.police_stations.push_back(u);
	g.distances[u] = 0;
	g.nodes.push(std::make_pair(u, g.distances[u]));
}

void dijkstra(Graph &g){

	std::pair<int, int> tmp;
	while(!g.nodes.empty()){

		tmp = g.nodes.top();
		g.nodes.pop();

		if(g.visited[tmp.first]){
			continue;
		}

		g.visited[tmp.first] = true;

		for(auto &x : g.ajd_list[tmp.first]){
			if(g.distances[x] > g.distances[tmp.first] + 1){
				g.distances[x] = g.distances[tmp.first] + 1;
				g.nodes.push(std::make_pair(x, g.distances[x]));
			}
		}

	}
}

int main(int argc, char** argv){

	Graph g;
	init_graph(g, 6);

	add_edge(g, 0, 1);
	add_edge(g, 0, 5);
	add_edge(g, 1, 5);
	add_edge(g, 1, 2);
	add_edge(g, 5, 2);
	add_edge(g, 2, 4);
	add_edge(g, 2, 3);
	add_edge(g, 3, 4);

	add_police_station(g, 0);
	//add_police_station(g, 4);

	dijkstra(g);

	for(int i = 0; i < g.size; i++){
		std::cout << i << ": " << g.distances[i] << std::endl;
	}

	exit(EXIT_SUCCESS);
}