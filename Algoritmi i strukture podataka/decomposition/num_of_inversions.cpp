#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int num_of_inversions(vector<int>& array);
int merge_sort_inversion_modifed(vector<int>& a, int l, int r, vector<int>& tmp);

int main(int argc, char** argv){

	int n; cin >> n;
	vector<int> array(n);
	for(int i = 0; i < n; i++){
		cin >> array[i];
	}

	cout << num_of_inversions(array) << endl;

	exit(EXIT_SUCCESS);
}

int num_of_inversions(vector<int>& array){
	int size = array.size();
	vector<int> tmp1(size);
	vector<int> tmp2(size);

	for(int i = 0; i < size; i++){
		tmp1[i] = array[i];
	}

	return merge_sort_inversion_modifed(tmp1, 0, size - 1, tmp2);
}

int merge_sort_inversion_modifed(vector<int>& a, int l, int r, vector<int>& tmp){
	if(l >= r){
		return 0;
	}
	int m = l + (r - l) / 2, num = 0;
	num += merge_sort_inversion_modifed(a, l, m, tmp);
	num += merge_sort_inversion_modifed(a, m + 1, r, tmp);
	int hl = l, m1 = m, m2 = m + 1, k = 0;
	while(hl <= m1 && m2 <= r){
		if(a[hl] > a[m2]){
			tmp[k++] = a[m2++];
			num += m1 - hl + 1;
		}
		else{
			tmp[k++] = a[hl++];
		}
	}
	while(hl <= m1){
		tmp[k++] = a[hl++];
	}
	while(m2 <= r){
		tmp[k++] = a[m2++];
	}

	for(int i = l; i <= r; i++){
		a[i] = tmp[i];
	}

	return num;
}