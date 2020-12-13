%option noyywrap

%{
	#include <stdio.h>
	#include <stdlib.h>
	
	int num_chars = 0;
	int num_lines = 0;
%}

%%

\n		{num_lines++; num_chars++;}		
.		{num_chars++;}

%%

int main(int argc, char** argv) {
	
	yylex();
	
	printf("Broj linija: %d\n", num_lines);
	printf("Broj karaktera: %d\n", num_chars);

	exit(EXIT_SUCCESS);
}
