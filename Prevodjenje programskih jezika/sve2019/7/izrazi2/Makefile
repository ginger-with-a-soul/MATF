parser: parser.o lex.yy.o
	gcc parser.o lex.yy.o -o parser

parser.o: parser.tab.c parser.tab.h
	gcc -c parser.tab.c -o parser.o

lex.yy.o: lex.yy.c
	gcc -c lex.yy.c -o lex.yy.o

lex.yy.c: lexer.l parser.tab.h
	flex lexer.l
	
parser.tab.c parser.tab.h: parser.y
	bison -d -v parser.y
	
.PHONY: clean

clean:
	rm parser *.tab.* *.yy.* *.output *.o
