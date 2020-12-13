#include <stdio.h>
#include <stdlib.h>

// Ovaj define je stavljen da bi program ispisivao i najlevlje izvodjenje neke recenice
// Ako necemo da se ispisuje izvodjenje, onda samo treba iskomentarisati tu liniju
#define ISPIS 1

/*
    Gramatika je:
    pravila  skupovi izbora
    S -> AB  {a}
       | C   {c}
    A -> a   {a}
    B -> b   {b}
    C -> cS  {c}
    Rekurzivni spust se moze primeniti samo na gramatike
    kod kojih su skupovi izbora disjunktni, tj. LL1 gramatike.
    Moramo se obavezno osloboditi leve rekurzije,
*/

// Deklarisemo tokene koji nam se javljaju u gramatici
#define a 1
#define b 2
#define c 3
#define EOI 0           // end of input

// Funkcija za obradu greske
void greska(const char *errmsg)
{
    fprintf(stderr, "%s\n", errmsg);
    exit(EXIT_FAILURE);
}

// Spoljasnja promenljiva koja ce predstvljati preduvidni karakter
int lookahead;

// Za svaki neterminal deklarisemo po jednu funkciju
// Prvo navodimo deklaracije, pa zatim definicije. Zasto?
void S();
void A();
void B();
void C();

// Sami cemo isprogramirati leksicki alalizator,
// a kasnije, u slozenijim primerima cemo koristiti
// sistem lex
int yylex()
{
    int ch = getchar();
    switch (ch) {
        case 'a': return a;
        case 'b': return b;
        case 'c': return c;
        case '\n':
        case EOF: return EOI;
        default: greska("Leksicka greska");
    }
    return -1;
}

// definicija funkcije koja odgovara neterminalu S
void S()
{
    // Ako nam se na ulazu nadje terminal a, primenjujemo pravilo S->AB
    if (lookahead == a) {
#ifdef ISPIS
        printf("S->AB\n");
#endif
        A();
        B();
    }
    // Ako nam se na ulazu nadje terminal c, primenjujemo pravilo S->C
    else if (lookahead == c) {
#ifdef ISPIS
        printf("S->C\n");
#endif
        C();
    }
    // Ako nam se na ulazu naslo nesto drugo, prijavljujemo gresku i neuspesno zavrsavamo program
    else
        greska("Sintaksna greska: Ocekivano je a ili c");
}

// definicija funkcije koja odgovara neterminalu A
void A()
{
    // Ako nam sa na ulazu pojavi a, primenjujemo pravilo A->a
    if (lookahead == a) {
#ifdef ISPIS
        printf("A->a\n");
#endif
        // Uvek kada imamo neki teminal u pravilima,
        // moramo da ucitamo nesto novo sa ulaza
        lookahead = yylex();
    }
    // U slucaju bilo cega drugog, prekidamo program, uz odgovarajucu poruku
    else
        greska("Sintaksna greska: Ocekivano je na ulazu a");
}

// definicija funkcije koja odgovara neterminalu B
void B()
{
    // Ako nam sa na ulazu pojavi b, primenjujemo pravilo B->b
    if (lookahead == b) {
#ifdef ISPIS
        printf("B->b\n");
#endif
        lookahead = yylex();
    } else
        greska("Sintaksna greska: Ocekivano je na ulazu b");
}

// Definicija funkcije koja odgovara neterminalu C
void C()
{
    /* Ako nam se na ulazu naslo c, primenjujemo pravilo C->cS */
    if (lookahead == c) {
#ifdef ISPIS
        printf("C->cS\n");
#endif
        lookahead = yylex();
        S();
    } else
        greska("Sintaksna greska: Ocekivano je na ulazu c");
}

// U main funkciji ucitavamo prvi karakter, i pozivamo funkciju koja ce nam
// naci izvodjenje sa startni simbol S
int main()
{
    lookahead = yylex();
    S();
    if (lookahead != EOI)
        greska("Sintaksna greska: Visak karaktera na ulazu");
    return 0;
}

