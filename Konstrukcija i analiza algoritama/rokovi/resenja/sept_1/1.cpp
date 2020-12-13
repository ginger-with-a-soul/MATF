#include <iostream>
#include <vector>
#include <cmath>

void build_segment_tree (std::vector<int> &array, std::vector<int> &segment_tree, int k, int x, int y, int pom)
{
  if (x == y) {
    segment_tree[k] = array[x];
    return;
  }

  int middle = (x + y) / 2;

  build_segment_tree(array, segment_tree, 2 * k, x, middle, pom ^ 1);
  build_segment_tree(array, segment_tree, 2 * k + 1, middle + 1, y, pom ^ 1);

  if (pom)
     segment_tree[k] = segment_tree[2 * k] | segment_tree[2 * k + 1];
  else
     segment_tree[k] = segment_tree[2 * k] ^ segment_tree[2 * k + 1];
}

void update_tree(std::vector<int> &segment_tree, int k, int x, int y, int index, int new_value, int pom)
{
  if (x == y) {
    segment_tree[k] = new_value;
    return ;
  }

  int middle = (x + y) / 2;

  if (index <= middle)
    update_tree(segment_tree, 2 * k, x, middle, index, new_value, pom ^ 1);
  else
    update_tree(segment_tree, 2 * k + 1, middle + 1, y, index, new_value, pom ^ 1);

  if (pom)
    segment_tree[k] = segment_tree[2 * k] | segment_tree[2 * k + 1];
  else
    segment_tree[k] = segment_tree[2 * k] ^ segment_tree[2 * k + 1];
}

int main ()
{
  int n, m, x, y;

  std::cin >> n >> m;

  int nn = pow(2, n);

  int height = ceil(log2(nn));

  int size = 2 * pow(2, height);

  std::vector<int> array;

  std::vector<std::pair<int, int>> queries;

  for (int i = 0; i < nn; i++) {
    scanf("%d", &x);
    array.push_back(x);
  }

  for (int i = 0; i < m; i++) {
    scanf("%d%d", &x, &y);
    queries.push_back({x - 1, y});
  }

  std::vector<int> segment_tree(size);

  build_segment_tree(array, segment_tree, 1, 0, nn - 1, n % 2);

  for (std::pair<int, int> &p : queries) {
    update_tree(segment_tree, 1, 0, nn - 1, p.first, p.second, n % 2);
    printf("%d\n", segment_tree[1]);
  }

  return 0;
}