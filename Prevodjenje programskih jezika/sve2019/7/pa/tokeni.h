/* E -> E + T
 * 		| T
 * T -> T*F
 * 		| F
 * F -> ( E )
 * 		| broj
 * 
 * -> eliminacija leve rekurzija
 * 					Skupovi izbora
 * E  -> T EP			broj, (
 * EP -> + T EP			+
 * 		| eps			), EOI
 * T - > F TP			broj, (
 * TP -> * F TP			*
 * 		| eps			+, ), EOI
 * F  -> ( E )			(
 * 		| broj 			broj
 */
 #ifndef TOKENI_H
 #define TOKENI_H
 
 #include <stdio.h>
 #include <stdlib.h>
 
 #define check_error(userMsg)\
	do { \
		fprintf(stderr, "Sintaksna greska: %s.\n", userMsg); \
		exit(EXIT_FAILURE); \
	} while (0)
 
 /* definicija tokena */
 #define EOI 	(0)
 #define PLUS	(1)
 #define PUTA	(2)
 #define BROJ	(3)
 #define OZ		(4)
 #define ZZ		(5)
 
 /* definicija neterminala */
 #define E 		(100)
 #define EP		(101)
 #define T		(102)
 #define TP		(103)
 #define F		(104)
 
 #endif
 
