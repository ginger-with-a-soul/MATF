%option noyywrap

%{

	#include <stdio.h>
	#include <stdlib.h>
	
	#define KLJUCNA_REC		(1)
	#define ID				(2)
	#define INTERPUNKCIJA	(5)
	#define DODELA			(6)
	#define I_CONST			(7)
	#define F_CONST			(8)
	#define OP				(9)
	#define ROP				(15)
	#define NN				(16)
	#define ZAGRADE			(17)
	
%}

DIGIT	[0-9]
ID		[a-z][a-z0-9]*


%%

if|then|begin|end|var|integer {return KLJUCNA_REC;}
{ID}						  {return ID;}
{DIGIT}+					  {return I_CONST;}
{DIGIT}+\.{DIGIT}*			  {return F_CONST;}
[+*/-]						  {return OP;}
[<>=]|">="|"<="				  {return ROP;}
:=							  {return DODELA;}
[.:;,]						  {return INTERPUNKCIJA;}
"("|")"						  {return ZAGRADE;}
[ \t\n]						  { }
.							  {
								fprintf(stderr, "Leksicka greska: %s\n", yytext);
								exit(EXIT_FAILURE);
							  }

%%

int main(int argc, char** argv){
	
	int token;
	if (argc > 1) {
		yyin = fopen(argv[1], "r");
		if (yyin == NULL) {
			exit(EXIT_FAILURE);
		}
	}
	else {
		yyin = stdin;
	}
	
	while ((token = yylex()) != 0) {
	
		switch (token) {
			case KLJUCNA_REC: printf("KLJUCNA_REC: %s\n", yytext); break;
			case ID: printf("ID: %s\n", yytext); break;
			case INTERPUNKCIJA: printf("INTERPUNKCIJA: %s\n", yytext); break;
			case DODELA: printf("DODELA: %s\n", yytext); break;
			case I_CONST: printf("I_CONST: %s\n", yytext); break;
			case F_CONST: printf("F_CONST: %s\n", yytext); break;
			case OP: printf("OP: %s\n", yytext); break;
			case ROP: printf("ROP: %s\n", yytext); break;
			case ZAGRADE: printf("ZAGRADE: %s\n", yytext); break;
			case NN: printf("NN: %s\n", yytext); break;
			default: exit(EXIT_FAILURE); break;
		}
	}
	
	if (yyin != stdin)
		fclose(yyin);
		
	exit(EXIT_SUCCESS);
}
