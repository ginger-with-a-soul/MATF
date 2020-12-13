%option noyywrap
%option noinput
%option nounput

%x comment

%{
    unsigned int broj_linija = 0;
%}

%%
"/*" {
    BEGIN(comment);
}

<comment>[^*\n]* { }

<comment>"*"[^/\n] {
}

<comment>"*"\n { ++broj_linija; }

<comment>\n { ++broj_linija; }

<comment>"*/" {
    BEGIN(INITIAL);
}

\n {
    ++broj_linija;
    ECHO;   // ispisi ono sto si prepoznao
}

. {
    ECHO;
}
%%

int main()
{
    yyin = fopen("06_input.c", "r");
    if (!yyin) { exit(1); }
    yylex();
    printf("Broj linija: %d\n", broj_linija);
    return 0;
}
