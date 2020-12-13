#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

	// E -> TE'    { num , ( }
    // E'-> +TE'   { + }
    //   |  eps    { ) , EOI }
    // T -> FT'    { ( , num }
    // T'-> *FT'   { * }
    //    | eps    { + , ) , EOI }
    // F -> (E)    { ( }
    //   |  num    { num }
#define check_error(userMsg)\
	perror(userMsg);\
	exit(EXIT_FAILURE);\

#define ISPIS 1

#define NUM 1
#define OZ 2
#define ZZ 3
#define EOI 0
#define PLUS 4
#define ZVEZDA 5

int lookahead;
void E();
void EP();
void T();
void TP();
void F();

int yylex(){
	char ch = getchar();
	switch(ch){
		case '(': return OZ;
		case ')': return ZZ;
		case '*': return ZVEZDA;
		case '+': return PLUS;
		case '\n':
		case EOF: return EOI;
	}

	if(isdigit(ch)){
		while(isdigit(ch = getchar()));
		ungetc(ch, stdin);
		return NUM;
	}
	else{
		check_error("Leksicka greska: Nepoznat ulaz\n");
	}
	return -1;
}

void E(){
	if(lookahead == NUM || lookahead == OZ){
		if(ISPIS){
			printf("E->TE'\n");
		}
		T();
		EP();
	}
	else{
		check_error("Ocekivan ulaz: NUM ili '('\n");
	}
}

void EP(){
	if(lookahead == PLUS){
		if(ISPIS){
			printf("E'->+TE'\n");
		}
		lookahead = yylex();
		T();
		EP();
	}
	else if(lookahead == ZZ || lookahead == EOI){
		if(ISPIS){
			printf("E'->eps\n");
		}
	}
	else{
		check_error("Ocekivan ulaz: '+', ')' ili EOI\n");
	}
}

void T(){
	if(lookahead == OZ || lookahead == NUM){
		if(ISPIS){
			printf("T->FT'\n");
		}
		F();
		TP();
	}
	else{
		check_error("Ocekivan ulaz: '(' ili NUM\n");
	}
}

void TP(){
	if(lookahead == ZVEZDA){
		if(ISPIS){
			printf("T'->*FT'\n");
		}
		lookahead = yylex();
		F();
		TP();
	}
	else if(lookahead == PLUS || lookahead == ZZ || lookahead == EOI){
		if(ISPIS){
			printf("T'->eps\n");
		}
	}
	else{
		check_error("Ocekivan ulaz: '*', '+', ')' ili EOI\n");
	}
}

void F(){
	if(lookahead == OZ){
		if(ISPIS){
			printf("F->(E)\n");
		}
		lookahead = yylex();
		E();
		if(lookahead == ZZ){
			lookahead = yylex();
		}
		else{
			check_error("Ocekivana: ')'\n");
		}
	}
	else if(lookahead == NUM){
		if(ISPIS){
			printf("F->num\n");
		}
		lookahead = yylex();
	}
	else{
		check_error("Ocekivan ulaz: '(' ili NUM\n");
	}
}

int main(){
	lookahead = yylex();
	E();
	if(lookahead != EOI){
		check_error("Sintaksna greska: Visak leksema na ulazu\n");
	}
	exit(EXIT_SUCCESS);
}
