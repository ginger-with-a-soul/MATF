#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

void merge_sort(vector<int>& array);
void merge_sort_divider(vector<int>& array, int l, int r, vector<int>& tmp);
void merge(vector<int>& array1, int l, int m1, vector<int>& array2, int m2, int r, vector<int>& tmp, int start);

int main(int argc, char** argv){

	int n; cin >> n;
	vector<int> array(n);

	for(int i = 0; i < n; i++){
		cin >> array[i];
	}

	merge_sort(array);

	for(int x : array){
		cout << x << " ";
	}
	
	cout << endl;

	exit(EXIT_SUCCESS);
}

void merge_sort(vector<int>& array){
	int size = array.size();
	vector<int> tmp(size);

	merge_sort_divider(array, 0, size - 1, tmp);
}

void merge_sort_divider(vector<int>& array, int l, int r, vector<int>& tmp){
	if(l < r){
		int m = l + (r - l) / 2;
		merge_sort_divider(array, l, m, tmp);
		merge_sort_divider(array, m + 1, r, tmp);
		merge(array, l, m, array, m + 1, r, tmp, l);

		for(int i = l; i <= r; i++){
			array[i] = tmp[i];
		}
	}
}

void merge(vector<int>& array1, int l, int m1, vector<int>& array2, int m2, int r, vector<int>& tmp, int start){
	while(l <= m1 && m2 <= r){
		tmp[start++] = array1[l] <= array2[m2]? array1[l++] : array2[m2++];
	}
	while(l <= m1){
		tmp[start++] = array1[l++];
	}
	while(m2 <= r){
		tmp[start++] = array2[m2++];
	}
}