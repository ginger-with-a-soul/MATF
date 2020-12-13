#include "tokeni.h"

#define DEBUG  (1)

extern int yylex();
int preduvid = 0;
int yyval = 0;

int e(void);
int ep(void);
int t(void);
int tp(void);
int f(void);

int main() {
	
	preduvid = yylex();
	
	int rez = e();
	
	if (preduvid == EOI) {
		
		printf("Recenica je u jeziku.\n");
		printf("Vrednost izraza je: %d\n", rez);
	}
	else {
		
		printf("recenica nije u jeziku\n");
	}
	
	exit(EXIT_SUCCESS);
}

int e(void) {
	
	if (preduvid == OZ || preduvid == BROJ) {
#ifdef	DEBUG
	printf("E -> T EP\n");
#endif
		return t() + ep();
	}
	else {
		check_error("Ocekivano je OZ ili BROJ.");
	}
}

int ep(void) {
	
	if (preduvid == PLUS){
#ifdef	DEBUG
	printf("EP -> + T EP\n");
#endif		
		preduvid = yylex();
		return t() + ep();
	}
	else if (preduvid == ZZ || preduvid == EOI) {
#ifdef	DEBUG
	printf("EP -> eps\n");
#endif		
		return 0;
	}
	else {
		check_error("Ocekivano je PLUS, ZZ ili EOI.");
	}
	
}
int t(void) {
	
	if (preduvid == BROJ || preduvid == OZ) {
#ifdef	DEBUG
	printf("T -> F TP\n");
#endif		
		return f()*tp();
	}
	else {
		
		check_error("Ocekivano je BROJ ili OZ.");
	}
}
int tp(void) {
	
	if (preduvid == PUTA) {
#ifdef	DEBUG
	printf("T -> *F TP\n");
#endif		
		preduvid = yylex();
		return f()*tp();
	}
	else if (preduvid == PLUS || preduvid == ZZ || preduvid == EOI) {
#ifdef	DEBUG
	printf("TP -> eps\n");
#endif		
		return 1;
	}
	else {
		
		check_error("Ocekivano je PLUS, ZZ, EOI");
	}
}
int f(void) {
	
	if (preduvid == OZ) {
#ifdef	DEBUG
	printf("F -> ( E )\n");
#endif		
		preduvid = yylex();
		int tmp  = e();
		if (preduvid != ZZ)
			check_error("Ocekivano je ZZ.");
			
		preduvid = yylex();
		
		return tmp;
	}
	else if (preduvid == BROJ) {
#ifdef	DEBUG
	printf("F -> BROJ\n");
#endif		
		int tmp = yyval;
		preduvid = yylex();
		
		return tmp;
	}
	else {
		check_error("Ocekivano je OZ ili BROJ");
	}
}



