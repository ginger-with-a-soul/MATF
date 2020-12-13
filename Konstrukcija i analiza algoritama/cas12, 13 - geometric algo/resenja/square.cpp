#include <iostream>
#include <vector>
#include <algorithm>

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

  void set_x(int x) { this->x = x; }
  void set_y(int y) { this->y = y; }

private:
  int x;
  int y;
};

bool compare(const Point &p_1, const Point &p_2)
{
  if (p_1.get_x() == p_2.get_x()) {
    return p_1.get_y() < p_2.get_y();
  }

  return p_1.get_x() < p_2.get_x();
}

std::ostream &operator<<(std::ostream &out, Point &p)
{
  out << p.get_x() << " " << p.get_y() << " ";
  return out;
}

// Funkcija koja odredjuje koordinate potencijalnih temena kvadrata ako imamo temena A i B
// Za vise informacija o formuli posetite
// https://math.stackexchange.com/questions/964625/find-3rd-and-4th-co-ordinates-for-a-square-given-co-ordinates-of-two-points
void find_coordinates (const Point &a, const Point &b, Point &c, Point &c_1, Point &d, Point &d_1)
{
  int delta_x = b.get_x() - a.get_x();
  int delta_y = b.get_y() - a.get_y();

  c.set_x(b.get_x() + delta_y);
  c_1.set_x(b.get_x() - delta_y);

  c.set_y(b.get_y() - delta_x);
  c_1.set_y(b.get_y() + delta_x);

  d.set_x(a.get_x() + delta_y);
  d_1.set_x(a.get_x() - delta_y);

  d.set_y(a.get_y() - delta_x);
  d_1.set_y(a.get_y() + delta_x);
}

bool check_for_vertices (std::vector<Point> &points, const Point &c, const Point &c_1, const Point &d, const Point &d_1)
{
  return (std::binary_search(points.begin(), points.end(), c, compare) && std::binary_search(points.begin(), points.end(), d, compare)) ||
         (std::binary_search(points.begin(), points.end(), c_1, compare) && std::binary_search(points.begin(), points.end(), d_1, compare));
}

bool is_there_square(std::vector<Point> &points)
{
  // Sortiramo tacke rastuce po x (pa ako ima vise sa istom x koordinatom onda po y koordinati)
  std::sort(points.begin(), points.end(), compare);

  int n = points.size();

  // Preostala temena potencijalnog kvadrata, mozemo imati 2 kvadrata cija su 2 temena A i B
  Point c, d, c_1, d_1;

  // Idemo kroz sve parove tacaka (ne racunamo tacku i nju samo kao par)
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {

      if (i == j)
        continue;

      // Odredjujemo koordinate potencijalnih preostalih temena
      find_coordinates(points[i], points[j], c, c_1, d, d_1);

      // Ako postoje tacke sa odgovarajucim temenima u skupu tacaka samo vracamo true kao indikator da postoje 4 tacke koje formiraju kvadrat
      if (check_for_vertices(points, c, c_1, d, d_1))
        return true;
    }
  }

  // Ako smo prosli kroz sve parove i nismo nasli 4 tacke koje formiraju kvadrat, vracamo false
  return false;
}

int main ()
{
  // {2, 0}, {1, 1}, {8, 19}, {2, 14}

  std::vector<Point> points = { {0, 3}, {2, 2}, {6, 4}, {1, 1}, {2, 1}, {2, 5}, {3, 0}, {0, 0}, {3, 3} };

  // std::boolalpha omogucava da ispisujemo true/false umesto 0/1 kada je u pitanju boolean vrednost
  std::cout << std::boolalpha << is_there_square(points) << "\n";

  return 0;
}
