#include <iostream>
#include <vector>
#include <queue>

class Graph{
    public:
        Graph(int v){
            this->v = v;
            adjacency_list.resize(v);
            visited.resize(v);
            in_degree.resize(v);
            std::fill(in_degree.begin(), in_degree.end(), 0);
            std::fill(visited.begin(), visited.end(), false);
        }

        void add_edge(int u, int v){
            adjacency_list[u].push_back(v);
            in_degree[v]++;
        }

        void topological(){
            std::queue<int> queue;
            for(int i = 0; i < v; i++){
                if(!in_degree[i]){
                    queue.push(i);
                }
            }

            int tmp;

            while(!queue.empty()){
                tmp = queue.front();
                queue.pop();
                std::cout << tmp << " ";
                for(int node : adjacency_list[tmp]){
                    in_degree[node]--;
                    if(!in_degree[node]){
                        queue.push(node);
                    }
                }
            }
        }
    private:
        std::vector<std::vector<int>> adjacency_list;
        std::vector<int> in_degree;
        std::vector<bool> visited;
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

    g.topological();
    std::cout << std::endl;

    exit(EXIT_SUCCESS);
}