#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define error(userMsg)\
	perror(userMsg);\
	exit(EXIT_FAILURE);\


#define ISPISX 6

void ispis(const char* msg){
	if(ISPISX){
		printf("%s\n", msg);
	}
}
/*
	E -> TE'		{(, num}		{E.val = T.val + E'.val}
	E' -> +TE'		{+}				{E'1.val = T.val + E'2.val}
		| eps		{), EOI}		{E'.val = 0}
	T -> FT'		{(, num}		{T.val = F.val * T'.val}
	T' -> *FT'		{*}				{T'1.val = F.val * T'2.val}
		| eps		{+, EOI, )}		{T'.val = 1}
	F -> (E)		{(}				{F.val = E.val}
		| num		{num}			{F.val = num.val}
 */

#define EOI 0
#define OZ 1
#define ZZ 2
#define PLUS 3
#define ZVEZDA 4
#define NUM 5

int lookahead;
int yyval;

int E();
int EP();
int T();
int TP();
int F();

int yylex(){
	char ch = getchar();
	switch(ch){
		case '(': return OZ;
		case ')': return ZZ;
		case '+': return PLUS;
		case '*': return ZVEZDA;
		case '\n':
		case EOF: return EOI;
	}

	if(isdigit(ch)){
		yyval = ch - '0';
		while(isdigit(ch = getchar())){
			yyval = yyval * 10 + ch - '0';
		}

		ungetc(ch, stdin);
		return NUM;
	}
	else{
		error("Leksicka greska: nepodrzana leksema\n");
	}
}

int E(){
	if(lookahead == OZ || lookahead == NUM){
		ispis("E -> TE'");
		return T() + EP();
	}
	else{
		error("Ocekivano: '(' ili NUM\n");
	}
}

int EP(){
	if(lookahead == PLUS){
		ispis("E' -> +TE'");
		lookahead = yylex();
		return T() + EP();
	}
	else if(lookahead == ZZ || lookahead == EOI){
		ispis("E' -> eps");
		return 0;
	}
	else{
		error("Ocekivano: '+', ')' ili EOI\n");
	}
}

int T(){
	if(lookahead == OZ || lookahead == NUM){
		ispis("T -> FT'");
		return F() * TP();
	}
	else{
		error("Ocekivano: '(' ili NUM\n");
	}
	return -1;
}

int TP(){
	if(lookahead == ZVEZDA){
		ispis("T'-> *FT'");
		lookahead = yylex();
		return F() * TP();
	}
	else if(lookahead == PLUS || lookahead == ZZ || lookahead == EOI){
		ispis("T' -> eps");
		return 1;
	}
	else{
		error("Ocekivano: '*', '+', ')' ili EOI\n");
	}
	return -1;
}

int F(){
	if(lookahead == OZ){
		int tmp;
		ispis("F -> (E)");
		lookahead = yylex();
		tmp = E();
		if(lookahead == ZZ){
			lookahead = yylex();
		}
		else{
			error("Ocekivana: ')'\n");
		}
		return tmp;
	}
	else if(lookahead == NUM){
		ispis("F -> num");
		lookahead = yylex();
		return yyval;
	}
	else{
		error("Ocekivano: '(' ili NUM\n");
	}
}

int main(){
	int rez;
	lookahead = yylex();
	rez = E();
	if(lookahead != EOI){
		error("Semanticka greska\n");
	}
	else{
		printf("Rezultat: %i\n", rez);
	}

	exit(EXIT_SUCCESS);
}