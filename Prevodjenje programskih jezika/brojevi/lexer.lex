%option noyywrap
%option nounput
%option noinput

%{
#include <iostream>
#include <cstdlib>
#include <string>
#include <map>

#include "parser.tab.hpp"
%}

%%

print {return PRINT_T;}
int {return INT_T;}
list {return LIST_T;}

\_[A-Za-z][A-Za-z0-9]* {yylval.string_type = new std::string(yytext); return ID_T;}
0x[0-9]+ {yylval.int_type = strtol(yytext, NULL, 16); return NUMBER_T;}
0[0-9]+ {yylval.int_type = strtol(yytext, NULL, 8); return NUMBER_T;}
[+-]?[0-9]+ {yylval.int_type = strtol(yytext, NULL, 10); return NUMBER_T;}
[=\;,+*\/\(\)\-\~\|\&\^\<\>\[\]] {return *yytext;}
[\t \n] {}
. {
	std::cerr << "Unknown character: " << *yytext << std::endl;
	exit(EXIT_FAILURE);
}

%%