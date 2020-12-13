#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>

struct Node {
	std::string word = "";
	unsigned num = 0;
	std::unordered_map<char, Node*> nodes;
};

void add_word(Node* root, std::string &word, int i, std::string &max_word, unsigned *max_num){
	if(i == (int)word.size()){
		root->word = word;
		root->num++;
		if(root->num > *max_num){
			*max_num = root->num;
			max_word = root->word;
		}
		return;
	}

	auto iter = root->nodes.find(word[i]);
	if(iter == root->nodes.end()){
		root->nodes[word[i]] = new Node();
	}

	add_word(root->nodes[word[i]], word, i + 1, max_word, max_num);
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


int main(int argc, char** argv){

	Node* root = new Node();

	std::vector<std::string> words = {"the", "most", "ocurring", "word", "is", "is", "and", "is", 
									"occurs", "3", "times"};

	std::string max_word = "";
	unsigned max_num = 0;

	for(auto s : words){
		add_word(root, s, 0, max_word, &max_num);
	}

	std::cout<< max_word << " " << max_num << std::endl;

	destroy_tree(root);

	exit(EXIT_SUCCESS);
}