#include <iostream>
#include <vector>

#define MAX 128

struct Node {

    Node () {
        isLeaf = false;
        for(int i = 0; i < MAX; i++){
            nodes[i] = nullptr;
        }
    }

    bool isLeaf;
    Node* nodes[MAX];

};

void add_word(Node* root, std::string &word){
    for(int i = 0; i < word.length(); i++){
        if(root->nodes[word[i]] == nullptr){
            root->nodes[word[i]] = new Node();
        }

        root = root->nodes[word[i]];
    }

    root->isLeaf = true;
}

bool find_word(Node* root, std::string &word){
    if(root == nullptr){
        return false;
    }
    
    for(int i = 0; i < word.length(); i++){
        root = root->nodes[word[i]];
        if(root == nullptr){
            return false;
        }
    }
    
    return root->isLeaf;
}

int main(){
    std::cout << "Unesi broj reci a zatim te reci: ";
    int n;
    std::cin >> n;
    Node* root = new Node();
    std::string s;
    for(int i = 0; i < n; i++){
        std::cin >> s;
        add_word(root, s);
    }

    std::cout << "Rec za koju zelite da proverite da li postoji u stablu: " << std::endl;
    std::cin >> s;
    std::cout << std::boolalpha << find_word(root, s) << std::endl;
}