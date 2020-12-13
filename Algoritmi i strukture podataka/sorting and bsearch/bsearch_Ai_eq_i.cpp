#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

unsigned return_pos(vector<int>& array);

int main(int argc, char** argv){

	unsigned n; cin >> n;
	vector<int> array(n);
	for(int i = 0; i < n; i++){
		cin >> array[i];
	}

	sort(array.begin(), array.end());

	cout << return_pos(array) << endl;

	exit(EXIT_SUCCESS);
}

unsigned return_pos(vector<int>& array){

	unsigned size = array.size();

	for(int i = 0; i < size; i++){
		array[i] -= i;
	}

	auto it = lower_bound(array.begin(), array.end(), 0);

	if(it != array.end() && *it == 0){
		return distance(array.begin(), it);
	}
	else{
		return -1;
	}

}