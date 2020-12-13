#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

unsigned bang_for_buck(vector<unsigned>& weight, vector<unsigned>& price, unsigned capacity);
bool compare_func(pair<double, unsigned>& p1, pair<double, unsigned>& p2);

int main(int argc, char** argv){

	unsigned n, capacity;
	cin >> n >> capacity;

	vector<unsigned> weight(n);
	vector<unsigned> price(n);
	for(int i = 0; i < n; i++){
		cin >> weight[i] >> price[i];
	}

	cout << bang_for_buck(weight, price, capacity) << endl;

	exit(EXIT_SUCCESS);
}

unsigned bang_for_buck(vector<unsigned>& weight, vector<unsigned>& price, unsigned capacity){
	unsigned size = weight.size();
	double value = 0;

	vector<pair<double, unsigned>> unitPriceAndWeight(size);

	for(int i = 0; i < size; i++){
		double unitPrice = (double) price[i] / (double) weight[i];
		unitPriceAndWeight[i] = make_pair(unitPrice, weight[i]);
	}

	sort(unitPriceAndWeight.begin(), unitPriceAndWeight.end(), compare_func);

	for(int i = 0; i < size && capacity > 0; i++){
		if(capacity >= unitPriceAndWeight[i].second){
			capacity -= unitPriceAndWeight[i].second;
			value += unitPriceAndWeight[i].first * unitPriceAndWeight[i].second;
		}
		else{
			value += unitPriceAndWeight[i].first * capacity;
			capacity = 0;
		}
	}

	return value;
}

bool compare_func(pair<double, unsigned>& p1, pair<double, unsigned>& p2){
	return p1.first > p2.first;
}