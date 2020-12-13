#include <iostream>
#include <vector>
#include <queue>

class Graph{
    public:
        Graph(int v){
            this->v = v;
            adjacency_list.resize(v);
            in_degree.resize(v);
            std::fill(in_degree.begin(), in_degree.end(), 0);
			visited.resize(v);
			std::fill(visited.begin(), visited.end(), false);
        }

        void add_edge(int u, int v){
            adjacency_list[u].push_back(v);
            in_degree[v]++;
        }

		void dfs(int u){
			if(visited[u]){
				found_cycle = true;
				std::cout << u << std::endl;
				return;
			}

			std::cout << u << "->";

			visited[u] = true;

			auto begin = adjacency_list[u].begin();
			auto end = adjacency_list[u].end();

			while(begin != end){
				if(!found_cycle){
					dfs(*begin);
				}
				begin++;
			}
		}

        void ciclus_finder(){

            std::queue<int> queue;
			std::queue<int> topological_order;

            for(int i = 0; i < v; i++){
                if(!in_degree[i]){
                    queue.push(i);
					topological_order.push(i);
                }
            }

            int tmp;
            while(!queue.empty()){
				tmp = queue.front();
				queue.pop();
				auto begin = adjacency_list[tmp].begin();
				auto end = adjacency_list[tmp].end();
				while(begin != end){
					in_degree[*begin]--;
					if(!in_degree[*begin]){
						queue.push(*begin);
						topological_order.push(*begin);
					}
					begin++;
				}
            }

			for(int i = 0; i < v; i++){
				if(in_degree[i]){
					dfs(i);
					return;
				}
			}
			std::cout << "Topolosko uredjenje je:\n";
			while(!topological_order.empty()){
				std::cout << topological_order.front() << "->";
				topological_order.pop();
			}
			std::cout << "\n";
        }
    private:
        int v;
        std::vector<std::vector<int>> adjacency_list;
        std::vector<int> in_degree;
		std::vector<bool> visited;
		bool found_cycle;
};

int main(){

    Graph g(6);

    g.add_edge(0, 1);
	g.add_edge(1, 3);
    g.add_edge(1, 4);
    g.add_edge(2, 4);
    g.add_edge(3, 0);
    g.add_edge(3, 2);
    g.add_edge(5, 2);
    g.add_edge(5, 4);
	

    g.ciclus_finder();

    exit(EXIT_SUCCESS);
}