#include <iostream>
#include <vector>

class Graph{
    public:
        Graph(int v){
            this->v = v;
            adjacency_list.resize(v);
            visited.resize(v);
            std::fill(visited.begin(), visited.end(), false);
        }

        void add_edge(int u, int v){
            adjacency_list[u].push_back(v);
        }

        void dfs(int u, int v){
            
        }

    private:
        std::vector<std::vector<int>> adjacency_list;
        std::vector<bool> visited;
        int v;
}