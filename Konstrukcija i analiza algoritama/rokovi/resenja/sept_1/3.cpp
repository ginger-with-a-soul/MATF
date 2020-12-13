#include <iostream>
#include <vector>

int main ()
{
  long long x, y;

  std::cin >> x >> y;

  long long n = x - y + 1;

  n--;

  long long max = (n * (n + 1)) / 2;

  long long i = 0;

  long long sigurno = x / y;

  long long min = 0;

  sigurno--;

  long long pom = (sigurno * (sigurno + 1)) / 2;

  min += pom * y;

  pom = x % y;

  if (pom != 0) {

    long long tmp = x / y;

    min += pom * tmp;
  }

  std::cout << min << " " << max << "\n";

  return 0;
}
