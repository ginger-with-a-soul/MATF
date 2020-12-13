#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

void ispis(const char* msg){
	printf("%s\n", msg);
}

void error(const char* userMsg){
	perror(userMsg);
	exit(EXIT_FAILURE);
}

#define ISPIS 1
#define EOI 0
#define NUM 1
#define OZ 2
#define ZZ 3
#define PLUS 4
#define PUTA 5

void E();
void EP();
void T();
void TP();
void F();

int next;
int yyval;

int yylex(){
	char ch = getchar();
	switch(ch){
		case '+': return PLUS;
		case '*': return PUTA;
		case '(': return OZ;
		case ')': return ZZ;
		case '\n': case EOF: return EOI;
	}

	if(isdigit(ch)){
		yyval = ch - '0';
		while(isidigit(ch = getchar())){
			yyval = yyval*10 + ch - '0';
		}
		ungetc(ch, stdin);
		return NUM;
	}
	error("Nepodrzana leksema!");
	return -1;
}

int main(){
	next = yylex();
	E();
	if(next != EOI){
		error("Semanticka greska!");
	}
	exit(EXIT_SUCCESS);
}

void E(){
	if(next == NUM || next == OZ){
		if(ISPIS){
			ispis("E -> TE'");
		}
		T();
		EP();
	}
	else{
		error("Ocekivano: NUM ili OZ");
	}
}

void EP(){
	if(next == PLUS){
		if(ISPIS){
			ispis("E'-> +TE'");
		}
		next = yylex();
		T();
		printf("+");
		EP();
	}
	else if(next == ZZ || next == EOI){
		if(ISPIS){
			ispis("E'-> eps");
		}
	}
	else{
		error("Ocekivano: PLUS, ZZ ili EOI");
	}
}

void T(){
	if(next == OZ || next == NUM){
		if(ISPIS){
			ispis("T -> FT'");
		}
		F();
		TP();
	}
	else{
		error("Ocekivano: OZ ili NUM");
	}
}

void TP(){
	if(next == PUTA){
		if(ISPIS){
			ispis("T'-> *FT'");
		}
		next = yylex();
		F();
		printf("*");
		TP();
	}
	else if(next == PLUS || next == ZZ || next == EOI){
		if(ISPIS){
			ispis("T'-> eps");
		}
		return;
	}
	else{
		error("Ocekivano: PUTA, PLUS, ZZ ili EOI");
	}
}

void F(){
	if(next == OZ){
		if(ISPIS){
			ispis("F -> (E)");
		}
		next = yylex();
		E();
		if(next == ZZ){
			next = yylex();
		}
		else{
			error("Ocekivana: ZZ");
		}
	}
	else if(next == NUM){
		if(ISPIS){
			ispis("F -> num");
		}
		next == yylex();
		printf("%i", yyval);
		return;
	}
	else{
		error("Ocekivano: OZ ili NUM");
	}
}