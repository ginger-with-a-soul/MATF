#include <iostream>
#include <vector>
#include <queue>

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
            adjacency_list[v].push_back(u);
        }

        void bfs(int root){
            std::queue<int> queue;
            queue.push(root);
            visited[root] = true;
            int tmp = queue.front();

            while(!queue.empty()){
                tmp = queue.front();
                std::cout << tmp << " ";
                
                queue.pop();

                auto begin = adjacency_list[tmp].begin();
                auto end = adjacency_list[tmp].end();

                while(begin != end){
                    if(!visited[*begin]){
                        visited[*begin] = true;
                        queue.push(*begin);
                    }
                    begin++;
                }
            }
            std::cout << std::endl;
            for(int i = 0; i < 8; i++){
                if(!visited[i]){
                    std::cout << "Graf nije povezan" << std::endl;
                }
            }
        }

    private:
        int v;
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

    g.bfs(0);


    exit(EXIT_SUCCESS);
}