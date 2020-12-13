
%{
	
#include <stdio.h>
#include <stdlib.h>

extern int yylex();

int yyerror(char* s){

	fprintf(stderr, "Sintaksnta greska: %s\n", s);
	exit(EXIT_FAILURE);
}

%}

%union{
	int vrednost;
}

%token<vrednost> BROJ

%type<vrednost> f t e

%start pocetak

%%
pocetak: pocetak naredba ';'
		| naredba ';' ;
naredba: e		{ printf("Vrednost izraza je: %d\n", $1); }
	;
e : e '+' t		{ $$ = $1 + $3; }
	| t			{ $$ = $1; }
	;
t: t '*' f		{ $$ = $1 * $3;}
	| f			{ $$ = $1; }
	;
f: '(' e ')'	{ $$ = $2; }
	| BROJ		{ $$ = $1; }
	;

%%

int main(){

	if (yyparse() == 0) {
		printf("Prihvate se izraz\n");
	}
	else {
		printf("Ne prihvata se izraz\n");
	}
	
	exit(EXIT_SUCCESS);
}



