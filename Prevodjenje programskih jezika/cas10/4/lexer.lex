%option noyywrap
%option noinput
%option nounput

%{
#include <iostream>
#include <string>
#include <cstdlib>
#include "parser.tab.hpp"
%}

%%

[0-9]+(\.[0-9]+)? {
	yylval.vrednost = atof(yytext);
	return broj_token;
}

print {
	return print_token;
}

[a-zA-Z_][a-zA-Z0-9_]* {
	yylval.id = new std::string(yytext);
	return id_token;
}

[\n*+()/-] return *yytext;

[ \t] {}

.	{
	std::cerr << "Nepodrzana leksema: " << *yytext << std::endl;
	exit(EXIT_FAILURE);
}

%%
