#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

bool exists_next_permutation(vector<int>& perm, int n);

int main(int argc, char** argv){

	int n; cin >> n;
	vector<int> perm(n);

	for(int i = 0; i < n; i++){
		cin >> perm[i];
	}

	while(exists_next_permutation(perm, n)){
		
		for(int i = 0; i < n; i++){
			cout << perm[i] << " ";
		}

		cout << endl;
	}

	exit(EXIT_SUCCESS);
}

bool exists_next_permutation(vector<int>& perm, int n){
	int i = n - 2;
	for(; i >= 0 && perm[i] > perm[i + 1]; i--){}

	if(i < 0){
		return false;
	}

	int j = n - 1;
	while(perm[i] > perm[j]){
		j -= 1;
	}

	swap(perm[i], perm[j]);

	for(i++, j = n-1; i < j; j--, i++){
		swap(perm[i], perm[j]);
	}
	return true;
}