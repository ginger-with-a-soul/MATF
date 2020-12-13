%option noyywrap

%{

#include "tokeni.h"

%}

%%

print		{return PRINT_T;}
card		{return CARD_T;}
[a-zA-Z][a-zA-Z0-9_]*	{return ID;}
[+-]?[0-9]+				{return BROJ;}
"/\\"	{return PRESEK_T;}
"\\/"	{return UNIJA_T;}
"\\"	{return RAZLIKA_T;}
"~"		{return KOMPLEMENT_T;}
"{"		{return OVZ;}
"}"		{return ZVZ;}
"("		{return OZ;}
")"		{return ZZ;}
","		{return Z;}
";"		{return TZ;}
"="		{return JEDNAKO;}
[ \t\n]	{ }
.		{
			fprintf(stderr, "Leksicka greska: %s\n", yytext);
			exit(EXIT_FAILURE);
		}

%%
