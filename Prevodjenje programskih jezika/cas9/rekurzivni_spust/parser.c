#include <stdio.h>
#include <stdlib.h>
#include "tokeni.h"

#define ISPISATI 1

void ispis(const char* msg){
	if(ISPISATI){
		printf("%s\n", msg);
	}
}

void error(const char* userMsg){
	perror(userMsg);
	exit(EXIT_FAILURE);
}


extern int yylex();
int next;

void nn();
void nnp();
void nar();
void usl();
void iz();

int main(){
	next = yylex();
	nn();
	if(next != EOI){
		error("Visak tokena na ulazu");
	}
	exit(EXIT_SUCCESS);
}

void nn(){
	if(next == WHILE_TOKEN || next == IF_TOKEN || next == ID || next == BEGIN_TOKEN || next == TZ || next == EOI || next == END_TOKEN){
		ispis("niz_naredbi --> naredba niz_naredvni'");
		nar();
		nnp();
	}
	else{
		error("Ocekivano: WHILE, IF, ID, BEGIN, END, TZ ili EOI");
	}
}

void nnp(){
	if(next == TZ){
		ispis("niz_naredbni' --> TZ naredba niz_naredbi'");
		next = yylex();
		nar();
		nnp();
	}
	else if(next == END_TOKEN || next == EOI){
		ispis("niz_naredbni' --> eps");
	}
	else{
		error("Ocekivano: TZ, END ili EOI");
	}
}

void nar(){
	if(next == WHILE_TOKEN){
		ispis("naredba --> WHILE uslov DO naredba");
		next = yylex();
		usl();
		if(next == DO_TOKEN){
			next = yylex();
		}
		else{
			error("Ocekivan: DO");
		}
		nar();
	}
	else if(next == IF_TOKEN){
		ispis("naredba --> IF uslov THEN naredba");
		next = yylex();
		usl();
		if(next == THEN_TOKEN){
			next = yylex();
		}
		else{
			error("Ocekivan: THEN");
		}
		nar();
	}
	else if(next == ID){
		ispis("naredba --> ID DTJ izraz");
		next = yylex();
		if(next == DTJ){
			next = yylex();
		}
		else{
			error("Ocekivan: DTJ");
		}
		iz();
	}
	else if(next == BEGIN_TOKEN){
		ispis("naredba --> BEGIN niz_naredbni END");
		next = yylex();
		nn();
		if(next == END_TOKEN){
			next = yylex();
		}
		else{
			error("Ocekivan: END");
		}
	}
	else if(next == TZ || next == EOI || next == END_TOKEN){
		ispis("naredba --> eps");
	}
	else{
		error("Ocekivano: WHILE, IF, ID, BEGIN, TZ, EOI ili END");
	}
}

void usl(){
	if(next == OZ){
		ispis("uslov --> OZ izraz ROP izraz ZZ");
		next = yylex();
		iz();
		if(next == ROP){
			next = yylex();
		}
		else{
			error("Ocekivan: ROP");
		}
		iz();
		next = yylex();
	}
	else{
		error("Ocekivano: OZ");
	}
}

void iz(){
	if(next == ID){
		ispis("izraz --> ID");
		next = yylex();
	}
	else if(next == NUM){
		ispis("izraz --> num");
		next = yylex();
	}
	else{
		error("Ocekivano: ID ili NUM");
	}
}