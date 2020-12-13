#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>

class Segment
{
public:
	Segment (int b, int e)
	{
		begin = b;
		end = e;
	}

	int get_begin() const { return begin; }
	int get_end() const { return end; }

private:
	int begin, end;
};

// Funkcija compare omogucava da se intervali sortiraju rastuce po pocecima a opadajuce po krajevima
// Zasto opadajuce? Razmotriti slucaj a = [5, 8], b = [5,12]. Ako ide rastuce, a ce biti pre b i algoritam nece
// naci da se a nalazi unutar b
bool compare(const Segment &s1, const Segment &s2)
{
	if (s1.get_begin() == s2.get_begin())
		return s1.get_end() > s2.get_end();

	return s1.get_begin() < s2.get_begin();
}

void sort_segments(std::vector<Segment> &segments)
{
	std::sort(segments.begin(), segments.end(), compare);
}

void find_all_segments(std::vector<Segment> &segments)
{
	int max = segments[0].get_end();

	int n = segments.size();

	for (int i = 1; i < n; i++)
		if (segments[i].get_end() <= max)
			std::cout << "[" << segments[i].get_begin() << ", " << segments[i].get_end() << "]\n";
		else
			max = segments[i].get_end();
}

int main()
{
	// {1, 2}, {1, 5}, {6, 8}, {6, 9}
	std::vector<Segment> segments = {{1, 2}, {1, 5}, {2, 7}, {3, 9}, {2, 4}, {6, 8}, {5, 8}};

	sort_segments(segments);

	find_all_segments(segments);

	return 0;
}
