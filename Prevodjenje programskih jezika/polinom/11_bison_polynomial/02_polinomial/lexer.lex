%option noyywrap
%option nounput
%option noinput

%{
#include <iostream>
#include "polinomial.hpp"
#include "parser.tab.hpp"
%}

%%
[-]?[0-9]+(\.[0-9]+)? {
    yylval.float_type = atof(yytext);
    return num_token;
}

[a-zA-Z][a-zA-Z0-9]+ {
    yylval.str_type = new std::string(yytext);
    return id_token;
}

[<>,\n+*():=!$|'\[\]-] {
    return *yytext;
}
[ \t] {

}
. {
    std::cerr
        << "Leksicka greska: Neprepoznat karakter: "
        << *yytext
        << std::endl;
    exit(EXIT_FAILURE);
}
%%
