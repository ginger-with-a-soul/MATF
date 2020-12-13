/* 
1. Naivna gramatika

program -> program naredba ';'
	| naredba ';'
	;
naredba -> ID = E
	| print E
	| card E
	;
E -> E UNIJA_T T
	| T
	;
T -> T PRESEK_T F
	| T RAZLIKA_T F
	| F
	;
F -> ID
	| skup
	| '(' E ')'
	| '~' F
	;
skup -> '{' lista '}'
	;
lista -> lista ',' BROJ
	| BROJ
	;

2. Eliminacija leve rekurzije			4. Skupovi izbora

program -> naredba ';' programP				ID, PRINT, CARD	
	;
programP -> naredba ';' programP			ID, PRINT, CARD	
	| eps									EOI
	;
naredba -> ID = E							ID
	| print E								PRINT
	| card E								CARD
	;
E -> T EP									ID, '(', '~', '{'
	;
EP -> UNIJA_T T EP							UNIJA_T
	| eps									';', ')'
	;
T -> F TP									ID, '(', '~', '{'
	;
TP -> PRESEK_T F TP							PRESEK_T
	| RAZLIKA_T F TP						RAZLIKA_T
	| eps									UNIJA_T, ';', ')'
	;
F -> ID										ID
	| skup									'{'
	| '(' E ')'								'('
	| '~' F									'~'
	;
skup -> '{' lista '}'						'{'
	;
lista -> BROJ listaP						BROJ
	;
listaP -> ',' BROJ listaP					','
	| eps									'}'
	;
	
3. First i follow skupovi
	
					First				Eps			Follow
program 		ID, PRINT, CARD			/			EOI	
programP		ID, PRINT, CARD			DA			EOI
naredba			ID, PRINT, CARD			/			';'
E				ID, '(', '~', '{'		/			';', ')'	
EP				UNIJA_T					DA			';', ')'
T				ID, '(', '~', '{'		/			UNIJA_T, ';', ')'
TP				PRESEK_T, RAZLIKA_T		DA			UNIJA_T, ';', ')'
F				ID, '(', '~', '{'		/			PRESEK_T, RAZLIKA_T, UNIJA_T, ';', ')'
skup			'{'						/			PRESEK_T, RAZLIKA_T, UNIJA_T, ';', ')'
lista 			BROJ					/			'}'
listaP			','						DA			'}'
*/
#include "tokeni.h"

#define MAX (256)

int preduvid = 0;
extern int yylex();

int stek[MAX];
int sp = 0;

int full(){
	
	return sp == MAX ? 1 : 0;
}

int empty() {
	
	return sp == 0 ? 1 : 0;
}

void push(int x) {
	
	if (full()) {
		fprintf(stderr, "Stek je pun\n");
		exit(EXIT_FAILURE);
	}
	
	stek[sp++] = x;
}

int peek(){
	if (empty()) {
		fprintf(stderr, "Stek je prazan\n");
		exit(EXIT_FAILURE);
	}
	
	return stek[sp-1];
}

int pop(){
	
	if (empty()) {
		fprintf(stderr, "Stek je prazan\n");
		exit(EXIT_FAILURE);
	}
	
	return stek[--sp];
}

int match() {
	
	return stek[sp-1] == preduvid ? 1 : 0;
}

int advance() {
	
	preduvid = yylex();
}

void greska(void) {
	
	exit(EXIT_FAILURE);
}

int main(){
	
	advance();
	push(PROGRAM);
	
	while (!empty()) {
		
		switch (peek()) {
			
			case PROGRAM:
				if (preduvid == ID || preduvid == CARD_T || preduvid == PRINT_T) {
					pop();
					push(PROGRAM_P);
					push(TZ);
					push(NAREDBA);
				}
				else {
					greska();
				}
				break;
			case PROGRAM_P:
				if (preduvid == ID || preduvid == CARD_T || preduvid == PRINT_T) {
					pop();
					push(PROGRAM_P);
					push(TZ);
					push(NAREDBA);
				}
				else if (preduvid == EOI) {
					pop();
				}
				else {
					greska();
				}
				break;
			case NAREDBA:
				if (preduvid == ID) {
					pop();
					push(E);
					push(JEDNAKO);
					push(ID);
				}
				else if (preduvid == PRINT_T) {
					pop();
					push(E);
					push(PRINT_T);
				}
				else if (preduvid == CARD_T) {
					pop();
					push(E);
					push(CARD_T);
				}
				else {
					greska();
				}
				break;
			case E:
				if (preduvid == OVZ || preduvid == OZ || preduvid == ID || preduvid == KOMPLEMENT){
					pop();
					push(EP);
					push(T);
				}
				else {
					greska();
				}
				break;
			case EP:
				if (preduvid == UNIJA_T) {
					pop();
					push(EP);
					push(T);
					push(UNIJA_T);
				}
				else if (preduvid == TZ || preduvid == ZZ) {
					pop();
				}
				else {
					greska();
				}
				break;
			case T:
				if (preduvid == OVZ || preduvid == OZ || preduvid == ID || preduvid == KOMPLEMENT){
					pop();
					push(TP);
					push(F);
				}
				else {
					greska();
				}
				break;
			case TP:
				if (preduvid == PRESEK_T) {
					pop();
					push(TP);
					push(F);
					push(PRESEK_T);
				}
				else if (preduvid == RAZLIKA_T) {
					pop();
					push(TP);
					push(F);
					push(RAZLIKA_T);
				}
				else if (preduvid == TZ || preduvid == ZZ || preduvid == UNIJA_T) {
					pop();
				}
				else {
					greska();
				}
				break;
			case F: 
				if (preduvid == OVZ) {
					pop();
					push(ZVZ);
					push(SKUP);
					push(OVZ);
				}
				else if (preduvid == KOMPLEMENT) {
					pop();
					push(F);
					push(KOMPLEMENT);
				}
				else if (preduvid == ID) {
					pop();
					push(ID);
				}
				else if (preduvid == OZ) {
					pop();
					push(ZZ);
					push(E);
					push(OZ);
				}
				else {
					greska();
				}
				break;
			case SKUP:
				if (preduvid == OVZ) {
					pop();
					push(ZVZ);
					push(LISTA);
					push(OVZ);
				}
				else {
					greska();
				}
				break;
			case LISTA:
				if (preduvid == BROJ) {
					pop();
					push(LISTA_P);
					push(BROJ);
				}
				else {
					greska();
				}
				break;
			case LISTA_P:
				if (preduvid == Z) {
					pop();
					push(LISTA_P);
					push(BROJ);
					push(Z);
				}
				else if (preduvid == ZVZ){
					pop();
				}
				else {
					greska();
				}
				break;
			default:
				if (match()) {
					pop();
					advance();
				}
				else {
					greska();
				}
				break;
		}
	}
	
	printf("Sve je ok\n");
	
	exit(EXIT_SUCCESS);
}
