%{

#include <stdio.h>
#include <stdlib.h>

extern int yylex();

void yyerror(char* s) {
	
	fprintf(stderr, "Sintaksna greska: %s\n", s);
	exit(EXIT_FAILURE);
}

%}

%union{
	int vrednost;
}

%token<vrednost> BROJ

%type<vrednost> e t f

%start pocetak

%%
pocetak: e		{ printf("Vrednost izraza: %d\n", $1); }
	;
e : e '+' t		{ $$ = $1 + $3; }
	| t			{ $$ = $1; }
	;
t : t '*' f		{ $$ = $1 * $3; }
	| f			{ $$ = $1; }
	;
f : '(' e ')'	{ $$ = $2; }
	| BROJ		{ $$ = $1; }
	;

%%

int main() {

	if (yyparse() == 0) 
		printf("OK\n");
	else 
		printf("Nije OK\n");
		
	exit(EXIT_SUCCESS);
}


