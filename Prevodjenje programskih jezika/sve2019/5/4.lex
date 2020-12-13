%option noyywrap

%x comment

%{
	#include <stdio.h>
	#include <stdlib.h>
	
	int broj_linija = 0;
%}

%%

"/*" 	{
			BEGIN(comment);
		}
<comment>[^*\n]*	{ }
<comment>"*"*		{ }
<comment>\n			{ broj_linija++;	}

<comment>\*+"/"		{
						BEGIN(INITIAL);
					}
\n		{ broj_linija++;ECHO;}
.		{ ECHO;}

%%

int main(){

	yylex();
	
	exit(EXIT_SUCCESS);
}
