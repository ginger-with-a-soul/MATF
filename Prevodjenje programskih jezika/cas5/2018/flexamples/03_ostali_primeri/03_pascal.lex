%option noyywrap
%option nounput
%option noinput

%{ // asdasdasdasdads
%}
%%
"{"[^}]*"}" { }

"(*"([^*]|"*"[^)])*"*)" {}
%%
int main()
{
    yylex();
    return 0;
}
