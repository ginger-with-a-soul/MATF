	/*
 * program -> program naredba ';'
 * 			| naredba ';'
 * naredba -> INT_T ID = E 
 * 			| PRINT '(' E ')' 
 * 			| E 
 * E -> E | T
 * 		| T
 * T -> T & F
 * 		| F
 * F -> ~ G
 * 		| G
 * G -> BROJ
 * 		| '(' E ')'
 * 
 * Eliminacija leve rekurzije:
 * 											Skupovi izbora
 * program -> naredba ';' programP				INT, PRINT, ~, BROJ, (
 * programP -> naredba ';' programP				INT, PRINT, ~, BROJ, (
 * 			| eps								EOI
 * naredba -> INT_T ID = E 						INT
 * 			| PRINT '(' E ')' 					PRINT
 * 			| E 								~, BROJ, (
 * E -> T EP									~, BROJ, (				
 * EP -> | T EP									|
 * 		| eps									;, )
 * T -> F TP									~, BROJ, (
 * TP -> & F TP									&
 * 		| eps									|, ;, )
 * F -> ~ G										~
 * 		| G										BROJ, (
 * G -> BROJ									BROJ
 * 	  | '(' E ')'								(
 * 
 * Skupovi izbora		First					Eps		Follow
 * program			INT, PRINT, ~, BROJ, (		NE		EOI
 * programP			INT, PRINT, ~, BROJ, (		DA		EOI
 * naredba			INT, PRINT, ~, BROJ, (		NE		;
 * E				~, BROJ, (					NE		;, )
 * EP				|							DA		;, )
 * T				~, BROJ, (					NE		|, ;, )
 * TP				&							DA	 	|, ;, )
 * F				~, BROJ, (					NE		&, |, ;, )
 * G				BROJ, (						NE		&, |, ;, )
 */
#include <stdio.h>
#include <stdlib.h>
#include "tokeni.h"

extern int yylex();
int preduvid;

void program(void);
void programP(void);
void naredba(void);
void E(void);
void T(void);
void TP(void);
void EP(void);
void F();
void G();

int main() {
	
	preduvid = yylex();
	
	program();
	
	if (preduvid == EOI) {
		printf("Sve je ok\n");
	}
	
	else {
		printf("program nije u redu\n");
	}
	
	exit(EXIT_SUCCESS);
}

void program(void) {
	
}
void programP(void) {
	
}
void naredba(void) {
	
}
void E(void) {
	
}

void T(void) {
	
}

void TP(void) {
	
}

void EP(void) {
	
}

void F() {
	
}

void G() {
	
}
