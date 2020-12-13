#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

bool compare_func(pair<int, int>& p1, pair<int, int>& p2);

int main(int argc, char** argv){
	int n, num = 1; cin >> n;
	vector<pair<int, int>> info(n);

	for(int i = 0; i < n; i++){
		cin >> info[i].first >> info[i].second;
	}
	
	sort(info.begin(), info.end(), compare_func);
	
	for(int i = 1; i < n; i++){
		if(info[i].first == info[i - 1].first || info[i].second >= info[i - 1].second){
			num += 1;
		}
	}

	cout << num << endl;

	exit(EXIT_SUCCESS);
}

bool compare_func(pair<int, int>& p1, pair<int, int>& p2){
	return (p1.first > p2.first) || (p1.first == p2.first && p1.second > p2.second);
}