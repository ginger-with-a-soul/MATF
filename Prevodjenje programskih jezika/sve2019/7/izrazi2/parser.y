%{

#include <stdio.h>
#include <stdlib.h>

extern int yylex();

int yyerror(char* s) {

	fprintf(stderr, "Sintaksna greska: %s\n", s);
	exit(EXIT_FAILURE);
}

%}

%union{
	
	float v;
}

%left '+' '-'
%left '*' '/'
%right UMINUS

%token<v> BROJ

%type<v> e

%start pocetak

%%

pocetak: e		{ printf("Vrednost izraza: %.2f\n", $1); }
	;
e :   e '+' e	{ $$ = $1 + $3;}
	| e '-' e	{ $$ = $1 - $3;}
	| e '*' e	{ $$ = $1 * $3; }
	| e '/' e	{ $$ = $1 / $3; }
	| '-' e	%prec UMINUS	{ $$ = -$2; }
	| BROJ		{ $$ = $1; }
	| '(' e ')' { $$ = $2;}

%%

int main(){
	
	if (yyparse() == 0) {
		printf("Prihvate se izraz\n");
	}
	else {
		printf("Ne prihvata se izraz.\n");
	}
	
	exit(EXIT_SUCCESS);
}
