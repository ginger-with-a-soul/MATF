parser: parser.tab.o lex.yy.o broj.o
	g++ -std=c++11 parser.tab.o broj.o lex.yy.o -o parser

broj.o: broj.cpp broj.hpp
	g++ -std=c++11 -c broj.cpp -o broj.o

lex.yy.o: lex.yy.c
	g++ -std=c++11 -c lex.yy.c -o lex.yy.o

parser.tab.o: parser.tab.cpp parser.tab.hpp
	g++ -std=c++11 -c parser.tab.cpp -o parser.tab.o

lex.yy.c: lexer.l parser.tab.hpp
	flex lexer.l

parser.tab.cpp parser.tab.hpp: parser.ypp
	bison -d -v parser.ypp

.PHONY: clean

clean:
	rm *.tab.* *.yy.* parser *.o *.output
