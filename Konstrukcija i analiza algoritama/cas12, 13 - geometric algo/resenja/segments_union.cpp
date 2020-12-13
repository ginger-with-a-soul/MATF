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

int interval_union(std::vector<Segment> &segments)
{
	// Pamtimo maksimalni desni kraj
	int right = segments[0].get_end();

	// Duzina unije je na pocetku velicina pocetnog segmenta
	int sum = segments[0].get_end() - segments[0].get_begin();

	int n = segments.size();

	for (int i = 1; i < n; i++) {
		// Ako je segment unutar drugog segmenta necemo racunati njegovu duzinu,
		// dovoljno je uzeti samo veci segment.
		// Ako segment prevazilazi trenutni maksimum imamo 2 slucaja. Jedan slucaj je da je njegov
		// levi deo unutar prethodnog segmenta i onda racunamo samo razliku njegovog kraja i
		// prethodnog kraja (else grana i primer a = [1,5], b = [3, 7] na uniju treba dodati 7 - 5).
		// Drugi slucaj je da je ceo segment desno od prethodnog segmenta i onda ceo dodajemo na uniju
		// (if grana i primer a = [1,3] b = [4,6] i onda dodajemo 6 - 4).
		if (segments[i].get_end() > right) {
			if (segments[i].get_begin() >= right) {
				sum += segments[i].get_end() - segments[i].get_begin();
				right = segments[i].get_end();
			}
			else {
				sum += segments[i].get_end() - right;
				right = segments[i].get_end();
			}
		}
	}

	return sum;
}

int main()
{
	// {1, 2}, {1, 5}, {6, 8}, {6, 9}
	std::vector<Segment> segments = {{1, 2}, {1, 5}, {2, 7}, {3, 9}, {2, 4}, {6, 8}, {5, 8}};

	sort_segments(segments);

	std::cout << interval_union(segments) << std::endl;

	return 0;
}
