#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

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

void add_word(Node* root, std::string &word, int i){
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

bool word_break_problem(Node* root, std::string &needle){
	int n = needle.size();
	std::vector<bool> progress(n, false);
	progress[0] = true;
	Node* tmp;

	for(int i = 0; i < n; i++){
		tmp = root;
		if(progress[i]){
			for(int j = i; j < n; j++){
				auto iter = tmp->nodes.find(needle[j]);

				if(iter == tmp->nodes.end()){
					break;
				}

				tmp = tmp->nodes[needle[j]];

				if(tmp->word != ""){
					progress[j + 1] = true;
				}

				if(j == n - 1){
					return true;
				}
			}
		}
	}
	return false;

}

int main(int argc, char** argv){

	Node *root = new Node();
	int n; std::cin >> n;

	std::vector<std::string> words(n);

	for(int i = 0; i < n; i++){
		std::cin >> words[i];
		add_word(root, words[i], 0);
	}

	std::string needle; std::cin >> needle;

	std::cout << std::boolalpha << word_break_problem(root, needle) << std::endl;

	exit(EXIT_SUCCESS);
}