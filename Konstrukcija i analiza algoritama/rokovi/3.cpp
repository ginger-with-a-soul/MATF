#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

struct Node {
	bool is_leaf = false;
	std::unordered_map<char, Node*> nodes;
	char came_with = '$';

};

void add_word(Node* root, std::string &word, int i){
	if(i == (int) word.size()){
		root->is_leaf = true;
		return;
	}

	auto iter = root->nodes.find(word[i]);
	if(iter == root->nodes.end()){
		root->nodes[word[i]] = new Node();
	}

	add_word(root->nodes[word[i]], word, i + 1);
}

void find_palindrome(Node* root, std::string &word, int i, Node* parent){
	if(i == (int) word.size()){

	}
	auto iter = root->nodes.find(word[i]);

	if(iter == root->nodes.end() && parent->came_with != word[i]){
		root->nodes[word[i]] = new Node();
	}
	else if(iter != root->nodes.end()){
		parent->came_with = word[i];
		find_palindrome(root->nodes[word[i]], word, i + 1, parent);
	}
	else if(parent->came_with == word[i]){
		find_palindrome(parent, word, i + 1, )
	}
}

int main(int argc, char** argv){

	int n, m;
	std::cin >> n;

	Node* root = new Node();

	std::string word;

	for(int i = 0; i < n; i++){
		std::cin >> word;
		add_word(root, word, 0);
	}

	std::cin >> m;

	for(int i = 0; i < m; i++){
		std::cin >> word;
		std::reverse(word.begin(), word.end());
		find_palindrome(root, word, 0, root);
	}

	exit(EXIT_SUCCESS);
}