#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <unordered_map>

struct Node {

    Node(){
        word = "";
        counter = 0;
    }

    std::string word;
    int counter;
    std::unordered_map<char, Node*> nodes;
};

void add_word(Node *root, std::string &word, int i){
    if(i == word.size()){
        root->word = word;
        root->counter++;
        return;
    }

    auto iterator = root->nodes.find(word[i]);

    if(iterator == root->nodes.end()){
        root->nodes[word[i]] = new Node();
    }

    add_word(root->nodes[word[i]], word, i + 1);
}

struct compare {
    bool operator()(Node *n1, Node *n2){
        return n1->counter < n2->counter;
    }
};

void add_to_heap(Node *root, auto &heap){
    if(root->word != ""){
        heap.push(root);
    }

    auto begin = root->nodes.begin();
    auto end = root->nodes.end();

    while(begin != end){
        add_to_heap(begin->second, heap);
        begin++;
    }
}


int main(){
    std::vector<std::string> dictionary = {"code", "coder", "coding", "codable", "codec", "codecs", "coded",
		"codeless", "codec", "codecs", "codependence", "codex", "codify",
		"codependents", "codes", "code", "coder", "codesign", "codec",
		"codeveloper", "codrive", "codec", "codecs", "codiscovered"};

        Node *root = new Node();
    
    for(std::string &word : dictionary){
        add_word(root, word, 0);
    }

    std::priority_queue<Node*, std::vector<Node*>, compare> heap;

    add_to_heap(root, heap);

    std::cout << heap.top()->word << " occurs " << heap.top()->counter << " times" << std::endl;

    exit(EXIT_SUCCESS);
}