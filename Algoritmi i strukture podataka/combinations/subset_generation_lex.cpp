#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

void generate_subset(vector<int>& set, int i, vector<int>& subset, int j);

int main(int argc, char** argv){

	int n; cin >> n;
	vector<int> set(n);
	vector<int> subset(n);

	for(int i = 0; i < n; i++){
		cin >> set[i];
	}

	generate_subset(set, 0, subset, 0);

	exit(EXIT_SUCCESS);
}

void generate_subset(vector<int>& set, int i, vector<int>& subset, int j){

	if(i == set.size()){
		for(int k = 0; k < j; k++){
			cout << subset[k] << " ";
		}
		cout << endl;
		return;
	}

	generate_subset(set, i + 1, subset, j);
	subset[j] = set[i];
	generate_subset(set, i + 1, subset, j + 1);

}