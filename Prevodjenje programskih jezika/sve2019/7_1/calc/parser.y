%{

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern int yylex();

void yyerror(char *s) {

	fprintf(stderr, "Sintaksna greska: %s\n", s);
	exit(EXIT_FAILURE);
}

#define INIT_CAP 	(32)
#define STEP		(2)

typedef struct {
	char* ime;
	float v;
} data_t;

data_t* promenljive;
int capacity = 0;
int n = 0;

void alociraj(){
	
	capacity = INIT_CAP;
	n = 0;
	promenljive = malloc(capacity*sizeof(data_t));
	if (promenljive == NULL)
		yyerror("Alokacija");
}

void dealociraj(){

	int i = 0;
	
	for (i = 0; i < n; i++) {
	
		free(promenljive[i].ime);
	}
	
	free(promenljive);
}

int pronadji(char* ime) {

	int i = 0;
	for (i = 0; i < n; i++) {
		if (!strcmp(ime, promenljive[i].ime))
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

%token PRINT PRINT_ALL LEQ NEQ EQ GEQ
%token<v> BROJ
%token<ime> ID

%type<v> izraz

%start program

%%
program: niz_naredbi
	;

niz_naredbi: niz_naredbi naredba ';' 
	| naredba ';'
	;
naredba:PRINT_ALL			{
								int i = 0;
								for (i = 0; i < n; i++) {
									printf("%s = %.2f\n", promenljive[i].ime, promenljive[i].v);
								}
							}
	| PRINT '(' izraz ')'	{printf("%.2f\n", $3);}
	| ID '=' izraz 			{
								int retVal = pronadji($1);
								if (retVal != -1) {
									promenljive[retVal].v = $3;
								}
								else {
									promenljive[n].ime = strdup($1);
									promenljive[n].v = $3;
									
									n++;
									
									if (n == capacity) {
										
										capacity *= STEP;
										promenljive = realloc(promenljive, capacity*sizeof(data_t));
										if (promenljive == NULL)
											yyerror("Realokacija\n");
									}
								}
								free($1);
							}
	| izraz '<' izraz		{ 
								if ($1 < $3) 
									printf("DA\n");
								else
									printf("NE\n");
							}
	| izraz '>' izraz		{ 
								if ($1 > $3) 
									printf("DA\n");
								else
									printf("NE\n");
							}
	| izraz EQ izraz		{ 
								if ($1 == $3) 
									printf("DA\n");
								else
									printf("NE\n");
							}
	| izraz NEQ izraz		{ 
								if ($1 != $3) 
									printf("DA\n");
								else
									printf("NE\n");
							}
	| izraz LEQ izraz		{ 
								if ($1 <= $3) 
									printf("DA\n");
								else
									printf("NE\n");
							}
	| izraz GEQ izraz		{ 
								if ($1 >= $3) 
									printf("DA\n");
								else
									printf("NE\n");
							}
	;
izraz: izraz '+' izraz		{ $$ = $1 + $3;}
	| izraz '-' izraz		{ $$ = $1 - $3;}
	| izraz '*' izraz		{ $$ = $1 * $3;}
	| izraz '/' izraz		{ $$ = $1 / $3;}
	| '-' izraz %prec UMINUS	{$$ = -$2;}
	| '(' izraz ')'	{ $$ = $2; }
	| ID			{
						int retVal = pronadji($1);
						if (retVal == -1)
							yyerror("Ne postoji promenljiva\n");
							
						$$ = promenljive[retVal].v;
						
						free($1);
					}
	| BROJ			{ $$ = $1;}
	;

%%

int main(){

	alociraj();

	if (yyparse() == 0)
		printf("OK\n");
	else
		printf("Nije OK\n");
		
	dealociraj();	
		
	exit(EXIT_SUCCESS);
}
