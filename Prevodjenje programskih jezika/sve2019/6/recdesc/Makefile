parser: parser.o lex.yy.o
	gcc lex.yy.o parser.o -o parser

parser.o: parser.c tokeni.h
	gcc -c parser.c -o parser.o

lex.yy.o: lex.yy.c
	gcc -c lex.yy.c -o lex.yy.o

lex.yy.c: lexer.l tokeni.h
	flex lexer.l
