%option noyywrap
%option nounput
%option noinput

%x comment

%{
#include "colors.h"
void colorize(const char* color){
    fprintf(yyout, "<span style='color: %s'>%s</span>", color, yytext);
}
%}

DIGIT [0-9]
KEYWORD while|for|if|else|#define|#include|const|static|begin|switch|case|break|default
TYPE int|char|double|float|struct|long|unsigned|signed|void|size_t|short

%%
"/*" {
    BEGIN(comment); colorize(COMMENT);}
<comment>[^*\n]* {colorize(COMMENT);}
<comment>"*"[^/\n] {colorize(COMMENT);}
<comment>"*"\n {colorize(COMMENT);}
<comment>\n {colorize(COMMENT);}
<comment>"*/" { BEGIN(INITIAL); }

"//".* {colorize(COMMENT);}

{DIGIT}+ {colorize(KEYWORDS);}
{TYPE} {colorize(TYPES);}
{KEYWORD} {colorize(KEYWORDS);}
. {colorize(REGULAR);}

%%
int main(){

    yyout = fopen("08_output.html", "w");

    fprintf(yyout, "<pre style='background: %s'>", BACKGROUND_COLOR);
    yylex();
    fprintf(yyout, "</pre>");

    fclose(yyout);
    exit(EXIT_SUCCESS);
}