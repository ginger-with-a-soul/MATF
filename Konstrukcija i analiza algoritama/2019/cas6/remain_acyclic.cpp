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
            std::fill(visite.begin(), visited.end(), false);
        }

        void add_edge(int u, int v){
            adjacency_list[u].push_back(v);
            in_degree[v]++;
            std::pair<int, int> p(u, v);
            edges.push_back(p);
        }

        void topological(){
            std::queue<int> queue;
            std::vector<int> topological;
            for(int i = 0; i < v; i++){
                if(!in_degree[i]){
                    queue.push(i);
                    topological.push_back(i);
                }
            }

            int tmp;

            while(!queue.empty()){
                tmp = queue.front();
                queue.pop();
                for(int node : adjacency_list[tmp]){
                    in_degree[node]--;
                    if(!in_degree[node]){
                        queue.push(node);
                        topological.push_back(node);
                    }
                }
            }
        }

        bool dfs(int u){
            visited[u] = true;

            auto begin = adjacency_list[u].begin();
            auto end = adjacency_list[u].end();

            while(begin != end){
                if(visited[*begin]){
                    return true;
                }
                else if(dfs(*begin)){
                    return true;
                }
                begin++;
            }

            visited[u] = false;

            return false;
        }

        void add_edges(){
            topological();

            for(int i = 0; i < v; i++){
                for(int y : adjacency_list[topological[i]]){
                    visited[y] = true;
                }
            }
        }
    private:
        std::vector<std::vector<int>> adjacency_list;
        std::vector<bool> visited;
        int v;
        std::vector<int> in_degree;
        std::vector<std::pair<int, int>> edges;
        std::vector<std::pari<int, int>> added_edges;
};