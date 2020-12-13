#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>
#include <numeric>

struct Graph {
  std::vector<std::vector<int>> adjacency_list;
  std::vector<int> parents;
  std::vector<std::vector<int>> capacities;
};

void initialize_graph(Graph &g, const std::vector<std::vector<int>> &adjacency_list, const std::vector<int> &parents, const std::vector<std::vector<int>> &capacities)
{
  g.adjacency_list = adjacency_list;
  g.parents = parents;
  g.capacities = capacities;
}

void add_edge(Graph &g, int u, int v, int capacity)
{
  g.adjacency_list[u].push_back(v);
  g.adjacency_list[v].push_back(u);
  g.capacities[u][v] = capacity;
}

int DFS(Graph &g, int start_node, int end_node)
{
  int ret = 0;

  std::fill(g.parents.begin(),g.parents.end(), -1);
  
  std::stack<int> dfs_stek;

  std::stack<int> min_capacity;

  dfs_stek.push(start_node);

  min_capacity.push(std::numeric_limits<int>::max());

  int current_node, neighbor_node, capacity, n;

  while (!dfs_stek.empty()) {
  	current_node = dfs_stek.top();
    capacity = min_capacity.top();    
    
    dfs_stek.pop();
    min_capacity.pop();
    
    if (current_node == end_node) {
  	  ret = capacity;
      break;
    }

    n = g.adjacency_list[current_node].size();
    for (int i = 0; i < n; i++) {
      neighbor_node = g.adjacency_list[current_node][i];

      if (g.capacities[current_node][neighbor_node] > 0 && g.parents[neighbor_node] == -1) {
        dfs_stek.push(neighbor_node);
        min_capacity.push(std::min(capacity, g.capacities[current_node][neighbor_node]));
        g.parents[neighbor_node] = current_node;
      }
    }
  }

  if (ret > 0) {
    current_node = end_node;
    
    while (current_node != start_node) {
      g.capacities[g.parents[current_node]][current_node] -= ret;
      g.capacities[current_node][g.parents[current_node]] += ret;
      current_node = g.parents[current_node];
    }
  }

  return ret;
}

int ford_fulkerson(Graph &g, int start_node, int end_node)
{
  int max_flow = 0, current_flow;

  while (true) {
    current_flow = DFS(g, start_node, end_node);

    if (current_flow == 0) 
    	break;
    max_flow += current_flow;
  }

    return max_flow;
}

int main()
{
  int n, m;
  std::vector<std::vector<int>> adjacency_list;
  std::vector<int> parents;
  std::vector<std::vector<int>> capacities;

  std::cin >> n >> m;

  adjacency_list.resize(n);

  parents.resize(n, -1);

  capacities.resize(n);

  for (auto &v : capacities)
  	v.resize(n, 0);

  Graph g;

  initialize_graph(g, adjacency_list, parents, capacities);

  int x, y;

  for (int i = 0; i < m; i++) {
    std::cin >> x >> y;
    add_edge(g, x, y, 1);
  }

  std::cin >> x >> y;

  std::cout << ford_fulkerson(g, x, y) << "\n";

  return 0;
}