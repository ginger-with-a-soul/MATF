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

bool compare(const Segment &s1, const Segment &s2)
{
	if (s1.get_begin() == s2.get_begin())
		return s1.get_end() < s2.get_end();

	return s1.get_begin() > s2.get_begin();
}

void sort_segments(std::vector<Segment> &segments)
{
	std::sort(segments.begin(), segments.end(), compare);
}

void find_all_segments(std::vector<Segment> &segments)
{
	int max = segments[0].get_end();

	int max_begin = segments[0].get_begin(), max_end = segments[0].get_end();
	int current_begin = segments[0].get_begin(), current_end = segments[0].get_end();

	int n = segments.size();

	int counter = 0, max_segments = 0;

	for (int i = 1; i <= n; i++)
		if (i != n && segments[i].get_end() >= max) {
			counter++;
        }
		else {
			if (counter > max_segments) {
				max_segments = counter;
				max_begin = current_begin;
				max_end = current_end;
			}
			current_begin = segments[i].get_begin();
			current_end = segments[i].get_end();
			counter = 0;
			max = segments[i].get_end();
		}

	std::cout << max_begin << " " << max_end << " " << max_segments << std::endl;
}

int main()
{
	// = {{12, 10}, {15, 11}, {22, 10}, {18, 14}, {9, 8}, {5, 1}, {10, 8}, {10, 1}};

    int n;

    std::cin >> n;

    std::vector<Segment> segments;

    int x, y;

    for (int i = 0; i < n; i++) {
        std::cin >> x >> y;
        segments.push_back(Segment(x, y));
    }

	sort_segments(segments);

	find_all_segments(segments);

	return 0;
}

