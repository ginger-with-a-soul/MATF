#include <iostream>
#include <vector>

using namespace std;

void find_subsets(vector<int>&set, vector<int>&subset);

int main(){

	int n;
	cin >> n;
	vector<int>set(n);
	vector<int>subset;

	for(int i = 0; i < n; i++){
		cin >> set[i];
	}

	find_subsets(set, subset);

}


void find_subsets(vector<int>&set, vector<int>&subset){

	if(set.empty()){
		for(int i = 0; i < subset.size(); i++){
			cout << subset[i] << " ";
		}
		cout << endl;
		return;
	}
	
	int x = set.back();
	set.pop_back();

	find_subsets(set, subset);

	subset.push_back(x);

	find_subsets(set, subset);

	set.push_back(x);
	subset.pop_back();
}