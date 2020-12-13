%option noyywrap

%{

#include "parser.tab.h"

%}

%%

print			{ return PRINT; }
print_ALL		{return PRINT_ALL; }
[A-Za-z]+			{ 
						char* cpy = strdup(yytext);
						if (cpy == NULL) 
							exit(EXIT_FAILURE);
						yylval.ime = cpy;
						return ID; 
					}
[0-9]+(\.[0-9]*)?	{
						yylval.v = atof(yytext);
						return BROJ;
					}
"=="				{ return EQ;  }
"!="				{ return NEQ; }
"<="				{ return LEQ; }
">="				{ return GEQ; }
[+*/()<>=;-]		{ return *yytext; }
[ \t\n]				{ }
.					{
						fprintf(stderr, "Leksicka greska: %s\n", yytext);
						exit(EXIT_FAILURE);
					}

%%
