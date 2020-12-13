%option noyywrap

%{
	#include <stdio.h>
	#include <stdlib.h>
	
	int broj_otvorenih = 0;
%}

%%

"("	{broj_otvorenih++;}
")"	{
		if (broj_otvorenih == 0) {
			
			printf("Zagrade nisu lepo uparene\n");
			exit(EXIT_SUCCESS);
		}
		else {
			broj_otvorenih--;
		}
	}
\n	{ ECHO; }
.	{ ECHO; }

%%

int main() {

	yylex();
	
	if (broj_otvorenih == 0) {
		printf("Zagrade su uparene\n");
	}
	else {
		printf("Zagrade nisu uparene\n");
	}
	
	exit(EXIT_SUCCESS);
}
