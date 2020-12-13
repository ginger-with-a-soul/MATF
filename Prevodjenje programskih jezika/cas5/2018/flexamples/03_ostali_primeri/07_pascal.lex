%option noyywrap
%option nounput
%option noinput

%{
#include <stdlib.h>
#define TOKEN_INT 1
#define TOKEN_REAL 2
#define TOKEN_KEYWORD 3
#define TOKEN_ID 4
#define TOKEN_OP 5
#define TOKEN_RO 6
#define TOKEN_ASSIGNMENT_OP 7
#define TOKEN_SEP 8
#define TOKEN_UNKNOWN_CHAR 9
#define TOKEN_BRACKET 10
#define TOKEN_COMMENT 11
%}

DIGIT [0-9]
ID [a-z][a-z0-9]*
%%
{DIGIT}+ { return TOKEN_INT; }
{DIGIT}+\.{DIGIT}* { return TOKEN_REAL; }
if|then|begin|end|var|function|integer {
    return TOKEN_KEYWORD;
}
{ID} { return TOKEN_ID; }
[*+/-] { return TOKEN_OP; }
"<"|">"|">="|"<="|"="|"<>" { return TOKEN_RO; }
":=" { return TOKEN_ASSIGNMENT_OP; }
[.,:;] { return TOKEN_SEP; }
"{"[^}\n]*"}" { }
"("|")" {
    return TOKEN_BRACKET;
}
[ \t\n] {}
. {
    ECHO;
    return TOKEN_UNKNOWN_CHAR;
}

%%
int main()
{
    int token;
    while ((token = yylex())) {
        switch(token) {
            case TOKEN_INT:             printf("TOKEN_INT\n"); break;
            case TOKEN_REAL:            printf("TOKEN_REAL\n"); break;
            case TOKEN_KEYWORD:         printf("TOKEN_KEYWORDT\n"); break;
            case TOKEN_ID:              printf("TOKEN_ID\n"); break;
            case TOKEN_OP:              printf("TOKEN_OP\n"); break;
            case TOKEN_RO:              printf("TOKEN_RO\n"); break;
            case TOKEN_ASSIGNMENT_OP:   printf("TOKEN_ASSIGNMENT_OP\n"); break;
            case TOKEN_SEP:             printf("TOKEN_SEP\n"); break;
            case TOKEN_UNKNOWN_CHAR:    printf("TOKEN_UNKNOWN_CHAR\n"); break;
            case TOKEN_BRACKET:         printf("TOKEN_BRACKET\n"); break;
            default:                    printf("Unrecognized token %d...\n", token); break;
        }
    }
    return 0;
}

