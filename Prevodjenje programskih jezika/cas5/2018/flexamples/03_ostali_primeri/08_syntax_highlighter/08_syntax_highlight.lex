%option noyywrap
%option noinput
%option nounput

%x comment

%{
#include "08_colors.h"

void colorize(const char* color)
{
    fprintf(yyout, "<span style='color: %s'>%s</span>", color, yytext);
}
%}

DIGIT [0-9]
ID [a-zA-Z_][a-zA-Z0-9_]*
WHITE [ \t\n]
KEYWORD if|else|switch|case|while|for|do|break|continue|const|static
TYPE int|short|long|signed|unsigned|void|size_t|float|double

%%
"/*" { BEGIN(comment); colorize(COMMENT_COLOR); }
<comment>[^*\n]* { colorize(COMMENT_COLOR); }
<comment>"*"[^/\n] { colorize(COMMENT_COLOR); }
<comment>"*"\n { colorize(COMMENT_COLOR); }
<comment>\n { colorize(COMMENT_COLOR); }
<comment>"*/" { BEGIN(INITIAL); }
"//".* { colorize(COMMENT_COLOR); }
{DIGIT}* { colorize(NUMBER_COLOR); }
\"([^\\\"]|\\.)*\" { colorize(STRING_COLOR); }
'([^\\']|\\.)' { colorize(CHAR_COLOR); }
^{WHITE}*#(.|\\\n)*\n  { colorize(PREPROC_COLOR); }
{KEYWORD} { colorize(PREPROC_COLOR); }
{TYPE} { colorize(TYPE_COLOR); }
{ID} { colorize(ID_COLOR); }
. { colorize(REGULAR_COLOR); }

%%
int main()
{
    yyout = fopen("08_output.html", "w");
    fprintf(yyout, "<pre style='background: %s'>", BACKGROUND);
    yylex();
    fprintf(yyout, "</pre>");
    return 0;
}
