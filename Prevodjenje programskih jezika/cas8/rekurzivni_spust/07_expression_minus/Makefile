parser: parser.c lex.yy.c
	gcc -o parser -Wall parser.c lex.yy.c

lex.yy.c: lexer.l
	flex lexer.l
