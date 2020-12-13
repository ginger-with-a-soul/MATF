%option noyywrap

%{
	#include <stdio.h>
	#include <stdlib.h>
%}

%%

"{"[^}]*"}" { }
"(*"([^*\n]|\*+[^)\n])*\*+")" { }

%%


int main(){
	
	yylex();

	exit(EXIT_SUCCESS);
}
