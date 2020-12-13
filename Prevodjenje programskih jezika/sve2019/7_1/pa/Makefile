parser: parser.o lex.yy.o
	gcc parser.o lex.yy.o -o parser

parser.o: parser.c tokeni.h
	gcc -c parser.c -o parser.o

lex.yy.o: lex.yy.c
	gcc -c lex.yy.c -o lex.yy.o

lex.yy.c: tokeni.h lexer.l
	flex lexer.l
