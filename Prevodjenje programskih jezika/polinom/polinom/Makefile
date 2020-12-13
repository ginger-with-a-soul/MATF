izvrsni: lex.yy.c y.tab.c polinom.c
	gcc -o izvrsni -Wall -lm lex.yy.c y.tab.c polinom.c


lex.yy.c : lexer.l y.tab.h
	flex lexer.l

y.tab.c y.tab.h: parser.y
	yacc -d -v parser.y