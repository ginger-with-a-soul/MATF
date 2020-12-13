#include <iostream>
#include <vector>
#include <unordered_map>
#include <stack>

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

bool is_leaf(Node *tmp){
    return !tmp->left && !tmp->right;
}

void print_leaf(Node *leaf, std::unordered_map <Node*, Node*> mapa){
    Node *tmp = leaf;
    while(mapa[tmp]){
        std::cout << tmp->key << "->";
        tmp = mapa[tmp];
    }
    std::cout << tmp->key << std::endl;
}

void leaf_to_root(Node *root){
    std::stack <Node*> stek;
    std::unordered_map <Node*, Node*> mapa;
    stek.push(root);
    mapa[root] = nullptr;
    Node* tmp;

    while(stek.size()){
        tmp = stek.top();
        stek.pop();
        if(is_leaf(tmp)){
            print_leaf(tmp, mapa);
        }

        if(tmp->right){
            stek.push(tmp->right);
            mapa[tmp->right] = tmp;
        }
        if(tmp->left){
            stek.push(tmp->left);
            mapa[tmp->left] = tmp;
        }
    }
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
}

int main(){

    Node* root = nullptr;
    int n;
    std::cin >> n;
    std::vector <int> array(n);

    for(int i = 0; i < n; i++){
        std::cin >> array[i];
    }
    for(int key : array){
        add_node(&root, key);
    }

    leaf_to_root(root);

    free_tree(root);

    exit(EXIT_SUCCESS);
}