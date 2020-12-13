%option noyywrap

%{
	
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	
	int vrednost;
%}

hiljade 	M+
stotine 	C+|CD|DC*|CM
desetice 	X+|XL|LX*|XC
jedinice	I+|IV|VI*|IX

%%

{hiljade}		{vrednost += 1000*yyleng; }
{stotine}		{
					if (strcmp(yytext, "CM") == 0) {
						vrednost += 900;
					}
					else if (strcmp(yytext, "CD") == 0) {
						vrednost += 400;
					}
					else {
						if (yytext[0] == 'D') {
							vrednost += 500;
							if (yyleng <= 4) {
								vrednost += 100*(yyleng-1);
							}
							else  {
								printf("Pogresan format broja: %s\n", yytext);
								exit(EXIT_SUCCESS);
							}
						}
						else if (yytext[0] == 'C') {
							
							if (yyleng <= 3) {
								vrednost+=100*yyleng;
							}
							else {
								printf("Pogresan format broja: %s\n", yytext);
								exit(EXIT_SUCCESS);
							}
						}
					}
				}
{desetice}		{
					if (strcmp(yytext, "XC") == 0) {
						vrednost += 90;
					}
					else if (strcmp(yytext, "XL") == 0) {
						vrednost += 40;
					}
					else {
						if (yytext[0] == 'L') {
							vrednost += 50;
							if (yyleng <= 4) {
								vrednost += 10*(yyleng-1);
							}
							else  {
								printf("Pogresan format broja: %s\n", yytext);
								exit(EXIT_SUCCESS);
							}
						}
						else if (yytext[0] == 'X') {
							
							if (yyleng <= 3) {
								vrednost+=10*yyleng;
							}
							else {
								printf("Pogresan format broja: %s\n", yytext);
								exit(EXIT_SUCCESS);
							}
						}
					}
				}
{jedinice}		{
					if (strcmp(yytext, "IX") == 0) {
						vrednost += 9;
					}
					else if (strcmp(yytext, "IV") == 0) {
						vrednost += 4;
					}
					else {
						if (yytext[0] == 'V') {
							vrednost += 5;
							if (yyleng <= 4) {
								vrednost += 1*(yyleng-1);
							}
							else  {
								printf("Pogresan format broja: %s\n", yytext);
								exit(EXIT_SUCCESS);
							}
						}
						else if (yytext[0] == 'I') {
							
							if (yyleng <= 3) {
								vrednost+=1*yyleng;
							}
							else {
								printf("Pogresan format broja: %s\n", yytext);
								exit(EXIT_SUCCESS);
							}
						}
					}
				}
.|\n			{
					if (vrednost > 0) {
						printf("%d", vrednost);
						vrednost = 0;
					}
					ECHO;
				}


%%

int main(){

	yylex();
	
	exit(EXIT_SUCCESS);
}
