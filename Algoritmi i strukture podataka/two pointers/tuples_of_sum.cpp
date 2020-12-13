#include <iostream>
#include <vector>

using namespace std;

unsigned tuples_of_sum(vector<int>& a, int sum);

int main(int argc, char** argv){

	unsigned n, s = 0;
	int sum;
	cin >> sum >> n;
	vector<int> a(n);
	for(int i = 0; i < n; i++){
		cin >> a[i];
	}

	s = tuples_of_sum(a, sum);

	cout << s << endl;

	exit(EXIT_SUCCESS);
}

unsigned tuples_of_sum(vector<int>& a, int sum){
	unsigned l = 0, r = a.size() - 1, s = 0, target;

	for(int i = 0; i < a.size() - 2; i++){
		r = a.size() - 1;
		l = i + 1;
		target = sum - a[i];
		while(l < r){
			if(a[l] + a[r] == target){
				s += 1;
				l += 1;
				r -= 1;
			}
			else if(a[l] + a[r] > target){
				r -= 1;
			}
			else{
				l += 1;
			}
		}
	}

	return s;
}