%option noyywrap
%option nounput
%option noinput

%{
#include <iostream>
#include <string>
#include <cstdlib>
#include <map>
#include "razlomak.hpp"

/* Mora na kraju jer zahteva sve iznad */
#include "parser.tab.hpp"
%}

%%
   
print  { return print_token; }
nom  { return nom_token; }
den  { return den_token; }
double  { return double_token; }
equals  { return equals_token; }
[a-zA-Z]+ { yylval.string_type = new std::string(yytext); return id_token; }

[+-]?[0-9]+ {
              yylval.int_type = atoi(yytext);
              return broj_token; 
} 

[\[\],/*+\()\-\n{}=] { return *yytext; }

[\t ] { /* Ignorisemo beline */ }

. { 
    // isto sto i stderr u C-u
    std::cerr << "Leksicka greska, nepoznat karakter: " << *yytext << std::endl;
    exit(EXIT_FAILURE);
}

%%