%option noyywrap

%{

#include "parser.tab.h"

%}

%%

print		{return PRINT;}
[A-Za-z]+	{	
				char *cpy = strdup(yytext);
				if (cpy == NULL) {
					fprintf(stderr,"strdup lexer\n");
					exit(EXIT_FAILURE);
				}
				yylval.ime = cpy;
				return ID;
			}
[0-9]+(\.[0-9]*)? {
						yylval.v = atof(yytext);
						return BROJ;
				  }
">="		{return GEQ;}
"<="		{return LEQ;}
"=="		{return EQ;	}
"!="		{return NEQ;}
[+*/()<>;=-]	{return *yytext;}
[ \t\n]		{ }
.			{
				fprintf(stderr,"Leksicka greska: %s\n", yytext);
				exit(EXIT_FAILURE);
			}

%%
