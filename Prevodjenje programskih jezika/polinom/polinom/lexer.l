%option noyywrap
%option noinput
%option nounput
%{
#include "polinom.h"
#include "y.tab.h"

%}

%%
-?[0-9]+(\.[0-9]+)?  { yylval.vrednost =  atof(yytext);
                        return BROJ;}
[a-z][a-z0-9]*        {  yylval.ime = strdup(yytext);
                         if(yylval.ime == NULL){
                            fprintf(stderr, "Strdup() %s\n",yytext); 
                            exit(EXIT_FAILURE);}    
                            
                          return ID; }
[<>,\n:=+\-*()!'$|[\]]     return *yytext;

[ \t]      				{}

.                        {
  fprintf(stderr, "Leksicka greska: Neprepoznat karakter '%c'\n", *yytext);
  exit(EXIT_FAILURE);
}
%%

