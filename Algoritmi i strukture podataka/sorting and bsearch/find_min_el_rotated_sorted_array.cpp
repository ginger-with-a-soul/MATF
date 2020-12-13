#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>

using namespace std;

unsigned find_min(vector<int>& array);

int main(int argc, char** argv){

	unsigned n, k; cin >> n >> k;
	vector<int> array(n);
	vector<int> array_copy(n);

	for(int i = 0; i < n; i++){
		cin >> array[i];
	}

	sort(array.begin(), array.end());

	for(int i = 0; i < n; i++){
		if(k > i){
			array_copy[i] = array[n + i - k];
		}
		else{
			array_copy[i] = array[abs(i - k)];
		}
	}

	for(auto x : array_copy){
		cout << x << " ";
	}
	cout << endl;

	cout << find_min(array_copy) << endl;

	exit(EXIT_SUCCESS);
}

unsigned find_min(vector<int>& array){
	unsigned l = 0, r = array.size() - 1, m;
	int first = array[0];

	while(l <= r){
		m = l + (r - l) / 2;
		if(array[m] > first){
			l = m + 1;
		}
		else{
			r = m - 1;
		}
	}
	
	if(l == array.size()){
		return array[0];
	}
	else{
		return array[l];
	}

}