%option noyywrap
%option noinput
%option nounput

%{
#include <iostream>
#include <cstdlib>
#include "parser.tab.hpp"
%}

%%

[0-9]+ {return broj_token;}
[+*()] {return yytext[0];}
[\n \t] {}

.	{
	std::cerr << "Nepodrzana leksema" << *yytext << std::endl;
	exit(EXIT_FAILURE);
}

%%