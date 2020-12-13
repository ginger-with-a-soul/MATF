#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

bool next_perm(vector<int>& perm);
bool queens_are_satisfied(vector<int>& perm);

int main(int argc, char** argv){

	int n; cin >> n;
	vector<int> perm(n);
	for(int i = 0; i < n; i++){
		perm[i] = i + 1;
	}

	do {
		
		if(queens_are_satisfied(perm)){
			for(int i = 0; i < perm.size(); i++){
				cout << perm[i] << " ";
			}
			cout << endl;
		}

	} while(next_perm(perm));

	exit(EXIT_SUCCESS);
}

bool next_perm(vector<int>& perm){
	int i = perm.size() - 2;

	for(; i >= 0 && perm[i] > perm[i + 1]; i--){}

	if(i < 0){
		return false;
	}

	int j = perm.size() - 1;
	for(; j > 0 && perm[j] < perm[i]; j--){}

	swap(perm[i], perm[j]);

	j = perm.size() - 1;
	i += 1;
	while(i < j){
		swap(perm[i++], perm[j--]);
	}

	return true;
}

bool queens_are_satisfied(vector<int>& perm){
	int n = perm.size();

	for(int i = 0; i < n; i++){
		for(int j = i + 1; j < n; j++){
			if(abs(i - j) == abs(perm[i] - perm[j])){
				return false;
			}
		}
	}
	return true;
}