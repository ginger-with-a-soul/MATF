#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <unordered_map>

struct Node{

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

    add_word(root->nodes[word[i]], word, i+1);
}

void find(Node *root){
    std::string back = "";

    while(root && !root->isWord && root->nodes.size() == 1){
        auto iterator = root->nodes.begin();
        back += iterator->first;
        root = iterator->second;
    }
    std::cout << back;
}


int main(){

    std::vector<std::string> dictionary = {"code", "coder", "coding", "codable", "codec", "codecs", "coded",
		"codeless", "codec", "codecs", "codependence", "codex", "codify",
		"codependents", "codes", "code", "coder", "codesign", "codec",
		"codeveloper", "codrive", "codec", "codecs", "codiscovered", "dimi"};

    Node *root = new Node();

    for(std::string &word : dictionary){
        add_word(root, word, 0);
    }

    find(root);

    std::cout << " is the longest common prefix" << std::endl;

    exit(EXIT_SUCCESS);
}