#include <iostream>
#include <vector>
#include <stack>
#include <queue>

struct Graph {
	int size;
	std::vector<std::vector<int>> adj_list;
	std::vector<bool> visited;
	std::stack<int> path;
	std::queue<int> queue;
	std::vector<int> parents;
};

void init_graph(Graph &g, int n){
	g.size = n;
	g.adj_list.reserve(n);
	g.visited.resize(n, false);
	g.parents.resize(n, -1);
}

void add_edge(Graph &g, int u, int v){
	g.adj_list[u].push_back(v);
	g.adj_list[v].push_back(u);
}

void BFS(Graph &g, int u, int v){
	g.queue.push(u);
	g.visited[u] = true;

	while(!g.queue.empty()){
		int tmp = g.queue.front();
		g.queue.pop();

		if(tmp == v){
			break;
		}

		auto begin = g.adj_list[tmp].begin();
		auto end = g.adj_list[tmp].end();

		while(begin != end){
			if(!g.visited[*begin]){
				g.visited[*begin] = true;
				g.parents[*begin] = tmp;
				g.queue.push(*begin);
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
	add_edge(g, 0, 2);
	add_edge(g, 1, 2);
	add_edge(g, 1, 3);
	add_edge(g, 3, 5);
	add_edge(g, 4, 4);
	add_edge(g, 4, 2);
	add_edge(g, 4, 5);
	add_edge(g, 5, 0);
	add_edge(g, 5, 6);
	add_edge(g, 6, 2);

	int u, v;
	std::cin >> u >> v;

	BFS(g, u, v);


	exit(EXIT_SUCCESS);
}