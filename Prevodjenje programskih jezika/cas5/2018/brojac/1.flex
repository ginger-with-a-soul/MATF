%option noyywrap
%option nounput
%option noinput

%{
    unsigned broj_linija = 0;
    unsigned broj_karaktera = 0;
%}

%%
\n {
    broj_linija++;
    broj_karaktera++;
}

. {
    broj_karaktera++;
}
%%
int main(){

    yylex();
    printf("Broj linija: %u\nBroj karaktera: %u\n", broj_linija, broj_karaktera);
    
    return 0;
}