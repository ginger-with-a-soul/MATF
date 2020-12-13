/*
Manacher-ov algoritam koristi se za odredjivanje najduzeg palindroma unutar nase niske.
Palindromi su simetricni u odnosu na centar.

Manacher-ov algoritam slican je Z-algoritmu. Radi na principu mirroring-a. Da bi Manacher-ov
algoritam funkcionisao, neophodno je da imamo 3 specijalna karaktera koji se nece javiti
u nasem potencijalnom palindromu. Prvi specijalni karakter oznacava pocetak, nakon njega ide
specijalni karakter koji odvaja slova, a na kraju ide specijalni karakter koji je razlicit od
ova dva i on oznacava kraj.

Prvo je potrebno da transformisemo nasu nisku tako da bude validna za Manacher-ov algoritam.
Na primer, niska "abba" -> $#a#b#b#a#@
Nakon toga, krecemo od elementa sa indeksom 1 jer je na 0. mestu @. Za svaki element i racunamo
njegovog parnjaka i to po formuli parnjak = centar * 2 - i. Nakon toga proveravamo da li se 
nalazimu u okviru nase desne granice, ako se nalazimo onda biramo manji element od 
desne granice - i ili one vrednosti koja pise u nasem parnjaku. Time garantujemo da necemo izaci
van desne granice jer tu ne znamo koji su karakteri. Ako se ne nalazimo to znaci da nismo unutar
veceg palindroma. Nakon toga se vracamo na linearno trazenje 
da li palindrom odatle mozemo da prosirimo i to tako sto prvo preskocimo tu vrednost koja je 
trenutno upisana na nasem indeksu i levo i desno a tek onda krenemo da pokusavamo da poklapamo.
Ako nam se dogodi da premasimo desnu granicu, onda centar postoje nasa pozicija i a desna granica
ide na vrednosti u i + i.
*/
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

void manacher(std::string &s){
	std::string tmp = "$#";
	int n = s.size();

	for(int i = 0; i < n; i++){
		tmp += s[i];
		tmp += '#';
	}
	tmp += '@';

	int C = 1, R = 1;
	
	int size = tmp.size();
	std::vector<int> mirror(size);
	int pair;

	for(int i = 1; i < size - 1; i++){
		pair = 2 * C - i;

		if(i < R){
			mirror[i] = std::min(R - i, mirror[pair]);
		}

		while(tmp[i + (mirror[i] + 1)] == tmp[i - (mirror[i] + 1)]){
			mirror[i]++;
		}

		if(i + mirror[i] > R){
			C = i;
			R = i + mirror[i];
		}
	}

	int max_position = std::max_element(mirror.begin(), mirror.end()) - mirror.begin();
  	int max = mirror[max_position];

  	// Rekonstruisemo string na osnovu duzine i pozicije centra, nalazimo pocetak i kraj, tj prvi i poslednji karakter koji pripadaju najduzoj palindromskoj
  	// podnisci
  	int start = max_position - max + 1;
	int end = start + 2 * max;
  	std::string result = "";

  	

  	// Uzimamo svaki drugi karakter zbog #
  	for (int i = start; i < end; i += 2)
  	  result += tmp[i];

  	std::cout << result << std::endl;
}

int main(int argc, char** argv){

	std::string s;
	std::cin >> s;

	manacher(s);

	exit(EXIT_SUCCESS);
}