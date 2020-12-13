%option noyywrap
%option noinput
%option nounput

%{
#define TOKEN_INTEGER 1
#define TOKEN_REAL 2
%}

DIGIT [0-9]

%%
[+-]?{DIGIT}+ { return TOKEN_INTEGER; }

[+-]?{DIGIT}+\.{DIGIT}*([Ee][+-]?{DIGIT}+)? {
    return TOKEN_REAL;
}

%%
int main(int argc, char* argv[])
{
    if (argc > 1) {
        yyin = fopen(argv[1], "r");
        if (yyin == NULL) {
            fprintf(stderr, "Greska...\n");
            exit(EXIT_FAILURE);
        }
    }
    if (argc > 2) {
        yyout = fopen(argv[2], "w");
        if (yyout == NULL) {
            fprintf(stderr, "Greska...\n");
            exit(EXIT_FAILURE);
        }
    }

    int token;

    while ((token = yylex())) {
        switch (token) {
            case TOKEN_INTEGER:
                fprintf(yyout, "Pronadjena je celobrojna konstantna.\n");
                break;
            case TOKEN_REAL:
                fprintf(yyout, "Pronadjena je konstantna u pokretnom zarezu.\n");
                break;
            default:
                fprintf(yyout, "Nepoznat token...%d\n", token);
        }
    }
    return 0;
}
