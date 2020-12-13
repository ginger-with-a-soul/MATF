#include <iostream>
#include <queue>
#include <vector>
#include<bits/stdc++.h>
#include <algorithm>

// Struktura koja predstavlja cvor strukture min-heap
// Struktura ima 3 podatka, vrednost elementa, redni broj liste u kojoj se nalazi i poziciju u listi
struct Node
{
  // Vrednost elementa
	int value;
  // Redni broj liste
  int list_num;
  // Pozicija u listi
  int index;
};

// Definisemo komparator
struct comp {
	bool operator()(const Node &node1, const Node &node2) const
	{
		return node1.value > node2.value;
	}
};

std::pair<int, int> findMinimumRange(std::vector<int> list[], int M)
{
  // Najveci element na pocetku je INT_MIN, njega ce "svaki" drugi broj pregaziti
  int high = INT_MIN;

  // Trenutna najveca razlika, odnosno interval koji cuvamo, od nje ce "svaka" razlika biti manja
	std::pair<int,int> p = { 0, INT_MAX };

  // Kreiramo min-heap
  std::priority_queue<Node, std::vector<Node>, comp> heap;

  for (int i = 0; i < M; i++)
	{
    // Stavljamo u heap minimalni (prvi) element svake od listi
		heap.push({list[i][0], i, 0});
    // Azuriramo najveci element koji se do sad javio, to je najveci od prvih (najmanjih) elemenata listi
		high = std::max(high, list[i][0]);
	}

  Node tmp;

	while (1)
	{
		// Uzimamo element sa vrha heap-a. Kako koristimo min-heap on ce biti najmanji element koji se trenutno nalazi u njemu. Uzimamo i redni broj liste u kojoj se nalazi, kao i indeks
    // u samoj listi
    tmp = heap.top();
    int low = tmp.value;
		int list_num = tmp.list_num;
		int index = tmp.index;

		// Izbacujemo element iz heap-a
		heap.pop();

		// Proveravamo da li je novi interval manji od prethodno najmanjeg koji smo nasli
		if (high - low < p.second - p.first) {
      // Ukoliko jeste, azuriramo interval
      p = {low, high};
		}

		// Ukoliko smo dosli do kraja neke liste, vracamo minimalni interval koji je nadjen
		if (index == list[list_num].size() - 1) {
			return p;
		}

    // U min-heap stavljamo naredni element iz liste u kojoj se nalazio poslednji element koji je izbacen. Dakle, nakon izbacivanja nekog elementa, zelimo da napredujemo u toj listi
		heap.push({list[list_num][index + 1], list_num, index + 1});

		// Azuriramo maksimalni element ukoliko ima potrebe za tim
		high = std::max(high, list[list_num][index + 1]);
	}
}

// main function
int main()
{
	std::vector<int> list[] =
	{
		{ 3, 6, 8, 10, 15 },
		{ 1, 5, 12 },
		{ 4, 8, 15, 16},
		{ 2, 6 }
	};

	const size_t M = sizeof(list) / sizeof(list[0]);

	std::pair<int, int> p = findMinimumRange(list, M);
	std::cout << "Minimum range is " << p.first << "-" << p.second << "\n";

	return 0;
}
