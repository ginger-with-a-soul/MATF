%option noyywrap
%option nounput
%option noinput

%{
#define TOKEN_INT 1
#define TOKEN_REAL 2
%}
DIGIT [0-9]

%%
[+-]?{DIGIT}+ {
    return TOKEN_INT;
}
[+-]?{DIGIT}+"."{DIGIT}*([Ee][+-]?{DIGIT}+)? {
    return TOKEN_REAL;
}
%%
int main(int argc, char** argv){

    if(argc > 1){
        yyin = fopen(argv[1], "r");
        if(yyin == NULL){
            printf("Los yyin\n");
            exit(EXIT_FAILURE);
        }
    }

    if(argc > 2){
        yyout = fopen(argv[2], "w");
        if(yyout == NULL){
            printf("Los yyout\n");
            exit(EXIT_FAILURE);
        }
    }

    int token;

    while((token = yylex())){
        switch(token){
            case TOKEN_INT: printf("INT\n"); break;
            case TOKEN_REAL: printf("REAL\n"); break;
            default: printf("Ni INT ni REAL\n");
        }
    }

    fclose(yyin);
    fclose(yyout);

    exit(EXIT_SUCCESS);
}
