%option noyywrap

%{
	#include <stdio.h>
	#include <stdlib.h>

	int num_chars = 0;
	int num_lines = 0;
%}

%%

\n { num_chars++; num_lines++;   }
.  { num_chars++;	}

%%

int main(){

	yylex();
	
	printf("Ukupno karaktera: %d\n", num_chars);
	printf("Ukupno linija: %d\n", num_lines);
	
	exit(EXIT_SUCCESS);
}
