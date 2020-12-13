%option noyywrap
%option noinput
%option nounput

%{
#include "tokeni.h"
extern int yylval;
%}

%%
"+" return PLUS;
"*" return PUTA;
"("  return OZ;
")" return ZZ;
[0-9]+ { 
    yylval = atoi(yytext);
    return BROJ;    
}
"\n" return EOI;
. {
    fprintf(stderr,"Leksicka greska: Nepoznata leksema %s!\n", yytext);
    exit(EXIT_FAILURE); 
}
%%
