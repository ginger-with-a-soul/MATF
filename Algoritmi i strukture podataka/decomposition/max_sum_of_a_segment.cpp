#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int max_seg(vector<int>& a);
void max_all_parts(const vector<int>& a, int l, int r, int& sum, int& max_sum, int& max_prefix, int& max_sufix);

int main(int argc, char** argv){

	int n; cin >> n;
	vector<int> a(n);
	for(int i = 0; i < n; i++){
		cin >> a[i];
	}

	cout << max_seg(a) << endl;

	exit(EXIT_SUCCESS);
}

int max_seg(vector<int>& a){

	int sum, max_sum, max_prefix, max_sufix;

	max_all_parts(a, 0, a.size() - 1, sum, max_sum, max_prefix, max_sufix);

	return max_sum;
}

void max_all_parts(const vector<int>& a, int l, int r, int& sum, int& max_sum, int& max_prefix, int& max_sufix){

	if(l == r){
		sum = max_sum = max_prefix = max_sufix = a[l];
		return;
	}

	int m = l + (r - l) / 2;
	int left_sum, max_left_sum, max_left_prefix, max_left_sufix;
	max_all_parts(a, l, m, left_sum, max_left_sum, max_left_prefix, max_left_sufix);
	int right_sum, max_right_sum, max_right_prefix, max_right_sufix;
	max_all_parts(a, m + 1, r, right_sum, max_right_sum, max_right_prefix, max_right_sufix);
	sum = left_sum + right_sum;
	max_prefix = max(max_left_prefix, left_sum + max_right_prefix);
	max_sufix = max(max_right_sufix, right_sum + max_left_sufix);
	max_sum = max({max_left_sum, max_right_sum, max_left_sufix + max_right_prefix});
}