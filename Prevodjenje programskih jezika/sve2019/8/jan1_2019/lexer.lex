%option noyywrap
%option noinput
%option nounput

%{
#include <iostream>
#include <cstdlib>
#include <string>
#include <map>
#include "numbers.hpp"

#include "parser.tab.hpp"
%}

%%
print {return PRINT_T;}
int {return INT_T;}
list {return LIST_T;}

_[A-Za-z][A-Za-z0-9]* {yylval.string_type = new std::string(yytext); return ID_T;}
0x[0-9A-Fa-f]+ {yylval.num_type = strtoi(yytext, NULL, 16); return NUMBER_T;}
0[0-7]+ {yylval.num_type = strtoi(yytext, NULL, 8); return NUMBER_T;}
[0-9]+ {yylval.num_type = atoi(yytext); return NUMBER_T;}

"<<" {return SHL_T;}
">>" {return SHR_T;}
"==" {return EQ_T;}
"!=" {return NEQ_T;}

[+*\/\-\[\]\=\;\(\)&\|\^\~] {return *yytext;}
[\t \n] {}

. {
	std::cerr << "Unknown token:" << *yytext << std::endl;
	exit(EXIT_FAILURE);
}

%%