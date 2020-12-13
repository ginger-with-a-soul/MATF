/*					Skupovi izbora			Akcije
 * E  -> T EP		(, BROJ					e.v = ep.v, ep.nasledjen = t.v
 * EP -> + T EP		+						ep1.v = ep2.v, ep2.nasledjen = ep1.nasledjen + t.v
 * 		 - T EP		-						ep1.v = ep2.v, ep2.nasledjen = ep1.nasledjen - t.v
 * 		 eps		), EOI					ep1.v = ep1.nasledjen
 * T  -> F TP		(, BROJ					ep.v = tp.v
 * TP -> * F TP		*						tp1.v = tp2.v, tp2.nasledjen = tp.nasledjen*f.v
 * 		 / F TP		/						tp1.v = tp2.v tp2.nasledjen = tp1.nasledjen/f.v	
 * 		 eps		+, -, ), BROJ			tp.v = tp.nasledjen
 * F  -> ( E )		(						f.v = e.v
 *		 BROJ 		BROJ					f.v  = BROJ.v
 */ 
#include "tokeni.h"

#define DEBUG 1

int preduvid = 0;
int yyval = 0;
extern int yylex();

int e();
int ep(int nasledjen);
int t();
int tp(int nasledjen);
int f();

int main(){
	
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

int e() {
	
	if (preduvid == OZ || preduvid == BROJ) {
#ifdef DEBUG
	printf("E -> T EP\n");
#endif	
		int n = t();
		return ep(n);
	}
	else {
		check_error("Ocekivano na ulazu OZ || BROJ");
	}
}

int ep(int nasledjen) {
	
	if (preduvid == PLUS){
#ifdef DEBUG
	printf("EP -> + T EP\n");
#endif			
		preduvid = yylex();
		int rez = nasledjen + t();
		return ep(rez);
	}
	else if (preduvid == MINUS) {
#ifdef DEBUG
	printf("EP -> - T EP\n");
#endif			
		preduvid = yylex();
		int rez = nasledjen - t();
		return ep(rez);
	}
	else if (preduvid == ZZ || preduvid == EOI) {
#ifdef DEBUG
	printf("EP -> eps\n");
#endif			
		return nasledjen;
	}
	else {
		check_error("....");
	}
}

int t() {
	
	if (preduvid == OZ || preduvid == BROJ) {
#ifdef DEBUG
	printf("T -> F TP\n");
#endif	
		int n = f();
		return tp(n);
	}
	else {
		check_error("....");
	}
}

int tp(int nasledjen) {
	
	if (preduvid == PUTA) {
#ifdef DEBUG
	printf("TP -> * F TP\n");
#endif			
		preduvid = yylex();
		int rez = nasledjen*f();
		return tp(rez);
	}
	else if (preduvid == DELJENJE) {
#ifdef DEBUG
	printf("TP -> / F TP\n");
#endif		
		preduvid = yylex();
		int rez = nasledjen/f();
		return tp(rez);
	}
	else if (preduvid == PLUS || preduvid == MINUS || preduvid == ZZ || preduvid == EOI){
#ifdef DEBUG
	printf("TP -> eps\n");
#endif		
		return nasledjen;
	}
	else {
		check_error("....");
	}
}

int f() {
	
	if (preduvid == OZ) {
#ifdef DEBUG
	printf("F -> ( E )\n");
#endif		

		preduvid = yylex();
		int rez = e();
		if (preduvid != ZZ) {
			check_error("....");
		}
		preduvid = yylex();
		return rez;
	}
	else if (preduvid == BROJ) {
#ifdef DEBUG
	printf("F -> BROJ\n");
#endif			
		int tmp = yyval;
		preduvid = yylex();
		return tmp;
	}
	else {
		
		check_error("....");
	}
}
