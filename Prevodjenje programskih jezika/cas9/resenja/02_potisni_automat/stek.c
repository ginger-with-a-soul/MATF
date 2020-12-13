#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
/*******************************
 *  Gramatika je:
 *  E -> E+T
 *    | T
 *  T -> T*F
 *    | F
 *  F -> (E)
 *   | num
 *  Moramo se obavezno osloboditi leve rekurzije
 *  pravila  skupovi izbora
 *  E -> TE'     { num , ( }
 *  E'-> +TE'    { + }
 *    | eps      { ) , EOI }
 *  T -> FT'     { ( , num }
 *  T'-> *FT'    { * }
 *    |eps       { + , ) , EOI }
 *  F -> (E)     { ( }
 *    | num       { num }
 *  Skupove izbora smo dobili za sva pravila koja nisu epsilon
 *  na osnovu skupova FIRST, a za epsilon pravila na osnovu
 *  skupova FOLLOW
 *******************************/

/* Deklarisemo tokene koji nam se javljaju u gramatici */
#define NUM 1
#define PLUS 2
#define ZVEZDA 3
#define OZ 4            /* otvorena zagrada */
#define ZZ 5            /* zatvorena zagrada */
#define EOI 0           /* end of inpit */

#define E 6
#define EP 7
#define T 8
#define TP 9
#define F 10

/* uvodimo sledeci define, samo ako hocemo da nam program ispise izvodjenje */
#define ISPIS 1

/* Spoljasnja promenljiva koja ce predstvljati preduvidni token */
int lookahead;

/* Funkcija za obradu greske */
void greska(char *poruka)
{
    fprintf(stderr, "%s\n", poruka);
    exit(EXIT_FAILURE);
}

/* Sami cemo isprogramirati leksicki alalizator,
 * a kasnije, u slozenijim primerima cemo koristiti
 * sistem lex
 */
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
    /* Ako je procitani karakter cifra, citamo sve naredne karaktere,
     * do pojave necega sto nije cifra, u cilju da procitano broj
     */
    if (isdigit(ch)) {
        while (isdigit(ch = getchar()));
        /* Ono poslednje sto smo procitali, i sto nije cifra, vracamo na ulaz */
        ungetc(ch, stdin);
        return NUM;
    }
    /* Ako se na ulazu nije pojavilo nista od ovoga, onda prekidamo program,
     * i ispisujemo propratnu poruku
     */
    greska("Leksicka greska: Nepoznat ulaz");
    return -1;
}

#define MAX 256

int stek[MAX];
int sp = 0;

int empty()
{
    return sp == 0;
}

int full()
{
    return sp >= MAX;
}

int pop()
{
    if (empty())
        greska("Stek je prazan, ne mozemo da uradimo pop()");
    return stek[--sp];
}

void push(int x)
{
    if (full())
        greska("Stek je pun, ne mozemo da radiomo push()");
    stek[sp++] = x;
}

int peek()
{
    if (empty())
        greska("Stek je prazan, ne mozemo da radimo peek()");
    return stek[sp-1];
}

void advance()
{
    lookahead = yylex();
}

int match(int x)
{
    return lookahead == x;
}

int main()
{
    advance();
    push(E);

    while (!empty()) {
        switch (peek()) {
            case E:
                if (match(NUM) || match(OZ)) {
#ifdef ISPIS
                    printf("E -> TE'\n");
#endif
                    pop();
                    push(EP);
                    push(T);
                } else
                    greska("Ocekivano je na ulazu NUM ili (");
                break;
            case EP:
                if (match(PLUS)) {
#ifdef ISPIS
                    printf("E' -> +TE'\n");
#endif
                    pop();
                    push(EP);
                    push(T);
                    push(PLUS);
                } else if (match(ZZ) || match(EOI)) {
#ifdef ISPIS
                    printf("E' -> eps\n");
#endif
                    pop();
                } else
                    greska("Ocekicano je na ulazu +, ) ili kraj ulaza");
                break;
            case T:
                if (match(NUM) || match(OZ)) {
#ifdef ISPIS
                    printf("T -> FT'\n");
#endif
                    pop();
                    push(TP);
                    push(F);
                } else
                    greska("Ocekivano je na ulazu NUM ili (");
                break;
            case TP:
                if (match(ZVEZDA)) {
#ifdef ISPIS
                    printf("T' -> *FT'\n");
#endif
                    pop();
                    push(TP);
                    push(F);
                    push(ZVEZDA);
                } else if (match(PLUS) || match(ZZ) || match(EOI)) {
#ifdef ISPIS
                    printf("T' -> eps\n");
#endif
                    pop();
                } else
                    greska("Ocekivano je na ulazu *, +, ) ili kraj ulaza");
                break;
            case F:
                if (match(NUM)) {
#ifdef ISPIS
                    printf("F -> num\n");
#endif
                    pop();
                    push(NUM);
                } else if (match(OZ)) {
#ifdef ISPIS
                    printf("F -> (E)\n");
#endif
                    pop();
                    push(ZZ);
                    push(E);
                    push(OZ);
                } else
                    greska("Ocekivano je na ulazu NUM ili (");
                break;
            default:
                if (match(peek())) {
                    pop();
                    advance();
                } else {
                    char poruka[MAX];
                    sprintf(poruka, "Ocekivano je na ulazu %s",
                            peek() == NUM ? "NUM":
                           (peek() == PLUS ? "+":
                           (peek() == ZVEZDA ? "*":
                           (peek() == OZ ? "(": ")"))));
                    greska(poruka);
                }
        }
    }

    if (!match(EOI))
        printf("Visak tokena na ulazu\n");
    else
        printf("Prepoznat aritmeticki izraz\n");

    return 0;
}
