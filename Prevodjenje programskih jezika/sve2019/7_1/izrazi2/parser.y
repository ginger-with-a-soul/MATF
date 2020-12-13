%{

#include <stdio.h>
#include <stdlib.h>

extern int yylex();

void yyerror(char* s){

	fprintf(stderr, "Sintaksna greska: %s\n", s);
	exit(EXIT_FAILURE);
}

%}

%left '+' '-'
%left '*' '/'
%right UMINUS

%union{
	float v;
}

%token<v> BROJ
%type<v> e
%start niz_naredbi

%%

niz_naredbi: niz_naredbi naredba ';'		{}
	| naredba ';'							{}
	;
naredba: e 						{printf("Vrednost izraza je: %.2f\n", $1);}
	;
e: 		e '+' e					{$$ = $1+$3;}
	|	e '-' e					{$$ = $1-$3;}
	| 	e '*' e					{$$ = $1*$3;}
	|	e '/' e					{$$ = $1/$3;}
	| 	'-' e %prec UMINUS		{$$ = -$2;}
	| 	'(' e ')'				{$$ = $2;}
	| 	BROJ					{$$ = $1;}
	;

%%

int main(){
	
	if (yyparse() == 0)  {
		printf("OK\n");
	}
	else {
		printf("Nije OK\n");
	}
	
	exit(EXIT_SUCCESS);
}
