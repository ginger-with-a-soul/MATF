%option noyywrap

%{

	#include <stdio.h>
	#include <stdlib.h>
	
	void stampaj_nisku(char* s);
	void stampaj_karakter(char c);
%}

DIGIT 	[0-9]
ID		[_a-zA-Z][a-zA-Z0-9_]*
WHITE	[ \t\n]

%%

{DIGIT}+		{
					fprintf(yyout, "<span style=\"color:blue\">%s</span>", yytext);
				}
{DIGIT}+\.{DIGIT}*		{
					fprintf(yyout, "<span style=\"color:blue\">%s</span>", yytext);
				}
if|else|switch|case|break|continue|while|for|do|char|double|int|float|short|signed|unsigned|long|void|struct|union|typedef|static|extern|default|return|register {
					fprintf(yyout, "<span style=\"font-weight:bold\">%s</span>", yytext);
			}
{ID}		{
				fprintf(yyout, "<span style=\"color:black\">%s</span>", yytext);
			}
^{WHITE}*#(.|\\\\n)*\n	{
				fprintf(yyout, "<span style=\"color:green\">%s</span>", yytext);
			}
"/*"([^*]|"*"*[^/*])*"*"*"/" {

				fprintf(yyout, "<span style=\"color:blue\">");
				stampaj_nisku(yytext);
				fprintf(yyout, "</span>\n");
			}
\"([^\\\"]|\\.)*\" {

				fprintf(yyout, "<span style=\"color:red\">");
				stampaj_nisku(yytext);
				fprintf(yyout, "</span>\n");
				}
'([^\\']|\\.)'			{
					fprintf(yyout, "<span style=\"color:violet\">");
				stampaj_nisku(yytext);
				fprintf(yyout, "</span>\n");
				}
.				{

					ECHO;
				}
%%

void stampaj_karakter(char c) {
	if (c == '<')
		fprintf(yyout, "&lt");
	else if (c == '>')
		fprintf(yyout, "&gt");
	else if (c == '&')
		fprintf(yyout, "&amp");
	else
		fprintf(yyout, "%c", c);
}

void stampaj_nisku(char* s) {

	while (*s++) {
		stampaj_karakter(*s);
	}
}

int main(int argc, char** argv){

	yyin = fopen(argv[1], "r");
	if (yyin == NULL)
		exit(EXIT_FAILURE);
	yyout = fopen(argv[2], "w");
	if (yyout == NULL)
		exit(EXIT_FAILURE);
	
	fprintf(yyout, "<html>\n<head>\n<title>%s</title>\n</head>\n<body>\n<pre>\n", argv[1]);
	
	yylex();	
	
	fprintf(yyout, "\n</pre>\n</body>\n</html>");
	
	exit(EXIT_SUCCESS);
}
