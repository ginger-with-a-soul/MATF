%option noyywrap

%x comment

%{
	#include <stdio.h>
	#include <stdlib.h>
	
	int broj_linija = 0;
%}

%%
if|then		{return KW;}
[a-z]*		{return ID;}


"/*"		{BEGIN(comment);}

<comment>[^*\n]*	{ }
<comment>"*"*		{ }
<comment>\n			{broj_linija++;}
<comment>\*+"/"		{BEGIN(INITIAL);}
\n					{broj_linija++; ECHO;}
.					{ECHO; }

%%

int main(){
	yylex();
	
	printf("Broj linija: %d\n", broj_linija);
	
	exit(EXIT_SUCCESS);
}
