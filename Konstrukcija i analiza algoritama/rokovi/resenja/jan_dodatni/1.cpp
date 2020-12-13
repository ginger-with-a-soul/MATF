#include <iostream>
#include <unordered_map>
using namespace std;

struct Cvor {
  unordered_map<char, Cvor*> grane;
};

Cvor* napravi(const string& s, size_t i) {
  if (i == s.size())
    return nullptr;
  Cvor* c = new Cvor();
  c->grane[s[i]] = napravi(s, i+1);
  return c;
}

bool ubaci(Cvor* cvor, const string& s, size_t i) {
  if (i == s.size() || cvor == nullptr)
    return false;
  auto it = cvor->grane.find(s[i]);
  if (it == cvor->grane.end()) {
    cvor->grane[s[i]] = napravi(s, i+1);
    return true;
  } else
    return ubaci(it->second, s, i+1);
}

void obrisi(Cvor* cvor) {
  if (cvor != nullptr) {
    for (auto it : cvor->grane)
      obrisi(it.second);
    delete cvor;
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  int n;
  cin >> n;
  bool OK = true;
  string broj;
  cin >> broj;
  Cvor* koren = napravi(broj, 0);
  for (int i = 1; i < n; i++) {
    cin >> broj;
    if (OK && !ubaci(koren, broj, 0))
      OK = false;
  }
  if (OK)
    cout << "DA" << endl;
  else
    cout << "NE" << endl;
  obrisi(koren);
  
  return 0;
}
