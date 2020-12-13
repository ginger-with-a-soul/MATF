/* 					Skupovi izbora				Akcije
 * E  -> T EP		OZ, BROJ					e.v = ep.v, ep.n = t.v 
 * EP -> + T EP		PLUS						ep1.v = ep2.v, ep2.v = ep.n + t.v
 * 		 - T EP		MINUS						ep1.v = ep2.v, ep2.v = ep.n - t.v
 * 		 eps		Z, EOI						ep1.v = ep1.n
 * T  -> F TP		OZ, BROJ					t.v = tp.v
 * TP -> * F TP		*							tp1.v = tp2.v, tp2.v = tp.n * f.v
 * 		 / F TP		/							tp1.v = tp2.v, tp2.v = tp.n / f.v
 * 		eps			PLUS, MINUS, ZZ, EOI		tp1.v = ep1.n
 * F  -> ( E )		OZ							f.v = e.v
 * 		 BROJ		BROJ						f.v = Broj.v
 */
 #include "tokeni.h"
 
 int preduvid = 0;
 int yyval = 0;
 extern int yylex();
 
 int e(void);
 int ep(int nasledjen);
 int t(void);
 int tp(int nasledjen);
 int f(void);
 
 int main(){
	 
	 preduvid = yylex();
	 int rez = e();
	 
	 if (preduvid == EOI) {
		 
		 printf("Recenica je u jeziku.\n");
		 printf("Vrednost izraza je: %d\n", rez);
	 }
	 else {
		 printf("Recenica nije u jeziku\n");
	 }
	 
	 exit(EXIT_SUCCESS);
 } 


 int e(void) {
	 
	 if (preduvid == OZ || preduvid == BROJ) {
		 
		 int rez = t();
		 return ep(rez);
	 }
	 else {
		 check_error("Ocekivano je...");
	 }
 }
 
 int ep(int nasledjen) {
	 
	 if (preduvid == PLUS) {
		 
		 preduvid = yylex();
		 int rez = nasledjen + t();
		 
		 return ep(rez);
	 }
	 else if (preduvid == MINUS) {
		 
		 preduvid = yylex();
		 int rez = nasledjen - t();
		 
		 return ep(rez);
	 }
	 else if (preduvid == ZZ || preduvid == EOI) {
		 
		 return nasledjen;
	 }
	 else {
		 check_error("....");
	 }
 }
 
 int t(void) {
	 
	 if (preduvid == BROJ || preduvid == OZ) {
		 
		 int rez = f();
		 return tp(rez);
	 }
	 else {
		 check_error("....");
	 }
 }
 
 int tp(int nasledjen) {
	 
	 if (preduvid == PUTA) {
		 
		 preduvid = yylex();
		 int rez = nasledjen*f();
		 return tp(rez);
	 }
	 else if (preduvid == DELJENJE) {
		 
		 preduvid = yylex();
		 int rez = nasledjen / f();
		 return tp(rez);
	 }
	 else if (preduvid == PLUS || preduvid == MINUS || preduvid == ZZ || preduvid == EOI) {
		 return nasledjen;
	 }
	 else {
		 check_error("....");
	 }
 }
 
 int f(void) {
	 
	 if (preduvid == BROJ) {
		 
		 int rez = yyval;
		 preduvid = yylex();
		 return rez;
	 }
	 else if (preduvid == OZ) {
		 
		 preduvid = yylex();
		 int rez = e();
		 
		 if (preduvid != ZZ) {
			 check_error("...");
		 }
		 
		 preduvid = yylex();
		 
		 return rez;
	 }
	 else {
		 
		 check_error("....");
	 }
 }
