#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

struct Node {
	std::string word = "";
	std::unordered_map<char, Node*> nodes;
};

void destroy_dic(Node* root){
	if(root == nullptr){
		return;
	}

	for(auto x : root->nodes){
		destroy_dic(x.second);
	}

	delete root;
}

void add_word(Node* root, std::string &word, int i){
	if(i == (int) word.size()){
		root->word = word;
		return;
	}

	auto iter = root->nodes.find(word[i]);

	if(iter == root->nodes.end()){
		root->nodes[word[i]] = new Node();
	}

	add_word(root->nodes[word[i]], word, i + 1);
}

void depth(Node* root){
	if(root->word != ""){
		std::cout << root->word << std::endl;
	}

	auto begin = root->nodes.begin();
	auto end = root->nodes.end();

	while(begin != end){
		depth(begin->second);
		begin++;
	}
}

void autocomplete(Node* root, std::string &word, int i){

	if(i == (int)word.size() && root->word != ""){
		std::cout << word << std::endl;
	}
	else if(i == (int) word.size() && root->word == ""){
		auto begin = root->nodes.begin();
		auto end = root->nodes.end();

		while(begin != end){
			depth(begin->second);
			begin++;
		}
	}
	else{
		auto iter = root->nodes.find(word[i]);

		if(iter == root->nodes.end()){
			std::cout << "No autocomplete entries" << std::endl;
			return;
		}

		autocomplete(root->nodes[word[i]], word, i + 1);
	}

}

int main(int argc, char** argv){

	int n; std::cin >> n;
	std::string word;

	Node* root = new Node();

	for(int i = 0; i < n; i++){
		std::cin >> word;
		add_word(root, word, 0);
	}

	std::cin >> word;
	autocomplete(root, word, 0);

	exit(EXIT_SUCCESS);
}