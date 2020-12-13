%option noyywrap
%option noinput
%option nounput

%{
#include <iostream>
#include <cstdlib>
#include <string>
#include <map>
#include "set.hpp"

#include "parser.tab.hpp"
%}

%%
print {return PRINT_T;}
card {return CARD_T;}
check {return CHECK_T;}
UniversalSet {return UNI_T;}

[A-Za-z][A-Za-z0-9]* {yylval.string_type = new std::string(yytext); return ID_T;}
[+-][0-9]+ {yylval.num_type = atoi(yytext); return NUM_T;}

"/\\"		{return PRESEK_T;}
"\\/"		{return UNIJA_T;}
"\\"		{return RAZLIKA_T;}
".."		{return TT;}

[();<,:=~{}] {return *yytext;}

[\t \n] {}

. {
	std::cerr << "Lex error: " << yytext << std::endl;
	exit(EXIT_FAILURE);
}

%%