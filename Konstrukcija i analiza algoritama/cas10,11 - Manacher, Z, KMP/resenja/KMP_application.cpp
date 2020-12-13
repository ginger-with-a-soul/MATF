#include <string>
#include <iostream>
#include <vector>
#include <algorithm>

// Funkcija koja na osnovu uzorka pattern racuna preffix_table niz
void compute_preffix_table(std::string &pattern, std::vector<int> &preffix_table)
{
  int n = pattern.size();

  preffix_table[0] = 0;

  // Indeks i je indeks koji ide kroz nisku, a indeks j ce zapravo sluziti da kaze kolika je duzina prefiksa i sufiksa koji se poklapaju
  int i = 1, j = 0;

  // Krecemo se kroz nisku
  while (i < n) {
    // Ukoliko poklopimo odgovarajuca 2 karaktera, potrebno je da na poziciju i smestimo j + 1 sto nam zapravo kaze kolika je duzina sufiksa niske
    // pattern[0-i] koji se poklapa sa prefiksom reci, tj kaze nam od koje pozicije u niski text nastavljamo pretragu ako nema poklapanja teksta i uzorka
    // na nekoj poziciji. Ako smo nasli poklapanje uvecavamo oba indeksa
    if (pattern[i] == pattern[j]) {
      preffix_table[i] = j + 1;
      i++;
      j++;
    }
    // Ako nema poklapanja na pozicijama i i j
    else {
      // Ako nismo na pocetku niske menjamo vrednost indeksa na LSP[j - 1]
      if (j != 0)
        j = preffix_table[j - 1];
      // Ako smo dosli na pocetak, na LSP[i] stavljamo 0 jer nemamo nikakav prefiks koji je i sufiks, i uvecavamo i
      else {
        preffix_table[i] = 0;
        i++;
      }
    }
  }

  for (char c : pattern)
    std::cout << c << " ";
  std::cout << "\n";


  for (int x : preffix_table)
    std::cout << x << " ";
  std::cout << "\n";
}

// Funkcija koja dodaje minimalan broj karaktera na nisku s i od nje pravi palindrom. Vraca rezultujucu nisku
std::string change_string(std::string &s)
{
  // Pravimo novu nisku koju cemo obrnuti, i jos jednu koja ce biti ista kao originalna niska
  std::string pom = s, pom_1 = pom;

  // Obrcemo nisku pom
  std::reverse(pom.begin(), pom.end());

  // Stavljamo specijalan karakter na pom_1, i nadovezujemo pom
  pom_1 += "#";

  pom_1 += pom;

  // Racunamo novu velicinu niske pom_1
  int n = pom_1.size();

  // Kreiramo prefiksnu tabelu velicine n
  std::vector<int> preffix_table(n);

  // Izracunavamo prefiksnu tabelu
  compute_preffix_table(pom_1, preffix_table);

  // Uzimamo odgovarajuci sufiks niske s koji treba da nadovezemo na pocetak
  std::string suffix = s.substr(preffix_table[n - 1]);
  // Obrcemo sufiks jer kao takav treba da bude nadovezan na pocetak niske
  std::reverse(suffix.begin(), suffix.end());

  // Nadovezujemo s na sufiks
  suffix += s;

  // Vracamo izmenjeni sufiks
  return suffix;
}

int main ()
{
  std::string s = "aacaaa";

  std::cout << change_string(s) << "\n";

  return 0;
}
