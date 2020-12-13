%option noyywrap
%option noinput
%option nounput

%{
    int broj_otvorenih = 0;
%}

%%
"(" {
    // Navodjenje simbola pod navodnicima skida semantiku regularnih izraza,
    broj_otvorenih++;
}

[)] {
    if (broj_otvorenih == 0) {
        printf("Zagrade nisu korektno uparene.\n");
        exit(1);
    } else broj_otvorenih--;
}

\n { /* Ignorisemo novi red */ }

. { /* Ignorisemo sve ostalo */ }
%%

int main()
{
    yylex();

    if (broj_otvorenih == 0)
        printf("Zagrade se korektno uparene.\n");
    else
        printf("Zagrade nisu korektno uparene.\n");
    return 0;
}
