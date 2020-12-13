#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int next_perm(vector<int>& perm);

int main(int argc, char** argv){
	 
	int n; cin >> n;
	if(n < 1 || n > 10){
		cerr << "invalid n value" << endl;
		exit(EXIT_FAILURE);
	}

	vector<int> perm(n);
	for(int i = 0; i < n; i++){
		perm[i] = i + 1;
	}

	int i = 1;
	do {
		if(i == 1){
			for(auto x : perm){
				cout << x << " ";
			}
			cout << endl;
		}
	} while((i = next_perm(perm)));

	exit(EXIT_SUCCESS);
}

int next_perm(vector<int>& perm){
	int n = perm.size();
	int i = n - 2;

	for(; i >= 0 && perm[i] > perm[i + 1]; i--){}

	if(i < 0){
		return 0;
	}

	int j = n - 1;
	for(; j > 0 && perm[j] < perm[i]; j--){}

	swap(perm[i], perm[j]);
	j = n - 1;
	i += 1;
	while(i < j){
		swap(perm[i++], perm[j--]);
	}

	i = n - 2;
	for(; i >= 0 && perm[i] % 2 != perm[i + 1] % 2; i--){}

	if(i < 0){
		return 1;
	}
	else{
		return  - 1;
	}
}