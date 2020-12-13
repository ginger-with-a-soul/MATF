%option noyywrap
%option nounput
%option noinput

%{
    unsigned broj_otvorenih = 0;
%}

%%
"(" {
    broj_otvorenih++;
}

")" {
    if(broj_otvorenih){
        broj_otvorenih--;
    }
    else{
        printf("Vise zatvorenih\n");
        exit(EXIT_FAILURE);
    }
}

\n {}
. {}

%%
int main(){

    yylex();
    if(broj_otvorenih){
        printf("Lose uparene\n");
    }
    else{
        printf("Dobro uparene\n");
    }

    return 0;
}