/* E - > E + T
 * 		| T
 * T -> T * F
 * 		| F
 * F -> ( E )
 * 		| BROJ
 * 
 * -> eliminacija leve rekurzije
 * 						Skupovi izbora
 * E  -> T EP				BROJ, (
 * EP -> + T EP				+
 * 		| eps				), EOI
 * T  -> F TP				BROJ, (
 * TP -> * F TP				*
 * 		| eps				+, ), EOI
 * F  -> ( E )				(
 * 		| BROJ				BROJ
 */
 #include "tokeni.h"
 
 int preduvid = 0;
 extern int yylex();
 
 #define MAX_SIZE 256
 
 int stek[MAX_SIZE];
 int sp = 0;
 
 int empty(){
	 
	 return sp == 0 ? 1: 0;
 }
 
 int full(){
	 
	 return sp == MAX_SIZE ? 1 : 0;
 }
 
 void push(int x){
	 
	 if (full()) {
		 check_error("stek je pun");
	 }
	 stek[sp++] = x;
 }
 
 int pop(){
	 if (empty()) {
		 check_error("stek je prazan");
	 }
	 return stek[--sp];
 }
 
 int peek(){
	 if (empty()) {
		 check_error("stek je prazan");
	 }
	 return stek[sp - 1];
 }
 
 int match(int x){
	 
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
					
					check_error("Ocekivano je broj ili (.");
				}
				break;
			case EP:
				if (match(PLUS)){
					pop();
					push(EP);
					push(T);
					push(PLUS);
				}
				else if (match(ZZ) || match(EOI)){
					
					pop();
				}
				else {
					
					check_error("Ocekivano je +, ) ili EOI.\n");
				}
				break;
			case T:
				if (match(BROJ) || match(OZ)){
					
					pop();
					push(TP);
					push(F);
				}
				else {
					check_error("Ocekivano je BROJ ili (.");
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
					check_error("Ocekivano je *,+,) ili EOI.");
				}
				break;
			case F:
				if (match(OZ)) {
					
					pop();
					push(ZZ);
					push(E);
					push(OZ);
				}
				else if (match(BROJ)) {
					
					pop();
					push(BROJ);
				}
				else {
					check_error("Ocekivano je broj ili (.");
				}
				break;
			default:
				if (match(peek())) {
					
					pop();
					advance();
				}
				else {
					check_error("Sintaksna greska");
				}
				break;
		}
	}
	
	printf("Izraz je ok\n");
	
	exit(EXIT_SUCCESS); 
 }
