#include "tokeni.h"

#define DEBUG (1)

int yyval = 0;
int preduvid = 0;
extern int yylex();

int e(void);
int ep(void);
int t(void);
int tp(void);
int f(void);

int main() {
	
	preduvid = yylex();
	
	int rezultat = e();
	
	if (preduvid == EOI) {
		printf("Recenica je u jeziku\n");
		printf("Rezultat je: %d\n", rezultat);
	}
	else {
		printf("Recenica nije u jeziku\n");
	}
	
	exit(EXIT_SUCCESS);
}


int e(void) {
	
	if (preduvid == OZ || preduvid == BROJ) {
#ifdef DEBUG
	printf("E -> T EP\n");;
#endif	
		return t() + ep();
	}
	else {
		check_error("Ocekivano OZ ili BROJ na ulazu.");
	}
}

int ep(void){
	
	if (preduvid == PLUS) {
#ifdef DEBUG
	printf("EP -> + T EP\n");;
#endif	
		preduvid = yylex();
		return t() + ep();		
	}
	else if (preduvid == ZZ || preduvid == EOI) {
#ifdef DEBUG
	printf("EP -> eps\n");;
#endif		
		return 0;
	}
	else {
		check_error("Ocekivano na ulazu PLUS, ZZ ili EOI.");
	}
}

int t(void) {
	
	if (preduvid == OZ || preduvid == BROJ) {
#ifdef DEBUG
	printf("T -> F TP\n");;
#endif		
		return f()*tp();
	}
	else {
		check_error("Ocekivano na ulazu OZ ili BROJ.");
	}
}

int tp(void) {
	
	if (preduvid == PUTA) {
#ifdef DEBUG
	printf("TP -> * F TP\n");;
#endif	
		preduvid = yylex();
		return f()*tp();
	}
	else if ( preduvid == PLUS || preduvid == ZZ || preduvid == EOI) {
#ifdef DEBUG
	printf("TP -> eps\n");;
#endif	
		return 1;
	}
	else {
		check_error("Ocekivano na ulazu PUTA, PLUS, ZZ ili EOI.");
	}
}

int f(void) {
	
	if (preduvid == OZ) {
#ifdef DEBUG
	printf("F -> ( E )\n");;
#endif	
		preduvid = yylex();
		int tmp = e();
		if (preduvid != ZZ) {
			
			check_error("Ocekivano je na ulazu ZZ.");
		}
		preduvid = yylex();
		return tmp;
	}
	else if (preduvid == BROJ) {
#ifdef DEBUG
	printf("F -> BROJ\n");;
#endif		
		preduvid = yylex();
		return yyval;
	}
	else {
		check_error("Ocekivano je na ulazu OZ ili BROJ.");
	}
}
