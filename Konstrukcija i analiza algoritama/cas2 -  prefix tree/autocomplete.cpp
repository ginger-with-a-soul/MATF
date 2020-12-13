#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>

struct Node {
	std::string word = "";
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

	auto beg = root->nodes.begin();
	auto end = root->nodes.end();
	while(beg != end){
		depth(beg->second);
		beg++;
	}
}

void find(Node* root, std::string &my_word, unsigned i){
	if(i == (unsigned)my_word.size() && root->word == ""){
		auto beg = root->nodes.begin();
		auto end = root->nodes.end();

		while(beg != end){
			depth(beg->second);
			beg++;
		}
	}
	else if(i == (unsigned)my_word.size() && root->word != ""){
		std::cout << my_word << std::endl;
	}
	else{
		auto it = root->nodes.find(my_word[i]);
		if(it == root->nodes.end()){
			std::cout << "No autocomplete entries!" << std::endl;
			return;
		}

		find(root->nodes[my_word[i]], my_word, i + 1);
	}
}

int main(int argc, char** argv){

	Node* root = new Node();

	std::vector<std::string> words = {"banana", "bycicle", "bilingual", "boomerang", "bonus",
									  "bussiness", "bike", "biker", "bipolar", "bureau", "Bob"};
	
	for(auto s : words){
		add_word(root, s, 0);
	}

	std::string my_word = "";
	std::cin >> my_word;

	find(root, my_word, 0);

	destroy_tree(root);

	exit(EXIT_SUCCESS);
}