#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

struct Node {
	bool is_leaf = false;
	std::unordered_map<char, Node*> nodes;
};

void add_word(Node* root, std::string &word, int i){
	if(i == (int)word.size()){
		root->is_leaf = true;
		return;
	}

	auto iterator = root->nodes.find(word[i]);
	if(iterator == root->nodes.end()){
		root->nodes[word[i]] = new Node();
	}

	add_word(root->nodes[word[i]], word, i + 1);
}

void destroy_tree(Node* root){
	if(root == nullptr){
		return;
	}

	for(auto x : root->nodes){
		destroy_tree(x.second);
	}

	delete root;
}

void lcp(Node* root, unsigned *i){
	if(root->nodes.size() == 1 && !root->is_leaf){
		*i += 1;
		lcp(root->nodes.begin()->second, i);
	}
}

int main(int arcg, char** argv){

	Node* root = new Node();
	std::vector<std::string> words = {"code", "coder", "codecs", "coding"};

	for(std::string s : words){
		add_word(root, s, 0);
	}
	unsigned i = 0;
	lcp(root, &i);
	std::cout << i << std::endl;

	destroy_tree(root);

	exit(EXIT_SUCCESS);
}