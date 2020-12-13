%option noyywrap

%{
	
	#include <stdio.h>
	#include <stdlib.h>
	
	#define I_CONST	(1)
	#define F_CONST	(2)
%}

DIGIT [0-9]

%%

[+-]?{DIGIT}+		{return I_CONST;}
[+-]?{DIGIT}+\.{DIGIT}*([eE][+-]?{DIGIT}+)?	{return F_CONST;}
.|\n	{ }

%%

int main(int argc, char** argv){

	int token = 0;
	
	yyin = fopen(argv[1], "r");
	if (yyin == NULL)
		exit(EXIT_FAILURE);
	
	yyout = fopen(argv[2], "w");
	if (yyout == NULL)
		exit(EXIT_FAILURE);
	
	while ((token = yylex()) != 0) {
	
		switch (token){
			case I_CONST:
				fprintf(yyout, "Ceo broj: %s\n", yytext);
				break;
			case F_CONST:
				fprintf(yyout, "Realan broj: %s\n", yytext);
				break;
			default:
				exit(EXIT_FAILURE);
				break;
		}
	}

	exit(EXIT_SUCCESS);
}
