%option nounput
%option noinput
%option noyywrap

%{
#include <iostream>
#include <string>
#include <vector>
#include "parser.tab.hpp"
%}

%%
print { return print_token; }
int { return int_token; }
list { return list_token; }
_[a-z][a-z0-9]* { yylval.string_type = new std::string(yytext); return id_token; }
0 { yylval.broj_type = 0; return broj_token; }
0x[0-9A-F]* { yylval.broj_type = strtol(yytext, NULL, 16); return broj_token; }
0[0-7]* { yylval.broj_type = strtol(yytext, NULL, 8); return broj_token; }
[1-9][0-9]* { yylval.broj_type = atoi(yytext); return broj_token; }
"==" { return eq_token; }
"!=" { return neq_token; }
"<<" { return shl_token; }
">>" { return shr_token; }
[-+*/=<>()%&|\[\]~^!,;:] { return *yytext; }
[\t\n ] { }
. {
	std::cerr << "Leksicka greska: " << std::string(yytext) << std::endl;
	exit(EXIT_FAILURE);	
}

%%
