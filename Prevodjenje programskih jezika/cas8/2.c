#include <stdio.h>
#include <stdlib.h>
#define check_error(expr, userMsg)\
	do {\
		if(expr){\
			perror(userMsg);\
			exit(EXIT_FAILURE);\
		}\
	} while(0)\

/*
    Gramatika je:
    A -> Aa
      |  b

	A -> bAP
	AP -> aAP
		| EPS
*/

int lookahead;

#define a 1
#define b 2
#define EOI 0
#define ISPIS 1

void A();
void AP();

int yylex();

int main(){
	lookahead = yylex();
	A();
	if(lookahead != EOI){
		check_error(1, "Los niz karaktera\n");
	}
	exit(EXIT_SUCCESS);
}

int yylex(){
	char ch = getchar();
	switch(ch){
		case 'a': return a; break;
		case 'b': return b; break;
		case '\n':
		case EOF: return EOI; break;
		default: check_error(1, "Losa sintaksa\n");
	}
	return -1;
}

void A(){
	if(lookahead == b){
		if(ISPIS){
			printf("A -> bAP\n");
		}
		lookahead = yylex();
		AP();
	}
	else{
		check_error(1, "Ocekivan ulaz b\n");
	}
}

void AP(){
	if(lookahead == a){
		if(ISPIS){
			printf("AP -> aAP\n");
		}
		lookahead = yylex();
		AP();
	}
	else if(lookahead == EOI){
		if(ISPIS){
			printf("AP -> EPS\n");
		}
	}
	else{
		check_error(1, "Ocekivano a ili kraj ulaza\n");
	}
}