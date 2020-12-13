%option noyywrap
%option nounput
%option noinput

%{
#include <iostream>
#include <string>
#include <cstdlib>
#include <map>
#include "razlomci.hpp"

#include "parser.tab.hpp"
%}

%%
print {return PRINT_T;}
nom {return NOM_T;}
den {return DEN_T;}
double {return DOUBLE_T;}
equals {return EQUALS_T;}

[A-Za-z][A-Za-z0-9]* {yylval.string_type = new std::string(yytext); return ID_T;}
[+-]?[0-9]+ {yylval.int_type = atoi(yytext); return NUMBER_T;}
[\(\),+*\/\[\]=\n\-] {return *yytext;}
[\t ] {}

. {
	std::cerr << "Unsupported character: " << *yytext << std::endl;
	exit(EXIT_FAILURE);
}

%%