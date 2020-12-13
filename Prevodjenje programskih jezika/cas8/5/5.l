%option noyywrap

%{
#include <stdio.h>
#include <stdlib.h>
#include "tokeni.h"

extern int yyval;
%}

%%
"+" {return PLUS;}
"*" {return PUTA;}
"(" {return OZ;}
")" {return ZZ;}
[0-9]+ {yyval = atoi(yytext); return NUM;}
\n	{return EOI;}

. {
	fprintf(stderr, "Nepodrzana leksema!\n");
	exit(EXIT_FAILURE);
}

%%