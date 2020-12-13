%option noyywrap
%option nounput
%option noinput

%{
    #define TOKEN_INTEGER 1
    #define TOKEN_REAL 2
%}

DIGIT [0-9]

%%

[+-]?{DIGIT}+ {
    return TOKEN_INTEGER;
}

[+-]?{DIGIT}+"."{DIGIT}*([Ee][+-]?{DIGIT}+)? {
    return TOKEN_REAL;
}

%%
int main(){

    int token;
    while((token = yylex())){
        switch(token){
            case TOKEN_INTEGER: printf("Nadjen integer\n"); break;
            case TOKEN_REAL: printf("Nadjen real\n"); break;
            default: printf("Nije ni integer ni real\n");
        }
    }
}