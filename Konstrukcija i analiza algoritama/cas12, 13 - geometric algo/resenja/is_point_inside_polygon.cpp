#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

class Point
{
public:
  Point () {}

  Point (int _x, int _y)
  {
    x = _x;
    y = _y;
  }

  int get_x() const { return x; }
  int get_y() const { return y; }

//private:
  int x;
  int y;
};

class Polygon
{
public:
	Polygon () {}

	Polygon (std::vector<Point> &ps) {
		points = ps;
	}

  // Funkcija koja racuna povrsinu trougla ako su data njegova temena
	float area(const Point &a, const Point &b, const Point &c)
	{
   		return fabs((a.get_x()*(b.get_y()-c.get_y()) + b.get_x()*(c.get_y()-a.get_y())+ c.get_x()*(a.get_y()-b.get_y()))/2.0);
	}

  // Funkcija koja proverava da li je Tacka P u unutrasnjosti trougla ABC
	bool is_inside(const Point &a, const Point &b, const Point &c, const Point &p)
	{
	   // Racunamo povrsinu trougla ABC
	   float A = area (a, b, c);

	   // Racunamo povrsinu trougla PBC
	   float A_1 = area (p, b, c);

	   // Racunamo povrsinu trougla PAC
	   float A_2 = area (a, p, c);

	   // Racunamo povrsinu trougla PAB
	   float A_3 = area (a, b, p);

	   // Ako je povrsina manjih trouglova PAB, PBC, PAC jednaka povrsini ABC vracamo true jer je onda tacka P unutar ABC, inace vracamo false
	   return (A == A_1 + A_2 + A_3);
	}

  int orientation(const Point &p, const Point &q, const Point &r)
  {
  	int val = (q.get_y() - p.get_y()) * (r.get_x() - q.get_x()) -
  						(q.get_x() - p.get_x()) * (r.get_y() - q.get_y());

  	if (val == 0)
  		return 0;

  	return (val > 0) ? 1: 2; // clock or counterclock wise
  }

	bool binary_search(Point &p)
	{
		int l = points.size() - 1, r = 1, s;

		Point lp = points[l], rp = points[r];

		Point start = points[0];

		while (abs(l - r) > 1) {
			s = (l + r) / 2;

			if (orientation(start, points[s], p) == 1) {
				lp = points[s];
				l = s;
			}
			else {
				rp = points[s];
				r = s;
			}
		}

		// std::cout << l << " " << r << std::endl;
		return is_inside(start, lp, rp, p);
	}

private:
	std::vector<Point> points;
};

// Tacka u odnosu na koju se vrsi sortiranje svih ostalih tacaka po uglu
Point p_0;

// Funkcija koja trazi ekstremnu tacku u skupu tacaka. Ekstremna tacka je ona koja ima nejvecu x koordinatu, a ako ima vise takvih onda je to ona sa najmanjom
// y koordinatom
int find_extreme_point(std::vector<Point> &points)
{
  int max_x = points[0].get_x(), min_y = points[0].get_y(), index = 0;

  int n = points.size();

  for (int i = 1; i < n; i++) {
    if (points[i].get_x() > max_x) {
      max_x = points[i].get_x();
      min_y = points[i].get_y();
      index = i;
    }
    else if (points[i].get_x() == max_x) {
      if (points[i].get_y() < min_y) {
        min_y = points[i].get_y();
        index = i;
      }
    }
  }

  return index;
}

void swap(Point &p_1, Point &p_2)
{
	Point tmp = p_1;
	p_1 = p_2;
	p_2 = tmp;
}

int orientation(Point p, Point q, Point r)
{
	int val = (q.get_y() - p.get_y()) * (r.get_x() - q.get_x()) -
						(q.get_x() - p.get_x()) * (r.get_y() - q.get_y());

	if (val == 0)
		return 0;

	return (val > 0) ? 1: 2; // clock or counterclock wise
}

// Ne moramo da imamo koren, jer nama ne treba stvarno rastojanje vec samo njihov odnos, pa ako je sqrt(x) < sqrt(y) vazi i x < y
int distance(const Point &p_1, const Point &p_2)
{
    return (p_1.get_x() - p_2.get_x()) * (p_1.get_x() - p_2.get_x()) + (p_1.get_y() - p_2.get_y()) * (p_1.get_y() - p_2.get_y());
}

bool compare(const Point &p_1, const Point &p_2)
{
  // U odnosu na tacku p_0 racunamo sve
  int orient = orientation(p_0, p_1, p_2);

  // Ako je suprotno od kretanja kazaljke na satu, tacka p_1 treba da bude pre p_2 u poretku
  if (orient == 2)
    return true;
  // Ako je u smeru kretanja kazaljke na satu, tacka p_2 treba da bude pre p_1 u poretku
  else if (orient == 1)
    return false;

  // Ako su kolinearne sortiraju se prema udaljenosti od p_0
  return distance(p_0, p_1) < distance(p_0, p_2);
}

Polygon convex_hull(std::vector<Point> &points)
{
  // Odredimo ekstremnu tacku
  int extreme_index = find_extreme_point(points);

  // Stavljamo ekstremnu tacku na poziciju 0
  swap(points[0], points[extreme_index]);

  // Sve tacke sortiramo prema uglu u odnosu na ekstremnu tacku
  p_0 = points[0];

  // Sortiramo po uglu ili po udaljenosti od tacke p_0 ako je ugao isti
  std::sort(points.begin() + 1, points.end(), compare);

  std::vector<Point> result;

  // Dodajemo prve 3 tacke u resenje
  result.push_back(points[0]);
  result.push_back(points[1]);

  int n = points.size();

  int m = 1;

  // Krecemo se kroz ostale tacke
  for (int k = 2; k < n; k++) {
    // Ako naidjemo na neku tacku takvu r takvu da vazi da izmedju poslednje 2 dodate tacke p, q i tacke r vazi orijentacija u smeru kretanja kazaljke na satu,
    // to znaci da poslednje dodatu tacku treba izbaciti iz resenja (za bolje i detaljnije objasnjenje pogledati skriptu profesorke Vesne)
    while (result.size() >= 2 && orientation(result[m - 1], result[m], points[k]) == 1) {
      // Izbacujemo poslednje dodatu tacku
      result.pop_back();
      // Smanjujemo brojac kako bismo se vratili jedno mesto u dosadasnjem omotacu (smanjili smo broj tacaka u omotacu)
      m--;
    }

    // Dodajemo novu tacku u omotac pa uvecavamo brojac koji ih broji
    m++;
    // Dodajemo bas novu tacku do koje smo dosli
    result.push_back(points[k]);
  }

  Polygon p(result);

  return p;
}

int main ()
{
  std::vector<Point> points = { {0, 3}, {1, 1}, {2, 2}, {4, 4}, {0, 0}, {1, 2}, {3, 1}, {3, 3} };

  Polygon p = convex_hull(points);

  Point point (5, 5);

  // std::boolalpha omogucava da ispisujemo true/false umesto 0/1 kada je u pitanju boolean vrednost
  std::cout << std::boolalpha << p.binary_search(point) << "\n";

  return 0;
}
