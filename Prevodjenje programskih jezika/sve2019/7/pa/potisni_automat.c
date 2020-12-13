#include "tokeni.h"

#define MAX_SIZE (256)

int preduvid = 0;
extern int yylex();

int stek[MAX_SIZE];
int sp = 0;

int empty(){
	
	return sp == 0 ? 1 : 0;
}

int full(){
	
	return sp == MAX_SIZE ? 1 : 0;
}

int pop(){
	
	if (empty()) {
		check_error("Stek je prazan");
	}
	
	return stek[--sp];
}

void push(int s){
	
	if (full()) {
		check_error("Stek je pun");
	}
	
	stek[sp++] = s;
}

int peek(){
	
	if (empty()) {
		check_error("Stek je prazan");
	}
	
	return stek[sp - 1];
}

int match(int x) {
	
	return preduvid == x;
}

void advance(){
	
	preduvid = yylex();
}

int main(){
	
	advance();
	push(E);
	
	while (!empty()) {
		
		switch (peek()) {
			case E:
				if (match(BROJ) || match(OZ)) {
					
					pop();
					push(EP);
					push(T);
				}
				else {
					check_error("Ocekivano je BROJ ili )");
				}
				break;
			case EP:
				if (match(PLUS)) {
					push(EP);
					push(T);
					push(PLUS);
				}
				else if (match(ZZ) || match(EOI)){
					
					pop();
				}
				else {
					check_error("Ocekivano +, ) ili EOI");
				}
				break;
			case T:
				if (match(BROJ) || match(OZ)) {
					
					pop();
					push(TP);
					push(F);
				}
				else {
					check_error("Ocekivano je BROJ ili )");
				}
				break;
			case TP:
				if (match(PUTA)) {
					
					pop();
					push(TP);
					push(F);
					push(PUTA);
				}
				else if (match(PLUS) || match(ZZ) || match(EOI)){
					pop();
				}
				else {
					check_error("Ocekivano je *, +, ) ili EOI");
				}
				break;
			case F:
				if (match(BROJ)) {
					
					pop();
					push(BROJ);
				}
				else if (match(OZ)) {
					pop();
					push(ZZ);
					push(E);
					push(OZ);
				}
				else {
					check_error("Ocekivano da broj ili (");
				}
				break;
			default:
				if (match(peek())){
					pop();
					advance();
				}
				else {
					check_error("Pogresan token na ulazu");
				}
				break;
		}
	}
	
	printf("Prepoznat je izraz\n");
	exit(EXIT_SUCCESS);
}



