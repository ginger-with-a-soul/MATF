#include <stdio.h>
#include <stdlib.h>
#include "tokeni.h"

#define ISPIS 1

void error(const char* userMsg){
	fprintf(stderr, "%s\n", userMsg);
	exit(EXIT_FAILURE);
}

void ispis(const char* ispis){
	fprintf(stdout, "%s\n", ispis);
}

int yyval;
int next;
extern int yylex();

int E();
int EP();
int T();
int TP();
int F();

int main(){
	next = yylex();
	int rez = E();
	if(next != EOI){
		error("Semanticka greska");
	}
	else{
		printf("Rezultat: %i\n", rez);
	}
	exit(EXIT_SUCCESS);
}

int E(){
	if(next == NUM || next == OZ){
		ispis("E -> TE'");
		return T() + EP();
	}
	else{
		error("Ocekivano: NUM ili OZ");
	}
	return -1;
}

int EP(){
	if(next == PLUS){
		ispis("E'-> +TE'");
		next = yylex();
		return T() + EP();
	}
	else if(next == ZZ || next == EOI){
		ispis("E'-> eps");
		return 0;
	}
	else{
		error("Ocekivano: PLUS, ZZ ili EOI");
	}
	return -1;
}

int T(){
	if(next == OZ || next == NUM){
		ispis("T -> FT'");
		return F() * TP();
	}
	else{
		error("Ocekivano: OZ ili NUM");
	}
	return -1;
}

int TP(){
	if(next == PUTA){
		ispis("T'-> *FT'");
		next = yylex();
		return F() * TP();
	}
	else if(next == PLUS || next == ZZ || next == EOI){
		ispis("T'-> eps");
		return 1;
	}
	else{
		error("Ocekivano: PUTA, PLUS, ZZ ili EOI");
	}
	return -1;
}

int F(){
	if(next == OZ){
		ispis("F -> (E)");
		next = yylex();
		int tmp = E();
		if(next == ZZ){
			next = yylex();
		}
		else{
			error("Ocekivano: OZ");
		}
		return tmp;
	}
	else if(next == NUM){
		ispis("F -> NUM");
		next = yylex();
		return yyval;
	}
	else{
		error("Ocekivano: OZ");
	}
	return -1;
}