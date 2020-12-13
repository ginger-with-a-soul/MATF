#include <iostream>
#include <vector>
#include <queue>
#include <stack>

class Graph {
    public:

        Graph(int v){
            this->v = v;
            adjacency_list.resize(v);
            parents.resize(v);
            std::fill(parents.begin(), parents.end(), -1);
            visited.resize(v);
            std::fill(visited.begin(), visited.end(), false);
        }

        void add_edge(int u, int v){

            adjacency_list[u].push_back(v);
            adjacency_list[v].push_back(u);

        }

        void bfs(int u, int v){

            std::queue<int> red;
            red.push(u);
            visited[u] = true;
            int tmp;

            while(!red.empty()){
                tmp = red.front();
                red.pop();
                if(tmp == v){
                    return;
                }

                auto begin = adjacency_list[tmp].begin();
                auto end = adjacency_list[tmp].end();

                while(begin != end){
                    if(!visited[*begin]){
                        visited[*begin] = true;
                        red.push(*begin);
                        parents[*begin] = tmp;
                    }
                    begin++;
                }
            }
        }

        void shortest_path(int u, int v){

            std::stack<int> path;

            bfs(u, v);

            if(parents[v] == -1){
                std::cout << "Nema puta od u do v" << std::endl;
                return;
            }

            path.push(v);

            while(parents[v] != -1){
                v = parents[v];
                path.push(v);
            }

            int n = path.size();

            while(n){
                int x = path.top();
                path.pop();
                if(n > 1){
                    std::cout << x << "-->";
                }
                else{
                    std::cout << x << std::endl;
                }
                n--;
            }
        }

    private:

        int v;
        std::vector<int> parents;
        std::vector<std::vector<int>> adjacency_list;
        std::vector<bool> visited;
};

int main(){
    Graph g(8);

    g.add_edge(0, 1);
    g.add_edge(0, 3);
    g.add_edge(1, 2);
    g.add_edge(3, 4);
    g.add_edge(3, 7);
    g.add_edge(4, 5);
    g.add_edge(4, 6);
    g.add_edge(4, 7);
    g.add_edge(5, 6);
    g.add_edge(6, 7);

    int u, v; std::cin >> u >> v;

    g.shortest_path(u, v);

    std::cout << std::endl;

    exit(EXIT_SUCCESS);
}