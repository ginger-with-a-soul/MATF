#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <queue>
#include <utility>

struct Node {
	std::string word = "";
	unsigned num = 0;
	std::unordered_map<char, Node*> nodes;
};

void add_word(Node* root, std::string &word, int i){
	if(i == (int)word.size()){
		root->word = word;
		root->num++;
		return;
	}

	auto iter = root->nodes.find(word[i]);
	if(iter == root->nodes.end()){
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

void my_heap_sort(Node* root,  std::priority_queue<std::pair<unsigned, std::string>> *q){
	if(root->word != ""){
		q->push(std::make_pair(root->num, root->word));
	}

	auto beg = root->nodes.begin();
	auto end = root->nodes.end();

	while(beg != end){
		my_heap_sort(beg->second, q);
		beg++;
	}
}


int main(int argc, char** argv){

	Node* root = new Node();

	std::vector<std::string> words = {"the", "most", "ocurring", "word", "is", "is", "and", "is", 
									"occurs", "3", "times", "the"};

	unsigned k = 0;
	std::cin >> k;

	std::priority_queue<std::pair<unsigned, std::string>> q;

	for(auto s : words){
		add_word(root, s, 0);
	}

	my_heap_sort(root, &q);

	while(k && !q.empty()){
		std::cout << q.top().second << " occurs " << q.top().first << " times" << std::endl;
		q.pop();
		k--;
	}

	destroy_tree(root);

	exit(EXIT_SUCCESS);
}