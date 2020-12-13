parser: parser.o lex.yy.o
	gcc parser.o lex.yy.o -o parser

parser.o: potisni_automat.c tokeni.h
	gcc -c potisni_automat.c -o parser.o

lex.yy.o: lex.yy.c
	gcc -c lex.yy.c -o lex.yy.o

lex.yy.c: lexer.l tokeni.h
	flex lexer.l
