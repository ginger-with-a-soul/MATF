#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

bool exist_next_var(vector<int>& var, int n);
void all_next_var(vector<int>& var, int n);

int main(int argc, char** argv){

	int n; cin >> n;
	vector<int> var = {2, 1, 3, 3, 2};

	all_next_var(var, n);

	exit(EXIT_SUCCESS);
}

void all_next_var(vector<int>& var, int n){
	while(exist_next_var(var, n)){
		for(int i = 0; i < var.size(); i++){
			cout << var[i] << " ";
		}
		cout << endl;
	}
}

bool exist_next_var(vector<int>& var, int n){
	int k = var.size() - 1;
	for(; k >= 0 && var[k] == n; k--){
		var[k] = 1;
	}
	if(k < 0){
		return false;
	}
	else{
		var[k] += 1;
		return true;
	}
}