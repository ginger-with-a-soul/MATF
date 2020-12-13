%option noyywrap
%option nounput
%option noinput

%{
    // Ovaj deo koda se doslovno prenosi u lex.yy.c na sam pocetak.
    // Ovde mozemo ukljucivati zaglavlja koja zelimo da koristimo, i/ili
    // Globalne promenljive koje predstavljaju brojace.

    int broj_linija = 0;
    int broj_karaktera = 0;
%}

%%
\n {
    // Navodimo sistemu lex da kada prepozna novi red
    // izvrsi akciju koja je definisana unutar bloka unutar zagrada {}

    broj_linija++;      // uvecavamo brojac novih redova jer smo naisli na novi red (tj red  se upravo zavrsio)
    broj_karaktera++;   // uvecavamo brojac karaktera jer je novi red karakter
}

. {
    broj_karaktera++;
}
%%
// Treci deo datoteke se doslovno prenosi u lex.yy.c na sami kraj
// U njemu cemo napisati main funkciju
int main()
{
    // Funkciju yylex mozemo prekinuti sa EOF-om (CTRL+D)
    // Ona je dobijena koriscenjem sistema 'flex' i u njoj se nalaze
    // nase reakcije na prepoznate tokene.
    yylex();
    printf("Broj linija: %d\n", broj_linija);
    printf("Broj broj_karaktera: %d\n", broj_karaktera);
    return 0;
}
