#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

class Point
{
public:
  Point () {}

  Point (double _x, double _y)
  {
    x = _x;
    y = _y;
  }

  double get_x() const { return x; }
  double get_y() const { return y; }

  void set_x(double x) { this->x = x; }
  void set_y(double y) { this->y = y; }

private:
  double x;
  double y;
};

bool compare(const Point &p_1, const Point &p_2)
{
  if ((int)p_1.get_x() * 100 == (int)p_2.get_x() * 100) {
    return (int)p_1.get_y() * 100 < (int)p_2.get_y() * 100;
  }

  return (int)p_1.get_x() * 100 < (int)p_2.get_x() * 100;
}

std::ostream &operator<<(std::ostream &out, Point &p)
{
  out << p.get_x() << " " << p.get_y() << " ";
  return out;
}

int max_triangles(std::vector<Point> &points)
{
  std::sort(points.begin(), points.end(), compare);

  int n = points.size();

  double third_x, third_y;

  int counter = 0;

  Point c;

  double side;

  for (int i = 0; i < n; i++) {
  	for (int j = i + 1; j < n; j++) {
  		if ((int)points[i].get_x() * 100 == (int)points[j].get_x() * 100) {
  			side = std::abs(points[i].get_y() - points[j].get_y());

  			third_y = (points[i].get_y() + points[j].get_y()) / 2.0;
  			third_x = points[i].get_x() + side * sqrt(3) / 2.0;

  			c.set_x(third_x);
  			c.set_y(third_y);

  			if (std::binary_search(points.begin(), points.end(), c, compare))
  				counter++;

			third_x = points[i].get_x() - side * sqrt(3) / 2.0;
  			
  			c.set_x(third_x);
  			c.set_y(third_y);

  			if (std::binary_search(points.begin(), points.end(), c, compare))
  				counter++;
  		}
  		else if ((int)points[i].get_y() * 100 == (int)points[j].get_y() * 100) {
			side = std::abs(points[i].get_x() - points[j].get_x());

  			third_x = (points[i].get_x() + points[j].get_x()) / 2.0;
  			third_y = points[i].get_y() + side * sqrt(3) / 2.0;

  			c.set_x(third_x);
  			c.set_y(third_y);

  			if (std::binary_search(points.begin(), points.end(), c, compare))
  				counter++;

			third_y = points[i].get_y() - side * sqrt(3) / 2.0;
  			
  			c.set_x(third_x);
  			c.set_y(third_y);

  			if (std::binary_search(points.begin(), points.end(), c, compare))
  				counter++;
  		}
  	}
  }

  return counter;
}

int main ()
{
  std::vector<Point> points;

  double x, y;

  int n;

  std::cin >> n;

  for (int i = 0; i < n; i++) {
    std::cin >> x >> y;
    points.push_back({x, y});
  }

  std::cout << max_triangles(points) << "\n";
  
  return 0;
}
