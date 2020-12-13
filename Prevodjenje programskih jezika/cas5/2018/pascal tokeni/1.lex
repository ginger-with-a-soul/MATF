%option noyywrap
%option nounput
%option noinput

%x comment

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
ID [a-zA-Z][a-zA-Z0-9_]*

%%

"/*" {
    BEGIN(comment);
}
<comment>[^*\n]* {}
<comment>"*"[^/\n] {}
<comment>"*"\n {}
<comment>\n {}
<comment>"*/" {
    BEGIN(INITIAL);
    return TOKEN_COMMENT;
}

"//".* {
    return TOKEN_COMMENT;
}

{DIGIT}+"."{DIGIT}* {
    return TOKEN_REAL;
}

{DIGIT}+ {
    return TOKEN_INT;
}

if|then|begin|end|var|function|integer {
    return TOKEN_KEYWORD;
}

{ID} {
    return TOKEN_ID;
}

[*+/-] {
    return TOKEN_OP;
}

"<"|">"|"<="|">="|"<<"|">>"|"<>"|"=" {
    return TOKEN_RO;
}

":=" {
    return TOKEN_ASSIGNMENT_OP;
}

[.,:;] {
    return TOKEN_SEP;
}

"("|")" {
    return TOKEN_BRACKET;
}

"{"[^}\n]*"}" {}

[ \t\n] {}

. {
    ECHO;
    return TOKEN_UNKNOWN_CHAR;
}

%%

int main(int argc, char** argv){

    if(argc > 1){
        yyin = fopen(argv[1], "r");
        if(yyin == NULL){
            printf("Bad yyin\n");
            exit(EXIT_FAILURE);
        }
    }
    if(argc > 2){
        yyout = fopen(argv[2], "w");
        if(yyout == NULL){
            printf("Bad yyout\n");
            exit(EXIT_FAILURE);
        }
    }

    int token;

    while((token = yylex())){
        switch(token){
            case TOKEN_INT: printf("INT\n"); break;
            case TOKEN_REAL: printf("REAL\n"); break;
            case TOKEN_ID: printf("ID\n"); break;
            case TOKEN_RO: printf("RO\n"); break;
            case TOKEN_BRACKET: printf("BRACKET\n"); break;
            case TOKEN_KEYWORD: printf("KEYWORD\n"); break;
            case TOKEN_UNKNOWN_CHAR: printf("UNKNOWN CHAR\n"); break;
            case TOKEN_ASSIGNMENT_OP: printf("ASSIGNMENT OP\n"); break;
            case TOKEN_SEP: printf("SEP\n"); break;
            case TOKEN_OP: printf("OP\n"); break;
            case TOKEN_COMMENT: printf("COMMENT\n"); break;
            default: printf("...\n");
        }
    }


    exit(EXIT_SUCCESS);
}