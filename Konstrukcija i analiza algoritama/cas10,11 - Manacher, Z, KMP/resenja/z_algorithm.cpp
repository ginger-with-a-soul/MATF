#include<iostream>
#include<vector>
using namespace std;

// funkcija koja izracunava sve elemente z-niza
vector<int> izracunajZNiz(const string &s) {
  int n = s.size();
  vector<int> z(n);
  int l = 0;
  int d = 0;

  for (int i = 1; i < n; i++) {
    // ako je tekuca pozicija unutar opsega [l,d]
    // koristimo prethodno izracunatu vrednost za inicijalizaciju
    if (i <= d)
      z[i] = min(d-i+1,z[i-l]);

    // preskacemo proveru karaktera od pozicije i do pozicije z[i];
    // poredimo karakter po karakter u niski i sve dok
    // se karakteri poklapaju povecavamo vrednost z[i]
    while (i+z[i] < n && s[z[i]] == s[i+z[i]])
      z[i]++;

    // ako je nova vrednost desnog kraja intervala poklapanja
    // veca od prethodne vrednosti, azuriramo interval [l,d]
    if (i+z[i]-1 > d) {
      l = i;
      d = i+z[i]-1;
    }
  }

  return z;
}

int main(){
  string niz="CDA#ACBACDACBACBACDA";
  int n=niz.size();
  vector<int> zNiz = izracunajZNiz(niz);
    
  for (int i=0; i<n; i++) {
    if (zNiz[i] == 3)
      cout << i - 4 << "\n";
  }

  return 0;
}
