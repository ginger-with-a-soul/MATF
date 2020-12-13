#include <iostream>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

unsigned pairs_of_diff(map<int, int>& a, int diff);

int main(int argc, char** argv){

	int diff, x;
	unsigned n, sum;
	cin >> diff >> n;
	vector<int> a2(n);
	map<int, int> a;
	for(int i = 0; i < n; i++){
		cin >> a2[i];
		a[a2[i]]++;
	}

	sum = pairs_of_diff(a, diff);

	cout << diff << endl;

	exit(EXIT_SUCCESS);
}

unsigned pairs_of_diff(map<int, int>& a, int diff){
	auto i = a.begin(), j = a.begin();
	unsigned s = 0;
	while(j != a.end()){
		if(j->first - i->first < diff){
			j++;
		}
		else if(j->first - i->first > diff){
			i++;
		}
		else{
			s += i->second * j->second;
			j++;
		}
	}

	return s;
}