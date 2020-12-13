#ifndef TOKENI_H
#define TOKENI_H

#include <stdio.h>
#include <stdlib.h>

#define check_error(userMsg)\
	do {\
		fprintf(stderr, "%s\n", userMsg);\
		exit(EXIT_FAILURE);\
	} while (0)

/* tokeni */
#define EOI		(0)
#define PLUS	(1)	
#define PUTA	(2)
#define OZ		(3)
#define ZZ		(4)
#define BROJ	(5)

/* simboli, neterminali */
#define E		(100)
#define EP		(101)
#define TP		(102)
#define T		(103)
#define F		(104)

#endif
