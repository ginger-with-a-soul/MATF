#include <iostream>
#include <queue>
#include <vector>

class Graph {
    public:
        Graph(int v){
            this->v = v;
            ajd_list.resize(v);
            visited.resize(v);
            in_degree.resize(v);
            std::fill(visited.begin(), visited.end(), false);
            std::fill(in_degree.begin(), in_degree.end(), 0);
        }

        void add_edge(int u, int v){
            ajd_list[u].push_back(v);
            in_degree[v]++;
        }

        void topological_sorting(){
            std::queue<int> nodes;
            
            for(int i = 0; i < v; i++){
                if(!in_degree[i]){
                    nodes.push(i);
                }
            }

            while(!nodes.empty()){
                int tmp = nodes.front();
                nodes.pop();

                std::cout << tmp << "->";

                for(auto node : ajd_list[tmp]){
                    in_degree[node]--;
                    if(!in_degree[node]){
                        nodes.push(node);
                    }
                }
            }
        }
    private:
        std::vector<std::vector<int>> ajd_list;
        std::vector<bool> visited;
        std::vector<int> in_degree;
        int v;
};

int main(){
    Graph g(6);

    g.add_edge(0, 1);
    g.add_edge(1, 4);
    g.add_edge(2, 4);
    g.add_edge(3, 0);
    g.add_edge(3, 2);
    g.add_edge(5, 2);
    g.add_edge(5, 4);

    g.topological_sorting();

    exit(EXIT_SUCCESS);
}