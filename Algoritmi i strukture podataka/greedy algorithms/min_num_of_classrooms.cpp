#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

unsigned num_of_classrooms(vector<pair<unsigned, unsigned>>& times, priority_queue<unsigned>& endTimes);
bool compare_func(pair<unsigned, unsigned>& p1, pair<unsigned, unsigned>& p2);

int main(int argc, char** argv){

	unsigned n, hs, he, ms, me; cin >> n;
	vector<pair<unsigned, unsigned>> times(n);
	priority_queue<unsigned, vector<unsigned>, less<unsigned>> endTimes;

	for(int i = 0; i < n; i++){
		cin >> hs >> ms >> he >> me;
		times[i].first = hs * 60 + ms;
		times[i].second = he * 60 + me;
	}

	sort(times.begin(), times.end(), compare_func);

	cout << num_of_classrooms(times, endTimes) << endl;

	exit(EXIT_SUCCESS);
}

bool compare_func(pair<unsigned, unsigned>& p1, pair<unsigned, unsigned>& p2){
	return p1.first < p2.first;
}

unsigned num_of_classrooms(vector<pair<unsigned, unsigned>>& times, priority_queue<unsigned>& endTimes){
	unsigned num = 0, size = times.size();

	for(int i = 0; i < size; i++){
		if(endTimes.empty()){
			num += 1;
			endTimes.push(times[i].second);
		}
		else if(endTimes.top() > times[i].first){
			endTimes.push(times[i].second);
			num += 1;
		}
		else{
			endTimes.pop();
			endTimes.push(times[i].second);
		}
	}

	return num;
}