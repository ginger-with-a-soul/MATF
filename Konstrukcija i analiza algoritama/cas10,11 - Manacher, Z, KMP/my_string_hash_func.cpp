/*
Kad hesiramo stringove, biramo dva broja - prvi prost broj veci od broja mogucih
ulaza u nasu hash f-ju (ako hesiramo samo mala slova engleskog alfabeta, postoji 26
mogucih slova - ulaza). Drugi broj treba da bude sto veci prost broj. Prvim brojem
mnozimo nasu hash vrednost a drugim brojem radimo moduo od svega.

Kada obradjujemo string, krenemo od njegovog kraja, nasu hash vrednost u svakom koraku
mnozimo sa prvim brojem i to saberemo sa ascii vrednoscu naseg trenutnog slova + 1. Na
kraju uradimo moduo od svega
*/

#include <iostream>
#include <string>

long long string_hash(std::string &s){
	int p = 29;
	int m = 1e9 + 9;
	long long hash_value = 0;

	for(int i = s.size() - 1; i >= 0; i--){
		hash_value = (hash_value * p + (s[i] - 'a' + 1)) % m;
	}

	return hash_value;
}

int main(int argc, char** argv){

	std::string s;
	std::cin >> s;

	std::cout << string_hash(s) << std::endl;

	exit(EXIT_SUCCESS);
}