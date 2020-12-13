/*
   E  -> TE'                     { (, BROJ }     { E.v = E'.v , E'.nasledjen = T.v}
   E' -> + T {print +} E'        { + }           { E'1.v = E'2.v , E'2.nasledjen = E'1.nasledjen + T.v }
   | - T {print - } E'       { - }           { E'1.v = E'2.v , E'2.nasledjen = E'1.nasledjen - T.v
   | eps                     { ), EOI }      { E'1.v = E'1.nasledjen }
   T  -> FT'                     { BROJ, ( }     { T.v = T'.v }
   T' -> * F {print *} T'        { * }           { T'1.v = T'2.v, T'2.nasledjen = T'1.nasledjen * F.v }
   | eps                     { +, -, ), EOI}    { T'1.v = T'1.nasledjen }
   F  -> BROJ {print BROJ.v }    { BROJ }        { F.v = BROJ.v}
   | (E)                     { ( }           { F.v = E.v }

   Nasledjen atribut se propagira od korena prema listovima stabla, a sintetizovani od listova prema korenu.
   Nasledjene atribute prosledjujemo funkcijama preko argumenta,
   a sintetizovani funkcije vracaju preko povratnih vrednosti.

   Dakel kako se sintaksna analiza radi sa leva na desno tako se vrednost izraza racuna
   i vrednost pocetnog dela izraza propagira se preko argumenta funkcijama kojima je potreban
   */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "tokeni.h"

// #define ISPIS 1

int preduvid;
int E();
int EP(int nasledjen);
int T();
int TP(int nasledjen);
int F();

int yylval;
extern int yylex();

int main() {
    preduvid = yylex();
    int vrednost = E();

    if (preduvid == EOI) {
        printf("\n\nRecenica odgovara jeziku zadatim gramatikom!\n");
        printf("\nVrednost izraza je %d\n", vrednost);
    } else
        printf("\nPrevise tokena na ulazu!\n");

    return 0;
}

int E()
{
    if (preduvid == OZ || preduvid == BROJ) {
#ifdef ISPIS
        printf("E -> TE'\n");
#endif
        int rezultat = T();
        return EP(rezultat);
    } else {
        fprintf(stderr, "Sintaksna greska u e(): Ocekivano je (, broj, a pojavilo se %d\n", preduvid);
        exit(EXIT_FAILURE);
    }
}

int EP(int nasledjen)
{
    if (preduvid == PLUS) {
#ifdef ISPIS
        printf("E' -> +TE'\n");
#endif
        preduvid = yylex();
        int rezultat = nasledjen + T();
        printf("+ ");
        return  EP(rezultat);
    }
    else if( preduvid == MINUS) {
#ifdef ISPIS
        printf("E' -> -TE'\n");
#endif
        preduvid = yylex();
        int rezultat = nasledjen - T();
        printf("- ");
        return EP(rezultat);
    } else if (preduvid == ZZ || preduvid == EOI) {
#ifdef ISPIS
        printf("E' -> eps\n");
#endif
        return nasledjen;
    } else {
        fprintf(stderr, "Sintaksna greska u ep(): Ocekivano je +,-,),EOI, a pojavilo se %d\n", preduvid);
        exit(EXIT_FAILURE);
    }
}

int T()
{
    if (preduvid == BROJ || preduvid == OZ) {
#ifdef ISPIS
        printf("T -> FT'\n");
#endif
        int rezultat = F();
        return TP(rezultat);
    } else {
        fprintf(stderr, "Sintaksna greska u t(): Ocekivano je (, broj, a pojavilo se %d\n", preduvid);
        exit(EXIT_FAILURE);
    }
}

int TP(int nasledjen)
{
    if (preduvid == PUTA) {
#ifdef ISPIS
        printf ("T' -> *FT'\n");
#endif
        preduvid = yylex();
        int rezultat = nasledjen * F();
        printf("* ");
        return TP(rezultat);
    } else if (preduvid == PODELJENO) {
#ifdef ISPIS
        printf ("T' -> /FT'\n");
#endif
        preduvid = yylex();
        int rezultat = nasledjen / F();
        printf("/ ");
        return TP(rezultat);
    } else if (preduvid == PLUS || preduvid == MINUS ||  preduvid == ZZ || preduvid == EOI) {
#ifdef ISPIS
        printf("T' -> eps\n");
#endif
        return nasledjen;
    } else {
        fprintf(stderr, "Sintaksna greska u tp(): Ocekivano je *,,/+, -,),EOI, a pojavilo se %d\n", preduvid);
        exit(EXIT_FAILURE);
    }
}

int F()
{
    if (preduvid == BROJ) {
#ifdef ISPIS
        printf("F -> BROJ\n");
#endif
        int rezultat = yylval;
        printf("%d ", yylval);
        preduvid = yylex();
        return rezultat;
    } else if (preduvid == OZ) {
#ifdef ISPIS
        printf("F -> (E)\n");
#endif
        preduvid = yylex();
        int rezultat = E();
        if (preduvid == ZZ)
            preduvid = yylex();
        else {
            fprintf(stderr, "Sintaksna greska u f(): Ocekivano je ), a pojavilo se %d\n", preduvid);
            exit(EXIT_FAILURE);
        }
        return rezultat;
    } else {
        fprintf(stderr, "Sintaksna greska u f(): Ocekivano je (, BROJ, a pojavilo se %d\n", preduvid);
        exit(EXIT_FAILURE);
    }
}

// e=>t ep =>f tp ep => BROJ tp ep => BROJ ep => BROJ + t ep => BROJ + f tp ep =>
//   => BROJ + BROJ tp ep => BROJ + BROJ * f tp ep => BROJ + BROJ * BROJ tp ep
//   => BROJ + BROJ* BROJ
