/*
    Gramatika je:
    E -> E+T
      |  T
    T -> T*F
      |  F
    F -> (E)
      |  BROJ
    Moramo se obavezno osloboditi leve rekurzije
    pravila skupovi izbora
    E -> TE'    { BROJ , ( }
    E'-> +TE'   { + }
      |  eps    { ) , EOI }
    T -> FT'    { ( , BROJ }
    T'-> *FT'   { * }
      |  eps    { + , ) , EOI }
    F -> (E)    { ( }
      |  BROJ   { BROJ }
    Skupove izbora smo dobili za sva pravila koja nisu epsilon
    na osnovu skupova PRVI, a za epsilon pravila na osnovu
    skupova SLEDI

    Zadatak 3.c hocemo da prosirimo tako da program ispisuje
    taj aritmeticki izraz, ali u postfiksnoj notaciji
    Npr 2+3 ispisuje 2 3 +
    Npr 2+3*4 ispisuje 2 3 4 * +
    Akcije koji dodajemo pravilima cemo pisati u okviru pravila
    jer cemo time precizirati kada se akcije izvrsavaju u samom pravilu
    pravila                     skupovi izbora
    E -> TE'                    { BROJ , ( }
    E'-> +T{print(+)}E'         { + }
      |  eps                    { ) , EOI }
    T -> FT'                    { ( , BROJ }
    T'-> *F{print(*)}T'         { * }
      |  eps                    { + , ) , EOI }
    F -> (E)                    { ( }
      |  BROJ{print(BROJ.v)}    { BROJ }
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define BROJ 1
#define PLUS 2
#define PUTA 3
#define LZ 4
#define DZ 5
#define EOI 0

#define ISPIS 1
int preduvid;

void E();
void EP();
void T();
void TP();
void F();

void greska(const char* errmsg)
{
    fprintf(stderr, "%s\n", errmsg);
    exit(EXIT_FAILURE);
}

int yyval;

// samostalno pisemo leksicki analizator
int yylex()
{
    char ch = getchar();
    switch (ch) {
        case '+': return PLUS;
        case '*': return PUTA;
        case '(': return LZ;
        case ')': return DZ;
        case '\n':
        case EOF: return EOI;
    }
    // ako smo procitali cifru
    if (isdigit(ch)) {
        yyval = ch -'0';
        while (isdigit(ch = getchar()))
            yyval = yyval *10 +ch -'0';

        ungetc(ch, stdin);
        return BROJ;
    }

    greska("Leksicka greska: nepoznata leksema!");
    return -1;
}


void E()
{
    if (preduvid == BROJ || preduvid == LZ) {
#ifndef ISPIS
        printf("E -> TE'\n");
#endif
        T();
        EP();
    }
    else
        greska("Sintaksna greska: Ocekivan je token BROJ ili LZ.");
}

void EP()
{
    if (preduvid== PLUS) {
#ifndef ISPIS
    printf("E' -> +TE'\n");
#endif
        preduvid = yylex();
        T();
        printf(" + ");
        EP();
    }
    else if (preduvid == DZ || preduvid == EOI) {
#ifndef ISPIS
        printf("E' -> eps\n");
#endif
        return;
    }
    else
        greska("Sintaksan greska: Ocekivan je token PLUS ili DZ ili EOI");
}

void T()
{
    if(preduvid == LZ || preduvid == BROJ) {
#ifndef ISPIS
        printf("T -> FT'\n");
#endif
        F();
        TP();
    } else
        greska("Sintaksna greska: Ocekivano je LZ ili BROJ.");
}

void TP()
{
    if (preduvid == PUTA) {
#ifndef ISPIS
        printf("T' -> *FT'\n");
#endif
        preduvid = yylex();
        F();
        printf(" * ");
        TP();
    }
    else if(preduvid == PLUS || preduvid == DZ || preduvid == EOI) {
#ifndef ISPIS
        printf("T' -> eps\n");
#endif
        return;
    }
    else
        greska("Sintaksan greska:NEocekivani token");
}

void F()
{
    if (preduvid == LZ) {
#ifndef ISPIS
        printf("F -> (E)\n");
#endif
        preduvid = yylex();
        E();
        if (preduvid == DZ)
            preduvid = yylex();
        else
            greska("Sintaksna greska: Ocekivano je DZ.");
    } else if (preduvid == BROJ) {
#ifndef ISPIS
        printf("F -> BROJ\n");
#endif
        preduvid = yylex();
        printf("%d ",yyval);
        return;
    }
}

int main(){
    preduvid = yylex();

    E();
    if (preduvid!=EOI)
        greska("Sintaksna greska: Visak karaktera na ulazu!");
    return 0;
}

