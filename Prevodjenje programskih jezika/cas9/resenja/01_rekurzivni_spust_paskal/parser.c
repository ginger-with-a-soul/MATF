/***************************
 * Gramatika kojom je obuhvacen deo sintakse
 * programskog jezika Paskal, ilustrovan primerom
 *
 * naredba --> WHILE uslov DO naredba
 *           | IF uslov THEN naredba
 *           | ID := izraz
 *           | BEGIN niznaredbi END
 *           | eps
 *
 * uslov --> LZ izraz ROP izraz DZ
 * izraz --> ID
 *         | BROJ
 * niznaredbi --> niznaredbi TZ naredba
 *              | naredba
 *
 * Moramo da se oslobodimo leve rekurzije iz poslednjeg pravila gramatike
 * Neka je aksioma gramatike neterminal niznaredbi!
 *
 * naredba --> WHILE uslov DO naredba
 *           | IF uslov THEN naredba
 *           | ID DTJ izraz
 *           | BEGIN niznaredbi END
 *           | eps
 *s
 * uslov --> LZ izraz ROP izraz RZ
 * izraz --> ID
 *         | BROJ
 *
 * niznaredbi --> naredba nizp
 * nizp --> TZ naredba nizp
 *        | eps
 *
 * Skupovi Prvi i Sledi
 *                           Prvi                       Sledi
 * niznaredbi | eps     |   {WHILE,IF,ID,BEGIN,;}   |   {EOI,END}
 * nizp       | eps     |   {;}                     |   {EOI,END}
 * naredba    | eps     |   {WHILE,IF,ID,BEGIN}     |   {;,EOI,END}
 * uslov      |  /      |   {LZ}                    |   {THEN,DO}
 * izraz      |  /      |   {ID, BROJ}              |   {ROP,RZ,;,EOI,END}
 *
 * Odredjujemo skupove izbora
 * niznaredbi --> naredba nizp           {WHILE,IF,ID,BEGIN,TZ,EOI,END}  jer je niznaredbi anulirajuci simbol
 * nizp --> TZ naredba nizp              {TZ}
 *        | eps                          {EOI,END}
 * naredba --> WHILE uslov DO naredba    {WHILE}
 *           | IF uslov THEN naredba     {IF}
 *           | ID DTJ izraz              {ID}
 *           | BEGIN niznaredbi END      {BEGIN}
 *           | eps                       {TZ,EOI,END}
 * uslov --> LZ izraz ROP izraz DZ       {LZ}
 * izraz --> ID                          {ID}
 *       | BROJ                          {BROJ}
 *
 ***************************/

#include <stdio.h>
#include <stdlib.h>
#include "tokeni.h"

#define _DEBUG

int preduvid;

/* F-ja ispisuje gresku i prekida program */
void greska(char* s)
{
    fprintf(stderr,"%s\n",s);
    exit(EXIT_FAILURE);
}

extern int yylex();

void niznaredbi();
void naredba();
void nizp();
void uslov();
void izraz();

void niznaredbi()
{
    if (preduvid == WHILE_TOKEN || preduvid == IF_TOKEN || preduvid == ID || preduvid == BEGIN_TOKEN || preduvid == TZ || preduvid == EOI || preduvid == END_TOKEN) {
#ifdef _DEBUG
        printf("niznaredbi-->naredba nizp\n");
#endif
        naredba();
        nizp();
    } else
        greska("Sintaksna greska! Ocekivano je nesto od: WHILE,IF,ID,BEGIN,TZ,EOI,END");
}

void naredba()
{
    if (preduvid == WHILE_TOKEN) {
#ifdef _DEBUG
        printf("naredba--> WHILE uslov DO naredba\n");
#endif
        preduvid = yylex();
        uslov();
        if (preduvid != DO_TOKEN)
            greska("Sintaksna greska! Ocekivano DO!");

        preduvid = yylex();
        naredba();
    } else if (preduvid == IF_TOKEN) {
#ifdef _DEBUG
        printf("naredba--> IF uslov THEN naredba\n");
#endif
        preduvid = yylex();
        uslov();
        if (preduvid != THEN_TOKEN)
            greska("Sintaksna greska! Ocekivano THEN!");
        preduvid = yylex();
        naredba();
    } else if(preduvid == ID) {
#ifdef _DEBUG
        printf("naredba--> ID DTJ izraz\n");
#endif
        preduvid = yylex();
        if (preduvid != DTJ)
            greska("Sintaksna greska! Ocekivano :=!");
        preduvid = yylex();
        izraz();
    } else if (preduvid ==BEGIN_TOKEN) {
#ifdef _DEBUG
        printf("naredba--> BEGIN niznaredbi END\n");
#endif
        preduvid = yylex();
        niznaredbi();
        if (preduvid != END_TOKEN)
            greska("Sintaksna greska! Ocekivano END!");
        preduvid =yylex();
    } else if(preduvid == TZ || preduvid == EOI || preduvid == END_TOKEN) {
#ifdef _DEBUG
        printf("naredba --> eps\n");
#endif
        return;
    } else {
        char pom[256];
        sprintf(pom,"Sintaksna greska! Neocekivan token %d!", preduvid);
        greska(pom);
    }
}

void nizp()
{
    if (preduvid == TZ) {
#ifdef _DEBUG
        printf("nizp --> TZ naredba nizp\n");
#endif
        preduvid = yylex();
        naredba();
        nizp();
    } else if (preduvid == EOI || preduvid == END_TOKEN) {
#ifdef _DEBUG
        printf("nizp--> eps\n");
#endif
        return;
    } else
        greska("Sintaksna greska! Ocekivano je: TZ ili EOI,ili END!");
}

void uslov()
{
    if (preduvid == LZ) {
#ifdef _DEBUG
        printf("uslov--> LZ izraz ROP izraz DZ\n");
#endif
        preduvid = yylex();
        izraz();
        if (preduvid != ROP)
            greska("Sintaksna greska! Ocekivano ROP!");
        preduvid = yylex();
        izraz();
        if (preduvid != DZ)
            greska("Sintaksna greska! Ocekivano DZ!");
        preduvid = yylex();
    } else
        greska("Sintaksna greska! Ocekivana je LZ!");
}

void izraz()
{
    if (preduvid == ID ) {
#ifdef _DEBUG
        printf("izraz--> ID\n");
#endif
        preduvid =yylex();
    } else if(preduvid ==BROJ) {
#ifdef _DEBUG
        printf("izraz--> BROJ\n");
#endif
        preduvid =yylex();
    } else
        greska("Sintaksna greska! Ocekivano je ID ili BROJ!");
}

int main()
{
    preduvid = yylex();

    niznaredbi();

    if (preduvid != EOI)
        greska("Visak tokena na ulazu!");

    return 0;
}
