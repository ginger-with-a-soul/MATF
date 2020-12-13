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
int main()
{
    int token;

    while ((token = yylex()))
    {
        switch (token)
        {
            case TOKEN_INTEGER:
                printf("Pronadjena je celobrojna konstantna.\n");
                break;
            case TOKEN_REAL:
                printf("Pronadjena je konstantna u pokretnom zarezu.\n");
                break;
            default:
                printf("Nepoznat token...%d\n", token);
        }
    }
    return 0;
}
