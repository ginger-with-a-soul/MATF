#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

/*
    Gramatika je:
    E -> E+T
      |  T
    T -> T*F
      |  F
    F -> (E)
      |  num

    Moramo se obavezno osloboditi leve rekurzije pravila  skupovi izbora
    E -> TE'    { num , ( }
    E'-> +TE'   { + }
      |  eps    { ) , EOI }
    T -> FT'    { ( , num }
    T'-> *FT'   { * }
       | eps    { + , ) , EOI }
    F -> (E)    { ( }
      |  num    { num }
    Skupove izbora smo dobili za sva pravila koja nisu epsilon
    na osnovu skupova FIRST, a za epsilon pravila na osnovu
    skupova FOLLOW
*/

// Deklarisemo tokene koji nam se javljaju u gramatici
#define NUM 1
#define PLUS 2
#define ZVEZDA 3
#define OZ 4            // otvorena zagrada
#define ZZ 5            // zatvorena zagrada
#define EOI 0           // end of inpit

// uvodimo sledeci define, samo ako hocemo da nam program ispise izvodjenje
#define ISPIS 1

// Spoljasnja promenljiva koja ce predstvljati preduvidni token
int lookahead;

// Za svaki neterminal deklarisemo po jednu funkciju
// Prvo navodimo deklaracije, pa zatim definicije.
void E();
void EP();
void T();
void TP();
void F();

// Funkcija za obradu greske
void greska(char *poruka)
{
    fprintf(stderr, "%s\n", poruka);
    exit(EXIT_FAILURE);
}

// Sami cemo isprogramirati leksicki alalizator,
// a kasnije, u slozenijim primerima cemo koristiti
// sistem lex
int yylex()
{
    int ch = getchar();
    switch (ch) {
        case '+': return PLUS;
        case '*': return ZVEZDA;
        case '(': return OZ;
        case ')': return ZZ;
        case '\n':
        case EOF: return EOI;
    }
    // Ako je procitani karakter cifra, citamo sve naredne karaktere,
    // do pojave necega sto nije cifra, u cilju da procitano broj
    if (isdigit(ch)) {
        while (isdigit(ch = getchar()));
        // Ono poslednje sto smo procitali, i sto nije cifra, vracamo na ulaz
        ungetc(ch, stdin);
        return NUM;
    }
    // Ako se na ulazu nije pojavilo nista od ovoga, onda prekidamo program,
    // i ispisujemo propratnu poruku
    greska("Leksicka greska: Nepoznat ulaz");
    return -1;
}

// definicija funkcije koja odgovara neterminalu E
void E()
{
    // Ako nam se na ulazu nadje terminal num ili ( , primenjujemo pravilo E->TE'
    if (lookahead == NUM || lookahead == OZ) {
#ifdef ISPIS
        printf("E->TE'\n");
#endif
        T();
        EP();
    }
    /* Ako nam se na ulazu naslo nesto drugo, prijavljujemo gresku i neuspesno zavrsavamo prigram */
    else
        greska("Sintaksna greska: Ocekivano je na ulazu num ili )");
}

/* definicija funkcije koja odgovara neterminalu EP */
void EP()
{
    // Ako nam sa na ulazu pojavi PLUS, primenjujemo pravilo E'->+TE'
    if (lookahead == PLUS) {
#ifdef ISPIS
        printf("E'->+TE'\n");
#endif
        lookahead = yylex();
        T();
        EP();
    }
    // Ako nam se na ulazu pojavi EOI, ili ) , primenjujemo pravilo E'->eps
    else if (lookahead == EOI || lookahead == ZZ) {
#ifdef ISPIS
        printf("E'->eps\n");
#endif
        // Ovde ide prazna akcija, jer je to epsilon pravilo
    }
    /* U slucaju bilo cega drugog, prekidamo program, uz odgovarajucu poruku */
    else
        greska("Sintaksna greska: Ocekivano je na ulazu +, ) ili kraj ulaza");
}

// definicija funkcije koja odgovara neterminalu T
void T()
{
    // Ako nam sa na ulazu pojavi ( ili num primenjujemo pravilo T->FT'
    if (lookahead == OZ || lookahead == NUM) {
#ifdef ISPIS
        printf("T->FT'\n");
#endif
        F();
        TP();
    } else
        greska("Sintaksna greska: Ocekivano je na ulazu ( ili num");
}

// Definicija funkcije koja odgovara neterminalu T'
void TP()
{
    // Ako nam se na ulazu nasla ZVEZDA, primenjujemo pravilo T'->*FT'
    if (lookahead == ZVEZDA) {
#ifdef ISPIS
        printf("T'->*FT'\n");
#endif
        lookahead = yylex();
        F();
        TP();
    }
    // Ako nam se na ulazu nadje +, ) ili kraj ulaza, primenjujemo pravilo T'->eps
    else if (lookahead == PLUS || lookahead == ZZ || lookahead == EOI) {
#ifdef ISPIS
        printf("T'->eps\n");
#endif
    } else
        greska("Sintaksna greska: Ocekivano je na ulazu *, +, ), ili kraj ulaza");
}

// Definicija funkcije koja odgovara neterminalu F
void F()
{
    // Ako ne na ulazu pojavila (, primenjujemo pravilo F->(E)
    if (lookahead == OZ) {
#ifdef ISPIS
        printf("F->(E)\n");
#endif
        lookahead = yylex();
        E();
        // proveravamo da li je sledeci karakter ), jer to mora da bude ako nije doslo do greske
        if (lookahead == ZZ)
            lookahead = yylex();
        else
            greska("Ocekivana na ulazu zatvorena zagrada");
    } else if (lookahead == NUM) {
#ifdef ISPIS
        printf("F->num\n");
#endif
        lookahead = yylex();
    } else
        greska("Sintaksna greska: Ocekvano na ulazu ( ili num");
}


// U main funkciji ucitavamo prvi karakter, i pozivamo funkciju koja ce nam
// naci izvodjenje sa startni simbol S
int main()
{
    lookahead = yylex();
    E();
    if (lookahead != EOI)
        greska("Sintaksna greska: Visak tokena na ulazu");
    return 0;
}
