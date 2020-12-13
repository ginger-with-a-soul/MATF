#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void perm(vector<int>&set, int k){
	if(k == 1){
		for(int i = 0; i < set.size(); i++){
			cout << set[i] << " ";
		}
		cout << endl;
	}

	for(int i = 0; i < k; i++){
		swap(set[i], set[k - 1]);
		perm(set, k - 1);
		swap(set[i], set[k - 1]);
	}

}

int main(){
	vector<int> set = {1, 2, 3};
	int k = 3;
	perm(set, k);
	exit(EXIT_SUCCESS);
}