%option noyywrap
%option noinput
%option nounput

%{
#include <iostream>
#include <cstdlib>
#include "parser.tab.hpp"
%}

%%

[0-9]+(\.[0-9]+)? {
	yylval.vrednost = atof(yytext);
	return broj_token;
}
[+*()/-] return *yytext;
[\n \t] {}
.	{
	std::cerr << "Nepodrzana leksema: " << *yytext << std::endl;
	exit(EXIT_FAILURE);
}
%%
