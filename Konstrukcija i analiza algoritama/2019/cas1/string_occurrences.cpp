#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <queue>

void first_k_nonrepeating(std::string niska, int k){
    std::map <char, int> mapa;

    for(char x : niska){
        mapa[x]++;
    }

    std::queue <char> heap;

    for(auto it : mapa){
        if(it.second == 1){
            heap.push(it.first);
        }
    }

    while(k-- && !heap.empty()){
        std::cout << heap.front() << " ";
        heap.pop();
    }

    std::cout << std::endl;
}

int main(){
    int k;
    std::cin >> k;
    std::string niska;
    std::cin >> niska;

    first_k_nonrepeating(niska, k);

    exit(EXIT_SUCCESS);
}