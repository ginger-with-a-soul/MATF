#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <unordered_map>

struct Node {

    Node(){
        isWord = false;
    }

    bool isWord;
    std::unordered_map<char, Node *> nodes;
};

void add_word(Node *root, std::string &word, int i){
    if(i == word.size()){
        root->isWord = true;
        return;
    }

    auto iterator = root->nodes.find(word[i]);

    if(iterator == root->nodes.end()){
        root->nodes[word[i]] = new Node();
    }

    add_word(root->nodes[word[i]], word, i + 1);
}

bool solver(auto root, std::string &needle){
    int n = needle.size();
    std::vector<bool> valid(n);

    valid[0] = true;
    Node *tmp;

    for(int i = 0; i < n; i++){
        if(valid[i]){
            tmp = root;
            for(int j = i; j < n; j++){
                auto finder = tmp->nodes.find(needle[j]);
                if(finder == tmp->nodes.end()){
                    break;
                }
                tmp = tmp->nodes[needle[j]];
                if(tmp->isWord){
                    valid[j + 1] = true;
                }
                if(j == n-1){
                    return true;
                }
            }
        }
    }
    return false;
}

int main(){

    std::cout << "Input your word: "; std::string needle; std::cin >> needle;
    std::vector<std::string> haystack = { "this", "th", "is", "famous", "word", "break", "b", "r", "e", "a", "k", "br", "bre", "brea", "ak", "prob", "lem" };
    
    Node *root = new Node();

    for(std::string &word : haystack){
        add_word(root, word, 0);
    }

    if(solver(root, needle)){
        std::cout << needle << " can be assembled" << std::endl;
    }
    else{
        std::cout << needle << " can't be assembled" << std::endl;
    }

    exit(EXIT_SUCCESS);
}