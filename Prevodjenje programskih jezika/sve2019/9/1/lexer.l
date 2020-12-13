%option noyywrap

%{

#include <iostream>
#include <cstdio>
#include <cstdlib>

using namespace std;

#include "skup.hpp"
#include "parser.tab.hpp"

%}

%%

print {return PRINT_T;}
check {return CHECK_T;}
card  {return CARD_T;}
UniversalSet {return UNI_T;}

[a-zA-Z][a-zA-Z0-9_]*	{
							yylval.ime = new string(yytext);
							return ID;
						}
[+-]?[0-9]+		{
					yylval.x = atoi(yytext);
					return BROJ;
				}

"/\\"		{return PRESEK_T;}
"\\/"		{return UNIJA_T;}
"\\"		{return RAZLIKA_T;}
".."		{return TT;}
[();<,:=~{}]			{return *yytext;}

[ \t\n]		{ }
. 			{
				cerr<<"Leksicka greska: "<<yytext<<endl;
				exit(EXIT_FAILURE);
			}
	
%%

