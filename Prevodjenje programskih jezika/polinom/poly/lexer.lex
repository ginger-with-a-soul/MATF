%option noyywrap
%option noinput
%option nounput

%{
#include <iostream>
#include "parser.tab.hpp"
%}

%%

[-]?[0-9]+(\.[0-9]+)? {yylval.float = atof(yytext); return broj_token;}
[_a-zA-Z][a-zA-Z0-9]+ {yylval.id = new std::string(yytext); return id_token;}
[<>+!=:$|*,\[\]\n()-] {return *yytext;}
[ \t] {}
. {
	std::cerr << Nepodrzana leksema: << *yyext << std::endl;
	exit(EXIT_FAILURE);
}

%%
