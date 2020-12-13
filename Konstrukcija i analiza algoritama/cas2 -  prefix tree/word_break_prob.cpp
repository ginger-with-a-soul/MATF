#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>

struct Node {
	bool is_leaf = false;
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

void add_word(Node* root, std::string &word, int i){
	if(i == (int)word.size()){
		root->is_leaf = true;
		return;
	}

	auto iter = root->nodes.find(word[i]);
	if(iter == root->nodes.end()){
		root->nodes[word[i]] = new Node();
	}

	add_word(root->nodes[word[i]], word, i + 1);
}

bool matcher(Node* root, std::string &needle){
	int size = needle.size();

	std::vector<bool> progress(size);

	progress[0] = true;
	Node* tmp;

	for(int i = 0; i < size; i++){

		tmp = root;
		
		if(progress[i]){
			for(int j = i; j < size; j++){
				auto iter = tmp->nodes.find(needle[j]);
				
				if(iter == tmp->nodes.end()){
					break;
				}

				tmp = tmp->nodes[needle[j]];

				if(tmp->is_leaf){
					progress[j + 1] = true;
				}
				if(j == size - 1){
					return true;
				}
			}
		}

	}
	return false;
}

int main(int argc,  char** argv){

	Node* root = new Node();

	std::vector<std::string> D = {"word", "br", "k", "pr", "oblem", "ea"};

	std::string needle = "wordbreakproblem";

	for(std::string s : D){
		add_word(root, s, 0);
	}

	if(matcher(root, needle)){
		std::cout << "Needle found!" << std::endl;
	}
	else{
		std::cout << "Needle couldn't be found" << std::endl;
	}

	destroy_tree(root);

	exit(EXIT_SUCCESS);
}