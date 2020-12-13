%option noyywrap

%{

#include "tokeni.h"

%}

%%

print	{return PRINT_T;}
card	{return CARD_T;}

[a-zA-Z][a-zA-Z0-9_]* {return ID;}
[+-]?[0-9]+			{return BROJ;}

"\\/"		{return UNIJA_T;}
"/\\"		{return PRESEK_T;}
"\\"		{return RAZLIKA_T;}
"~"			{return KOMPLEMENT;}

"("		{return OZ;}
")"		{return ZZ;}
"{"		{return OVZ;}
"}"		{return ZVZ;}

"="		{return JEDNAKO;}
","		{return Z;}
";"		{return TZ;}

[ \t\n]	{}
. 		{
			fprintf(stderr,"Leksicka greska: %s\n", yytext);
			exit(EXIT_FAILURE);
		}

%%
