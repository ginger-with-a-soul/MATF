#include <iostream>
#include <vector>
#include <queue>
#include <stack>

struct Graph {
	int size;
	std::vector<std::vector<int>> ajd_list;
	std::vector<bool> visited;
	std::stack<int> path;
	std::queue<int> queue;
	std::vector<int> parents;
};

void init_graph(Graph &g, int n){
	g.size = n;
	g.ajd_list.reserve(n);
	g.visited.resize(n, false);
	g.parents.resize(n, -1);
}

void add_edge(Graph &g, int u, int v){
	g.ajd_list[u].push_back(v);
	g.ajd_list[v].push_back(u);
}

void BFS(Graph &g, int u, int v){

	g.visited[u] = true;
	g.queue.push(u);
	int tmp;

	while(!g.queue.empty()){
		tmp = g.queue.front();
		g.queue.pop();

		if(tmp == v){
			break;
		}

		auto begin = g.ajd_list[tmp].begin();
		auto end = g.ajd_list[tmp].end();

		while(begin != end){
			if(!g.visited[*begin]){
				g.queue.push(*begin);
				g.parents[*begin] = tmp;
				g.visited[*begin] = true;
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
	std::cout << std::endl;
}

int main(int argc, char** argv){

	Graph g;
	init_graph(g, 7);

	add_edge(g, 0, 1);
	add_edge(g, 0, 3);
	add_edge(g, 1, 2);
	add_edge(g, 2, 3);
	add_edge(g, 3, 4);
	add_edge(g, 3, 6);
	add_edge(g, 4, 5);
	add_edge(g, 5, 6);
	add_edge(g, 0, 4);

	int u, v; std::cin >> u >> v;

	BFS(g, u, v);

	exit(EXIT_SUCCESS);
}