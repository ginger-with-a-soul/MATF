#include <iostream>
#include <vector>

class Graph{
    public:

        Graph(int v){
            this->v = v;
            visited.resize(v);
            std::fill(visited.begin(), visited.end(), false);
            adjacency_list.resize(v);
        }

        void add_edge(int u, int v){
            adjacency_list[u].push_back(v);
        }

        void dfs(int u){
            visited[u] = true;

            std::cout << u << " "; 

            auto begin = adjacency_list[u].begin();
            auto end = adjacency_list[u].end();

            while(begin != end){
                if(!visited[*begin]){
                    dfs(*begin);
                }
                begin++;
            }
        }

    private:

        std::vector<std::vector<int>> adjacency_list;
        int v;
        std::vector<bool> visited;

};

int main(){
    
    int v, x; std::cin >> v >> x;
    Graph g(v);
    g.add_edge(0, 1);
    g.add_edge(0, 2);
    g.add_edge(1, 2);
    g.add_edge(2, 0);
    g.add_edge(2, 3);
    g.add_edge(3, 3);

    g.dfs(x); std::cout << std::endl;

    exit(EXIT_SUCCESS);
}