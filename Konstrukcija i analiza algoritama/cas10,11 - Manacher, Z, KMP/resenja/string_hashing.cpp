#include <iostream>
#include <string>

long long calculate_hash(const std::string &s)
{
	int p = 31;
	int m = 1e9 + 9;
	long long hash_value = 0;

	int n = s.size();
	for(int i = n-1; i >= 0; i--) {
		hash_value = (hash_value * p + (s[i]-'a'+1)) % m;
	}

	return hash_value;
}

int main()
{
	std::string s;

	std::cin >> s;

	std::cout << calculate_hash(s) << "\n";

	return 0;
}