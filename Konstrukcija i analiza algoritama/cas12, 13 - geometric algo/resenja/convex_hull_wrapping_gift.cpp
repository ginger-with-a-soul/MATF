#include <iostream>
#include <vector>
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

  bool operator !=(const Point &p)
  {
    return this->x != p.x || this->y != p.y;
  }

  bool operator ==(const Point &p)
  {
    return this->x == p.x && this->y == p.y;
  }

private:
  int x;
  int y;
};

// Funkcija koja trazi ekstremnu tacku u skupu tacaka. Ekstremna tacka je ona koja ima najvecu x koordinatu, a ako ima vise takvih onda je to ona sa najmanjom
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

// Po formuli a*b = |a| * |b| * cos(phi) racunamo vrednost ugla izmedju 2 vektora (prave)
float angle_between_lines (const Point &p_1, const Point &p_2, const Point &p_3, const Point &p_4)
{
  int v_1_x = p_2.get_x() - p_1.get_x();
  int v_1_y = p_2.get_y() - p_1.get_y();
  int v_2_x = p_4.get_x() - p_3.get_x();
  int v_2_y = p_4.get_y() - p_3.get_y();

  int scalar = v_1_x * v_2_x + v_1_y * v_2_y;

  return acos(scalar / (sqrt(v_1_x * v_1_x + v_1_y * v_1_y) * sqrt(v_2_x * v_2_x + v_2_y * v_2_y)));
}

void swap(Point &p1, Point &p2)
{
	Point tmp = p1;
	p1 = p2;
	p2 = tmp;
}

void convex_hull(std::vector<Point> &points)
{
  // Odredimo ekstremnu tacku
  int extreme_index = find_extreme_point(points);

  std::vector<Point> result;

  // Stavljamo ekstremnu tacku na poziciju 0
  swap(points[0], points[extreme_index]);

  // Tacka p je tacka u odnosu na koju racunamo uglove, a tacka extreme_point ce nam sluziti da znamo kada smo dosli do pocetne tacke ponovo, tj kada
  // smo zavrsili sa kreiranjem konveksnog omotaca
  Point p = points[0], extreme_point = p;

  // Tacke l_0 i l_1 sluze kao tacke koje odredjuju pravu L (iz algoritma kod profesorke u skripti). Posto je prava koja nam treba na pocetku paralelna sa
  // X osom, uzimamo bilo koju tacku koja ima istu y koordinatu kao i tacka p
  Point l_0 = p, l_1 {p.get_x() + 2, p.get_y()};

  int n = points.size();

  float min_angle, angle;

  int min_angle_index;

  do {
    // Postavljamo minimalni ugao na nesto vece od pi, jer cemo vrednost dobiti u radijanima, najvise pi
    min_angle = 5.0;

    // Dodajemo tacku koju trenutno razmatramo u resenje
    result.push_back(p);

    // Idemo kroz sve tacke i zaobilazimo tacku koju trenutno razmatramo, tj prolazimo kroz ostale tacke i racunamo koja je tacka q za koju vazi da je ugao
    // izmedju prave L i prave -p-q minimalan. Pamtimo njen indeks
    for (int i = 0; i < n; i++) {
      if (p == points[i])
        continue;

      // Racunamo ugao izmedju prave L i svake prave oblika -p-tacka, gde je p poslednja dodata tacka u konveksni omotac, a tacka element svih ostalih
      // tacaka iz skupa
      angle = angle_between_lines(l_0, l_1, p, points[i]);

      if (angle < min_angle && angle != 0.0) {
        min_angle_index = i;
        min_angle = angle;
      }
    }

    // Nova prava prolazi kroz staru tacku p i novu tacku p
    l_0 = p;
    // Azuriramo tacku p
    p = points[min_angle_index];
    l_1 = p;
  } while (p != extreme_point);

  for (Point &p : result)
    std::cout << p.get_x() << " " << p.get_y() << "\n";
}

int main ()
{
  std::vector<Point> points = { {0, 0}, {12, 2}, {9, 3}, {8, 7}, {5, 3}, {3, 6}, {1, 4}, {14, 0} };

  convex_hull(points);

  return 0;
}