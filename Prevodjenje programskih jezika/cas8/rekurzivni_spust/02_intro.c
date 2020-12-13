#include <stdio.h>
#include <stdlib.h>

/*
    Gramatika je:
    A -> Aa
      |  b
    Moramo se obavezno osloboditi leve rekurzije,
    jer u tom slucaju, neka od funkcija ce zapasti u beskonacnu rekurziju.
    pravila skupovi izbora
    A -> bA'    {b}
    A'-> aA'    {a}
      |  eps   {EOI}
*/

// Deklarisemo tokene koji nam se javljaju u gramatici
#define a 1
#define b 2
#define EOI 0           // end of input

// Funkcija koja obradjuje greske
void greska(char *poruka)
{
    fprintf(stderr, "%s\n", poruka);
    exit(1);
}

// Spoljasnja promenljiva koja ce predstvljati preduvidni karakter
int lookahead;

// Za svaki neterminal deklarisemo po jednu funkciju
// Prvo navodimo deklaracije, pa zatim definicije.
void A();
void AP();

// Sami cemo isprogramirati leksicki alalizator,
// a kasnije, u slozenijim primerima cemo koristiti
// sistem lex
int yylex()
{
    int ch = getchar();
    switch (ch) {
        case 'a': return a;
        case 'b': return b;
        case '\n':
        case EOF: return EOI;
        default: greska("Leksicka greska");
    }
    return -1;
}

// definicija funkcije koja odgovara neterminalu A
void A()
{
    // Ako nam se na ulazu nadje terminal b, primenjujemo pravilo A->bA'
    if (lookahead == b) {
        printf("A->bA'\n");
        lookahead = yylex();
        AP();
    }
    // Ako nam se na ulazu naslo nesto drugo, prijavljujemo gresku i neuspesno zavrsavamo program
    else
        greska("Sintaksna greska: Ocekivano je na ulazu b!");
}

// definicija funkcije koja odgovara neterminalu A'
void AP()
{
    // Ako nam sa na ulazu pojavi a, primenjujemo pravilo A'->aA'
    if (lookahead == a) {
        printf("A'->aA'\n");
        lookahead = yylex();
        AP();
    }
    // Ako nam se na ulazu pojavi kraj ulaza EOI, primenjujemo pravilo A'->eps
    else if (lookahead == EOI) {
        printf("A'->eps\n");
    }
    // U slucaju bilo cega drugog, prekidamo program, uz odgovarajucu poruku
    else
        greska("Sintaksna greska: Ocekivano je na ulazu a ili kraj ulaza!");
}

// U main funkciji ucitavamo prvi karakter, i pozivamo funkciju koja ce nam
// naci izvodjenje sa startni simbol A
int main()
{
    lookahead = yylex();
    A();
    if (lookahead != EOI)
        greska("Sintaksna greska: Visak tokena na ulazu");
    return 0;
}
