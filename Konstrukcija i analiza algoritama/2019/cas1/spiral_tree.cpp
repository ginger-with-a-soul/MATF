#include <iostream>
#include <vector>
#include <list>

struct Node {
    Node () {
        left = right = nullptr;
    }
    int key;
    Node* left;
    Node* right;
};

void free_tree(Node *root){
    if(root == nullptr){
        return;
    }

    free_tree(root->left);
    free_tree(root->right);

    delete root;
}

void spiral(Node *root, bool leftToRight){
    std::list <Node*> nodes;
    nodes.push_back(root);

    

    while(nodes.size()){
        leftToRight = !leftToRight;
        int n = nodes.size();
        while(n--){
            if(leftToRight){
                Node* tmp = nodes.front();
                nodes.pop_front();
                std::cout << tmp->key << " ";
                if(tmp->left){
                    nodes.push_back(tmp->left);
                }
                if(tmp->right){
                    nodes.push_back(tmp->right);
                }
            }
            else{
                Node* tmp = nodes.back();
                nodes.pop_back();
                std::cout << tmp->key << " ";
                if(tmp->right){
                    nodes.push_front(tmp->right);
                }
                if(tmp->left){
                    nodes.push_front(tmp->left);
                }
            }
        } 
    }
    std::cout << std::endl;
}

void add_node(Node **root, int key){
    if(*root == nullptr){
        *root = new Node();
        (*root)->key = key;
        return;
    }

    if(key > (*root)->key){
        add_node(&(*root)->right, key);
    }
    else{
        add_node(&(*root)->left, key);
    }

    return;
}

int main(){

    Node *root = nullptr;
    int n;
    std::cin >> n;
    std::vector <int> niz(n);
    for(int i = 0; i < n; i++){
        std::cin >> niz[i];
    }
    for(int key : niz){
        add_node(&root, key);
    }

    spiral(root, true);

    free_tree(root);

    exit(EXIT_SUCCESS);
}