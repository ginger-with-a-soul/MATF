%option noyywrap

%{

#include "tokeni.h"

%}

%%
int	{return INT_T;}
print {return PRINT_T;}
_[a-zA-Z][a-zA-Z0-9]*	{return ID;}
[0-9]+			{return BROJ;}
"|"			{return ILI;}
"&"			{return III;}
"("			{return OZ;}
")"			{return ZZ;}
"~"			{return INV;}
";"			{return TZ;}
[ \t\n]		{}
. 			{printf("lex\n"); exit(EXIT_FAILURE);}

%%
