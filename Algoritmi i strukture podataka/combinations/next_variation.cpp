#include <iostream>
#include <vector>

using namespace std;

bool next_var(vector<int>&var, int k, int n);

int main(){
	int n, k, x = 0;
	cin >> n >> k;
	vector<int>var(k);

	while(x < k){
		cin >> var[x++];
	}

	if(next_var(var, k, n)){
		for(int i = 0; i < var.size(); i++){
			cout << var[i] << " ";
		}
		cout << endl;
	}
}

bool next_var(vector<int>&var, int k, int n){
	int i = k - 1;

	while(var[i] == n){
		var[i] = 0;
		i--;
		if(i < 0){
			return false;
		}
	}

	var[i]++;
	return true;
}