#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>

struct Node {
	std::string word = ""
	unsigned num = 0;
	std::unordered_map<char, Node*> nodes;
};

void destroy_tree(Node* root){
	if(root == nullptr){
		return;
	}

	for(auto x : root->nodes){
		destroy_tree(x.second);
	}

	delete root;
}

void add_word(Node* root, std::string &word, unsigned i){
	if(i == (unsigned)word.size()){
		root->word = word;
		root->num++;

	}
}

int main(int argc, char** argv){

	unsigned n, m;
	std::cin >> n >> m;
	for(int i = 0; i < n; i++){
		for(int j = 0; j < m; j++){
			std::string x = "";
			char y = getc();
			x.append(tos);
		}
	}

	exit(EXIT_SUCCESS);
}