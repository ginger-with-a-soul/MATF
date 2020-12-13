#include <stdio.h>
#include <stdlib.h>

#define check_error(expr, userMsg)\
	do {\
		if(expr){\
			perror(userMsg);\
			exit(EXIT_FAILURE);\
		}\
	} while(0)\

	// S -> AB  {a}
    //    | C   {c}
    // A -> a   {a}
    // B -> b   {b}
    // C -> cS  {c}

int lookahead;

#define ISPIS 1

#define a 1
#define b 2
#define c 3
#define EOI 0

void S();
void A();
void B();
void C();

int yylex(){
	char ch = getchar();
	switch(ch){
		case 'a': return a; break;
		case 'b': return b; break;
		case 'c': return c; break;
		case '\n': break;
		case EOF: return EOI; break;
		default: check_error(1, "Leksicka greska\n"); break;
	}
	return -1;
}

void S(){
	if(lookahead == a){
		if(ISPIS){
			printf("S->AB\n");
		}
		A();
		B();
	}
	else if(lookahead == c){
		if(ISPIS){
			printf("S->C\n");
		}
		C();
	}
	else{
		check_error(1, "Sintaksna greska: ocekivano a ili c\n");
	}
}

void A(){
	if(lookahead == a){
		if(ISPIS){
			printf("A->a\n");
		}
		lookahead = yylex();
	}
	else{
		check_error(1, "Sintaksna greska: ocekivano a\n");
	}
}

void B(){
	if(lookahead == b){
		if(ISPIS){
			printf("B->b\n");
		}
		lookahead = yylex();
	}
	else{
		check_error(1, "Sintaksna greska: ocekivano b\n");
	}
}

void C(){
	if(lookahead == c){
		if(ISPIS){
			printf("C->cS\n");
		}
		lookahead = yylex();
		S();
	}
	else{
		check_error(1, "Sintaksna greska: ocekivano c\n");
	}
}

int main(){
	lookahead = yylex();
	S();
	if(lookahead != EOI){
		check_error(1, "Nedozvoljen broj karaktera na ulazu\n");
	}
	exit(EXIT_SUCCESS);
}