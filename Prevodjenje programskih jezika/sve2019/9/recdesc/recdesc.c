/*
1. Naivna gramatika
program -> program naredba ';'
		| naredba ';'
		;
naredba -> ID '=' E
		| PRINT_T E
		| CARD E
		;
E -> E UNIJA_T T
	| T
	;
T -> T RAZLIKA_T F
	| T PRESEK_T F
	| F
	;
F -> '(' E ')'
	| '~' F
	| skup
	| ID
	;
skup -> '{' lista '}'
	;
lista -> lista ',' BROJ
	| BROJ
	;
	
1. Eliminacija leve rekurzije				4. Skupovi izbora
											
program -> naredba ';' programP					ID, PRINT, CARD
	;
programP -> naredba ';' programP				ID, PRINT, CARD			
	| eps										EOI
	;
naredba -> ID '=' E								ID
		| PRINT_T E								PRINT
		| CARD E								CARD
		;
E -> T EP										'(', '{', '~', ID					
	;
EP -> UNIJA_T T EP								UNIJA_T
	| eps										';', ')'
	;
T -> F TP										'(', '{', '~', ID
	;
TP -> PRESEK_T F TP								PRESEK_T
	| RAZLIKA_T F TP							RAZLIKA_T
	| eps										UNIJA_T, ';'
	;
F -> '(' E ')'									'('
	| '~' F										'~'
	| skup										'{'
	| ID										ID
	;
skup -> '{' lista '}'							'{'
	;
lista -> BROJ listaP							BROJ
	;
listaP -> ',' BROJ listaP						','
	| eps										'}'
	;

3. First i Follow skupovi
					First				Eps			Follow
program			ID, PRINT, CARD			/			EOI
programP		ID, PRINT, CARD			DA			EOI
naredba			ID, PRINT, CARD			/			';'
E 				'(', '{', '~', ID		/			';', ')'
EP				UNIJA_T					DA			';', ')'
T				'(', '{', '~', ID		/			UNIJA_T, ';'
TP				PRESEK_T, RAZLIKA_T		DA			UNIJA_T, ';'
F				'(', '{', '~', ID		/			PRESEK_T, RAZLIKA_T, UNIJA, ';'
skup			'{'						/			PRESEK_T, RAZLIKA_T, UNIJA, ';'
lista			BROJ					/			'}'
listaP			','						DA			'}'

*/
#include "tokeni.h"

int preduvid = 0;
extern int yylex();

void program(void);
void programP(void);
void naredba(void);
void E(void);
void EP(void);
void T(void);
void TP(void);
void F(void);
void skup(void);
void lista(void);
void listaP(void);

int main(){
	
	preduvid = yylex();
	
	program();
	
	if (preduvid == EOI) {
		printf("sve je ok\n");
	}
	else {
		printf("visak tokena na ulazu\n");
	}
	
	exit(EXIT_SUCCESS);
}

void program(void) {
	if (preduvid == ID || preduvid == CARD_T || preduvid == PRINT_T) {
		
		naredba();
		if (preduvid != TZ)
			exit(EXIT_FAILURE);
		preduvid = yylex();
		programP();
	}
	else {
		exit(EXIT_FAILURE);
	}
}

void programP(void) {
	if (preduvid == ID || preduvid == CARD_T || preduvid == PRINT_T) {
		
		naredba();
		if (preduvid != TZ)
			exit(EXIT_FAILURE);
		preduvid = yylex();
		programP();
	}
	else if (preduvid == EOI) {
		
		return;
	}
	else {
		exit(EXIT_FAILURE);
	}
}

void naredba(void) {
		
	if (preduvid == PRINT_T) {
		preduvid = yylex();
		E();
	}
	else if (preduvid == ID) {
		preduvid = yylex();
		if (preduvid != JEDNAKO)
			exit(EXIT_FAILURE);
		preduvid = yylex();
		E();
	}
	else if (preduvid == CARD_T) {
		preduvid = yylex();
		E();
	}
	else {
		exit(EXIT_FAILURE);
	}
}

void E(void) {
	if (preduvid == OZ || preduvid == OVZ || preduvid == ID || preduvid == KOMPLEMENT_T) {
		
		T();
		EP();
	}
	else {
		exit(EXIT_FAILURE);
	}
}


void EP(void) {
	
	if (preduvid == UNIJA_T) {
		
		preduvid = yylex();
		T();
		EP();
	}
	else if (preduvid == ZZ || preduvid == TZ) {
		return;
	}
	else {
		exit(EXIT_FAILURE);
	}
}


void T(void) {
	
	if (preduvid == OZ || preduvid == OVZ || preduvid == ID || preduvid == KOMPLEMENT_T) {
		
		F();
		TP();
	}
	else {
		exit(EXIT_FAILURE);
	}
}
void TP(void) {
	if (preduvid == PRESEK_T) {
		preduvid = yylex();
		F();
		TP();
	}
	else if (preduvid == RAZLIKA_T) {
		preduvid = yylex();
		F();
		TP();
	}
	else if (preduvid == UNIJA_T || preduvid == TZ) {
		return;
	}
	else {
		
		exit(EXIT_FAILURE);
	}
}

void F(void) {
	
	if (preduvid == ID) {
		
		preduvid = yylex();
	}
	else if (preduvid == OVZ) {
		
		skup();
	}
	else if (preduvid == KOMPLEMENT_T) {
		
		preduvid = yylex();
		F();
	}
	else if (preduvid == OZ) {
		
		preduvid = yylex();
		E();
		if (preduvid != ZZ)
			exit(EXIT_FAILURE);
		preduvid = yylex();
	}
	else {
		exit(EXIT_FAILURE);
	}
}

void skup(void) {
	
	if (preduvid == OVZ) {
		
		preduvid = yylex();
		lista();
		if (preduvid != ZVZ)
			exit(EXIT_FAILURE);
		preduvid = yylex();
	}
	else {
		exit(EXIT_FAILURE);
	}
}

void lista(void) {
	if (preduvid == BROJ) {
		
		preduvid = yylex();
		listaP();
	}
	else {
		
		exit(EXIT_FAILURE);
	}
}

void listaP(void) {
	
	if (preduvid == Z) {
		
		preduvid = yylex();
		if (preduvid != BROJ)
			exit(EXIT_FAILURE);
		
		preduvid = yylex();
		listaP();
	}
	else if (preduvid == ZVZ) {
		
		return;
	}
	else {
		exit(EXIT_FAILURE);
	}
}
