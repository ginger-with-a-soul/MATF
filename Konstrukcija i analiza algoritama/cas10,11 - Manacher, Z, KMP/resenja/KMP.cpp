#include <string>
#include <iostream>
#include <vector>

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

// Funkcija KMP koja implementira KMP algoritam. Kao argumente dobija string koji predstavlja text i string koji predstavlja uzorak koji se trazi
void KMP(std::string &text, std::string &pattern)
{
  // Racunamo duzinu teksta kao i uzorka koji se trazi
  int m = text.size();
  int n = pattern.size();

  // Kreiramo LSP niz, njegova duzina je n jer je usko povezan sa samim uzorkom koji se trazi cija je duzina n
  std::vector<int> preffix_table(n);

  compute_preffix_table(pattern, preffix_table);

  // Indeksi koji se krecu kroz tekst (i) i uzorak (j)
  int i = 0, j = 0;

  // Idemo kroz ceo tekst
  while (i < m) {
    // Dok god mozemo da poklopimo karaktere, to i radimo, i samo uvecavamo indekse kako bismo se kretali kroz tekst i uzorak
    if (text[i] == pattern[j]) {
      i++;
      j++;
    }

    if (j == n) {
      std::cout << "Pattern found! :)\n";
      return ;
    }

    // Ako nismo prekoracili duzinu teksta (moze da se desi jer gore uvecavamo indeks i) i ako se odgovarajuci karakteri ne poklapaju, premestamo indeks i
    // koji se krece kroz tekst da dodje bas na poziciju preffix_table[j - 1], jer znamo da odatle treba krenuti u dalje poklapanje zato sto je sve pre toga vec
    // poklopljeno (sufiks je isti kao prefiks)
    if (i < m && pattern[j] != text[i]) {
      // Ako se nismo vratili na pocetak teksta azuriramo indeks j i gledamo odakle uporedjujemo dalje
      if (j != 0)
        j = preffix_table[j - 1];
      // Ako smo se vratili na pocetak teksta i nema poklapanja idemo dalje kroz tekst
      else
        i++;
    }
  }

  std::cout << "Pattern not found! :(\n";
}


int main ()
{
  std::string text = "abcabcabcabcabcabcabcd";

  std::string pattern = "abcabcabcd";

  KMP(text, pattern);

  return 0;
}
