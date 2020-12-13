#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <queue>

struct Node {

    Node(){
        word = "";
        count = 0;
    }

    std::string word;
    int count;

    std::unordered_map<char, Node*> nodes;
};

void add_word(Node *root, std::string &s, int i){
    if(i == s.size()){
        root->word = s;
        root->count++;
        return;
    }

    auto iterator = root->nodes.find(s[i]);

    if(iterator == root->nodes.end()){
        root->nodes[s[i]] = new Node();
    }

    add_word(root->nodes[s[i]], s, i + 1);
}

struct comparator{
    bool operator()(Node *n1, Node *n2){
        return n1->count < n2->count;
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

    std::vector<std::string> words = {"code", "coder", "coding", "codable", "codec", "codecs", "coded",
		"codeless", "codec", "codecs", "codependence", "codex", "codify",
		"codependents", "codes", "code", "coder", "codesign", "codec",
		"codeveloper", "codrive", "codec", "codecs", "codiscovered"};

    std::cout << "Input k: "; int k; std::cin >> k;

    Node *root = new Node();
    for(std::string &s : words){
        add_word(root, s, 0);
    }

    std::priority_queue<Node*, std::vector<Node*>, comparator> heap;

    add_to_heap(root, heap);

    while(k-- && heap.size()){
        Node *tmp = heap.top(); heap.pop();
        std::cout << tmp->word << " occurs " << tmp->count << " times" << std::endl;
    }

    exit(EXIT_SUCCESS);
}