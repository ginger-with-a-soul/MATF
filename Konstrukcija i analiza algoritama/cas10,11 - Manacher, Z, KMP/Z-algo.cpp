/*
Z-algoritam sluzi za pronalazenje svih pozicija zeljene niske u tekstu.
Da bismo koristili Z-algoritam, prvo moramo da odredimo Z-tabelu. Z-tabela nam
govori za svaku poziciju i kolika je vrednost prefiksa koji pocinje na toj poziciji.

0 1 2 3 4 5 6 7 8 9 10
a b c d x a b c d x f

Ako gledamo poziciju 5 onda je vrednost prefiksa 4 jer se poklapaju a b c d
Ako gledamo poziciju 6 onda je vrednost 0 jer se ne poklapa a na poziciji 0 i b na poziciji
6
Prvi indeks nam nije vazan pa je 0

0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18
a a b x a a	b x c a a  b  x  a  a  b  x  a  y
----------------------------------------------
0 1 0 0 4 1 0 0 0 8 1  0  0  5  1  0  0  1  0  --> Z-niz

Naivan nacin je da za svaku slovo krenemo od pocetka i poredimo - O(n^2)

Bolji nacin je, da kada dobijemo prvo poklapanje vece od 1 (na poziciji 4 na primer), samo
prepisemo za sve ostale posle 1. vec izracunate vrednosti (Z-kutija). Za sve sto je van Z-kutije
moramo rucno.
VAZNO! Moze da se dogodi da negde ne smemo tek tako da prepisemo vrednosti. To se desava kada
vrednost u nekom indeksu koji zelimo da prepisemo + vrednost na indeksu gde to zelimo da upisemo
izadju van granica kutije (van opsega koji je odredjen prvim tekucim poklapanjem koje je vece
od 1). U nasem slucaju, to se desava kada kutija pocinje na poziciji 9. Ona obuhvata 8 mesta ->
proteze se do indeksa 17 ali bez njega. Kada dodjemo do indeksa 13, ako bismo samo prepisivali
dobili bismo vrednost 4. Medjutim, 13 + 4 je 17 a to je prvi clan van nase kutije. Zbog toga
moramo da poredimo taj clan sa prvim clanom posle onog indeksa koji nam je sugerisao da upisemo
vrednost 4. Vidimo da se poklapaju (a i a, ali da se posle toga ne poklapaju sledeci b i y). Zbog
toga, upisujemo vrednost 5 a ne 4. Posto je vrednost koju sada upisujemo veca od 1, i nasa kutija se
pomera. Ako imamo neki zbir (vrednost koja je sugerisana da bude prepisana + trenutno indeks gde
treba da je prepisemo) takav da izlazi van granice naseg niza, onda taj ostatak indeksa u kutiji 
racunamo kao desna granica - indeks + 1. Svaki put kad se karakter nalazi desno od desne granice
kutije, moramo trivilanim pristupom.
*/


#include <iostream>
#include <string>
#include <vector>

std::vector<int> find_Z_array(std::string haystack){
	int l = 0, d = 0;
	int n = haystack.size();
	std::vector<int> Z_array(n);

	for(int i = 1; i < n; i++){
		if(i <= d){
			Z_array[i] = std::min(Z_array[i - l], d - i + 1);
		}

		while(i + Z_array[i] < n && haystack[Z_array[i]] == haystack[Z_array[i] + i]){
			Z_array[i]++;
		}

		if(i + Z_array[i] - 1 > d){
			l = i;
			d = i + Z_array[i] - 1;
		}
	}
	return Z_array;
}

int main(int argc, char** argv){

	std::string needle, haystack;
	std::cin >> needle >> haystack;
	
	haystack = needle + '#' + haystack;
	
	std::vector<int> Z_array = find_Z_array(haystack);

	int needle_size = needle.size();
	int haystack_size = haystack.size();

	for(int i = 0; i < haystack_size; i++){
		if(Z_array[i] == needle_size){
			std::cout << i - needle_size - 1 << std::endl;
		}
	}

	exit(EXIT_SUCCESS);
}