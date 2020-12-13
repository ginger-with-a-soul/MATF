%option noyywrap

%{
	#include "tokeni.h"
	
	extern int yyval;
%}

%%

[0-9]+		{
				yyval = atoi(yytext);
				return BROJ; 
			}	
"("			{ return OZ; }
")"			{ return ZZ; }
"+"			{ return PLUS; }
"*"			{ return PUTA; }
"-"			{ return MINUS; }
"/"			{ return DELJENJE; }
[ \t\n]		{ }
.			{ 
				fprintf(stderr, "Leksicka greska: %s\n", yytext);
				exit(EXIT_FAILURE);
			}

%%
