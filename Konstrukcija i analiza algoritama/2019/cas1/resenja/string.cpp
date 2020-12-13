#include<iostream>
#include<unordered_map>
#include<map>
#include<vector>
#include<queue>

void first_k_non_epeating(std::string str, int k)
{
  // Mapa u koju smestamo karakter, broj pojavljivannja, i poslendje pojavljivanje karaktera
  std::map<char, std::pair<int, int>> map;

  for (int i = 0 ; i < str.length(); i++)
  {
    map[str[i]].first++;
    map[str[i]].second = i;
  }

  // Pravimo min-heap
  std::priority_queue<int, std::vector<int>, std::greater<int>> heap;

  // Prolazimo kroz mapu i za sve one elemente koji se javljaju samo jednom smestamo u heap njihovo poslednje pojavljivanje (za njih je to ujedno prvo i jedino pojavljivanje)
  for (auto it : map)
  {
    int count = it.second.first;
    int index = it.second.second;

    if (count == 1) {
      heap.push(index);
    }
  }

  // Uzimamo prvih k elemenata heap-a ukoliko ih ima k
  while (k-- && !heap.empty())
  {
    // Uzimamo poslednji element, pisemo karakter koji se u originalnoj nisci nalazi na toj poziciji i skidamo element sa heap-a
    int min_index = heap.top();
    heap.pop();

    std::cout << str[min_index] << " ";
  }
}

int main()
{
	std::string str = "ABCDBAGHCHFAC";
	int k = 3;

	first_k_non_epeating(str, k);

  std::cout << "\n";
	return 0;
}
