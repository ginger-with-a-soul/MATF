#include <vector>
#include <numeric>
#include <iostream>

int accumulate(std::vector<int> &a, int default_value)
{
	int n = a.size();

	for (int i = 0; i < n; i++) {
		default_value += a[i];
	}

	return default_value;
}

int main ()
{
	std::vector<int> a = {1, 2, 3, 4, 5};

	// 25 + 16 + 9 + 4 + 1 = 55

	// PRVI ARGUMENT JE UVEK AKUMULATOR!!!
	std::cout << std::accumulate(a.begin(), a.end(), 0, [](int acc, int x){ return acc + x * x; }) << "\n";

	// std::cout << accumulate(a, 100) << "\n"; 

	return 0;
}