#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void counting_sort(vector<int>& array);

int main(int argc, char** argv){

	unsigned n; cin >> n;
	vector<int> array(n);
	
	for(int i = 0; i < n; i++){
		cin >> array[i];
	}

	counting_sort(array);

	for(int i = 0; i < n; i++){
		cout << array[i] << " ";
	}

	cout << endl;

	exit(EXIT_SUCCESS);
}

void counting_sort(vector<int>& array){

	int m = *max_element(array.begin(), array.end());
	unsigned size = array.size();

	vector<int> occurrences(m + 1, 0);

	for(int i = 0; i < size; i++){
		occurrences[array[i]] += 1;
	}

	for(int i = 0, k = 0; i < m + 1; i++){
		for(int j = 0; j < occurrences[i]; j++){
			array[k++] = i;
		}
	}

}