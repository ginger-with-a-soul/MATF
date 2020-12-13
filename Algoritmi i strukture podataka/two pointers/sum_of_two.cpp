#include <iostream>
#include <vector>

using namespace std;

unsigned sum_of_two(vector<int>& a, unsigned sum);

int main(int argc, char** argv){

	unsigned n, sum, s = 0;
	cin >> sum;
	cin >> n;
	vector<int> a(n);
	for(int i = 0; i < n; i++){
		cin >> a[i];
	}

	s = sum_of_two(a, sum);

	cout << s << endl;

	exit(EXIT_SUCCESS);
}

unsigned sum_of_two(vector<int>& a, unsigned sum){
	unsigned l = 0, r = a.size() - 1, s = 0;
	while(l < r){
		if(a[l] + a[r] == sum){
			s += 1;
			l += 1;
			r -= 1;
		}
		else if(a[l] + a[r] > sum){
			r -= 1;
		}
		else{
			l += 1;
		}
	}
	return s;
}