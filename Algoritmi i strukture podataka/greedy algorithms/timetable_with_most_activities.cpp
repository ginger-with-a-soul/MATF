#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

bool compare_func(pair<unsigned, unsigned>& p1, pair<unsigned, unsigned>& p2);
unsigned num_of_activies(vector<pair<unsigned, unsigned>>& times);

int main(int argc, char** argv){

	unsigned n, hs, he, ms, me; cin >> n;
	vector<pair<unsigned, unsigned>> times(n);

	for(int i = 0; i < n; i++){
		cin >> hs >> ms >> he >> me;
		times[i].first = hs * 60 + ms;
		times[i].second = he * 60 + me;
	}

	cout << num_of_activies(times) << endl;

	exit(EXIT_SUCCESS);
}

unsigned num_of_activies(vector<pair<unsigned, unsigned>>& times){
	unsigned size = times.size(), activities = 1, currentEnd = 0;

	sort(times.begin(), times.end(), compare_func);

	currentEnd = times[0].second;

	for(int i = 1; i < size; i++){
		if(times[i].first >= currentEnd){
			currentEnd = times[i].second;
			activities += 1;
		}
	}
	
	return activities;
}

bool compare_func(pair<unsigned, unsigned>& p1, pair<unsigned, unsigned>& p2){
	return p1.second < p2.second;
}