#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>

struct Node {
	bool is_leaf = false;
	std::unordered_map<char, Node*> nodes;
};

Node* create_node(){
	return new Node();
}

void add_word(Node* root, std::string &word, int i){
	if(i == (int)word.size()){
		root->is_leaf = true;
		return;
	}

	auto iterator = root->nodes.find(word[i]);
	if(iterator == root->nodes.end()){
		root->nodes[word[i]] = create_node();
	}

	add_word(root->nodes[word[i]], word, i + 1);
}

bool find_word(Node* root, std::string &word, int i){
	if(i == (int)word.size()){
		return root->is_leaf;
	}

	auto iterator = root->nodes.find(word[i]);
	if(iterator == root->nodes.end()){
		return false;
	}

	find_word(root->nodes[word[i]], word, i + 1);
}

void delete_tree(Node* root){
	if(root = nullptr){
		return;
	}

	for(auto node : root->nodes){
		delete_tree(node.second);
	}

	delete root;

}

int main(int argc, char** argv){

	Node* root = create_node();

	std::vector<std::string> words = {"cod", "coder", "coding", "codecs"};
	std::string word = "coder";

	for(std::string x : words){
		add_word(root, x, 0);
	}

	std::cout << std::boolalpha << find_word(root, word, 0) << std::endl;

	exit(EXIT_SUCCESS);
}