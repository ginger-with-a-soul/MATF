#include <iostream>
#include <vector>
#include <map>
#include <string>

struct Node {
	std::string word = "";
	std::map<char, Node*> nodes;
};

void add_word(Node* root, std::string& word, int i){
	if(i == (int)word.size()){
		root->word = word;
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

void lex(Node* root){
	if(root->word != ""){
		std::cout << root->word << std::endl;
	}

	auto beg_it = root->nodes.begin();
	auto end_it = root->nodes.end();

	while(beg_it != end_it){
		lex(beg_it->second);
		beg_it++;
	}

}

int main(int argc, char** argv){

	std::vector<std::string> words = {"ana", "anastasija", "anastasijin", "anamarija", "anamarijin"};

	Node* root = new Node();

	for(auto s : words){
		add_word(root, s, 0);
	}

	lex(root);

	destroy_tree(root);

	exit(EXIT_SUCCESS);
}