%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "polinom.h"

#define YYDEBUG 1
#define KORAK 5
extern int yylex();

void yyerror(char* s){
  fprintf(stderr,"%s\n",s);
  exit(EXIT_FAILURE);
}

typedef struct {
  char * ime;
  Polinom polinom;
} Promenljiva;

Promenljiva * niz = NULL;
int alocirano = 0;
int broj_promenljivih = 0;


int nadji(char* s ){
  int i; 
  
  for(i=0; i<broj_promenljivih; i++)
    if(strcmp(s,niz[i].ime) == 0)
      return i;
  
  return -1;
}

void definisi(char *s, Polinom * p){
  if(alocirano == broj_promenljivih){
    alocirano += KORAK;
    niz = realloc(niz, sizeof(Promenljiva)* alocirano);
    if(niz == NULL)
      yyerror("realloc za nove promenljive!\n"); 
  }

  niz[broj_promenljivih].ime = strdup(s);
  if(niz[broj_promenljivih].ime == NULL)
    yyerror("strdup za novu promenljive!\n");
    
  niz[broj_promenljivih].polinom = *p;  
  
  broj_promenljivih++;
}


void deinicijalizacija(){
  int i;
  
  for(i=0 ;i<broj_promenljivih; i++)
    free(niz[i].ime);
    
  free(niz);  
}

%}

%union{
  float vrednost;
  Polinom p;
  char * ime;
}

%nonassoc '='
%left '+' '-'
%left '*'
%right UMINUS
%left '\''

%token<vrednost> BROJ
%type<p> listakoef polinom
%token<ime> ID
%%
program : program linija 
  | linija 
  ;
  
linija : polinom '\n'   { ispisi(&$1);}
  | ID ':' '=' polinom '\n' {  int i = nadji($1);
                          if(i == -1) 
                            definisi($1, &$4); 
                          else 
                            niz[i].polinom = $4;
                          free($1);  
                            }
                            
  | polinom '=' '=' polinom  '\n'{  if(jednaki(&$1,&$4) )
                                printf("True");
                               else 
                                printf("False");}
  | polinom '!' '=' polinom '\n' {  if(!jednaki(&$1,&$4) )
                                printf("True");
                               else 
                                printf("False");}     
  | polinom '[' BROJ ']'  '\n'   { printf("%f\n", vrednost(&$1, $3));}                                 
  ;

polinom : '<' listakoef '>'   { $$ = $2; }
  | ID                    {  int i = nadji($1);
                             if(i == -1)
                                yyerror("nedefinisana promenljiva\n");
                             $$ = niz[i].polinom;
                             free($1);
                           }
  | polinom '+' polinom         { $$ = saberi(&$1,&$3);  }
  | polinom '-' polinom         { $$ = oduzmi(&$1,&$3);  }
  | polinom '*' polinom         { $$ = pomnozi(&$1,&$3);  }
  | '-' polinom     %prec UMINUS {$$ = uminus(&$2);}
  | '(' polinom ')'         { $$ = $2;}
  | polinom '\''                {$$ = izvod(&$1);}
  | '$' polinom '|' BROJ    { $$ = integral(&$2,$4);}
  ;   

listakoef : listakoef ',' BROJ   {  $$ = $1;
                                    dodaj_koeficijent(&$$, $3);}
  | BROJ   { $$.stepen = 0;
              $$.koeficijenti[0]= $1; }
              
  ;
  
  /*f : BROJ 
  | polinom '[' BROJ ']'*/
%%

int main(){
  yydebug = 1;
  yyparse();

  deinicijalizacija();
  return 0;
}