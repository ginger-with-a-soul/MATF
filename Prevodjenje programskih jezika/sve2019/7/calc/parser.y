%{

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern int yylex();

void yyerror(char* s) {
	fprintf(stderr, "Sintaksna greska: %s\n", s);
	exit(EXIT_FAILURE);
}

#define INIT_CAPACITY (32)
#define STEP (2)

typedef struct {
	char* ime;
	float v;
} prom_t;

prom_t* promenljive;
int capacity = INIT_CAPACITY;
int n = 0;

void alociraj(){
	
	capacity = INIT_CAPACITY;
	n = 0;
	
	promenljive = malloc(capacity*sizeof(prom_t));
	if (promenljive == NULL) {
		yyerror("Aloakcija");
		exit(EXIT_FAILURE);
	}
}

void dealociraj(){
	
	int i = 0;
	
	for (int i = 0; i < n; i++) {
		free(promenljive[i].ime);
	}
	
	free(promenljive);
}

int pronadji(char* s) {
	
	for (int i = 0; i < n; i++) {
		if (!strcmp(s, promenljive[i].ime))
			return i;
	}
	
	return -1;
}

%}

%union{
	float v;
	char* ime;
}

%left '+' '-'
%left '*' '/'
%right UMINUS

%token EQ NEQ GEQ LEQ PRINT
%token<v> BROJ
%token<ime> ID

%type<v> e

%start niz_naredbi

%%

niz_naredbi: niz_naredbi naredba ';'	{ }
	| naredba ';'						{ }
	;
naredba: PRINT '(' e ')'	{ printf("%.2f\n", $3); }
	| ID '=' e				{ 
								int retVal = pronadji($1);
								if (retVal != -1) {
								
									promenljive[retVal].v = $3;
								}
								else {
									promenljive[n].ime = strdup($1);
									if (promenljive[n].ime == NULL) {
										yyerror("parser strdup");
										exit(EXIT_FAILURE);
									}
									promenljive[n].v = $3;
									
									n++;
									
									if (n == capacity) {
									
										capacity*=STEP;
										promenljive = realloc(promenljive, capacity*sizeof(prom_t));
										if (promenljive == NULL) {
											yyerror("realloc");
											exit(EXIT_FAILURE);
										}
									}
								}
								free($1);
							}
	| e '<' e				{ 
								if ($1 < $3)
									printf("da\n");
								else 
									printf("ne\n");
							}
	| e '>' e				{  
								if ($1 > $3)
									printf("da\n");
								else 
									printf("ne\n");
							}
	| e LEQ e				{  
								if ($1 <= $3)
									printf("da\n");
								else 
									printf("ne\n");
							}
	| e GEQ e				{  
								if ($1 >= $3)
									printf("da\n");
								else 
									printf("ne\n");
							}
	| e NEQ e				{  
								if ($1 != $3)
									printf("da\n");
								else 
									printf("ne\n");
							}
	| e EQ e				{ 
								if ($1 == $3)
									printf("da\n");
								else 
									printf("ne\n"); 
							}
	;
e:    e '+' e	{ $$ = $1 + $3;}
	| e '-' e 	{ $$ = $1 - $3;}
	| e '*' e	{ $$ = $1 * $3;}
	| e '/' e	{ $$ = $1 / $3;}
	| '-' e	%prec UMINUS { $$ = -$2;}
	| '(' e ')'	{ $$ = $2;}
	| ID		{ 
					int retVal = pronadji($1);
					if (retVal == -1) {
						yyerror("Nije definisana promenljiva");
						exit(EXIT_FAILURE);
					}
					$$ = promenljive[retVal].v;
					free($1);
				}
	| BROJ		{ $$ = $1;}
	;

%%

int main() {
	
	alociraj();
	
	if (yyparse() == 0)
		printf("OK\n");
	else 
		printf("Nije OK\n");
	
	dealociraj();	
	
	exit(EXIT_SUCCESS);
}
