%option noyywrap

%{
	#include <stdio.h>
	#include <stdlib.h>
		
	#define KLJUCNA_REC 	(1)
	#define ID				(2)
	#define INTERPUNKCIJA	(3)
	#define DODELA			(4)
	#define I_CONST			(5)
	#define OP				(6)
	#define F_CONST			(7)
	#define ZAGRADE			(8)
	#define ROP				(9)
%}

%%

if|then|var|begin|end|integer		{return KLJUCNA_REC;}
[a-z][a-z0-9]*						{return ID;}
[0-9]+			{return I_CONST;}
[0-9]+\.[0-9]*	{return F_CONST;}
":="			{return DODELA;}
[+*/-]			{return OP;}
[><=]|"<="|">="	{return ROP;}
[.:,;]			{return INTERPUNKCIJA;}
"("|")"			{return ZAGRADE;}
[ \t\n]			{ }
.				{
					fprintf(stderr, "Leksicka greska: %s\n", yytext);
					exit(EXIT_FAILURE);
				}

%%

int main(int argc, char** argv){
	
	int token = 0;
	
	if (argc > 1 && ((yyin = fopen(argv[1], "r")) == NULL))
		exit(EXIT_FAILURE);
		
	while ((token = yylex()) != 0) {
	
		switch (token) {
			case KLJUCNA_REC: printf("KLJUCNA_REC: %s\n", yytext); break;
			case ID: printf("ID: %s\n", yytext); break;
			case DODELA: printf("DODELA: %s\n", yytext); break;
			case OP: printf("OP: %s\n", yytext); break;
			case ROP: printf("ROP: %s\n", yytext); break;
			case INTERPUNKCIJA: printf("INTERPUNKCIJA: %s\n", yytext); break;
			case ZAGRADE: printf("ZAGRADE: %s\n", yytext); break;
			case I_CONST: printf("I_CONST: %s\n", yytext); break;
			case F_CONST: printf("F_CONST: %s\n", yytext); break;
			default: exit(EXIT_FAILURE); break;
		}
	}
	
	if (yyin != stdin)
		fclose(yyin);
		
	exit(EXIT_SUCCESS);
}
