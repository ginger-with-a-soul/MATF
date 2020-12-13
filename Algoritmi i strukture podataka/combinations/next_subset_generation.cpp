#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

void generate_next_subset(vector<int>& subset, int n);

int main(int argc, char** argv){

	int n; cin >> n;
	vector<int> subset = {4};

	generate_next_subset(subset, n);

	for(int i = 0; i < subset.size(); i++){
		cout << subset[i] << " ";
	}

	cout << endl;

	exit(EXIT_SUCCESS);
}

void generate_next_subset(vector<int>& subset, int n){
	if(subset.empty()){
		subset.push_back(1);
		return;
	}

	if(subset.back() < n){
		subset.push_back(subset.back() + 1);
		return;
	}

	subset.pop_back();

	if(subset.empty()){
		exit(EXIT_SUCCESS);
	}
	
	subset.back() += 1;
	return;
}