parser: lex.yy.o parser.tab.o broj.o
	g++ -std=c++11 parser.tab.o lex.yy.o broj.o -o parser

broj.o: broj.cpp broj.hpp
	g++ -std=c++11 -c broj.cpp -o broj.o

lex.yy.o: lex.yy.c
	g++ -std=c++11 -c lex.yy.c -o lex.yy.o

parser.tab.o: parser.tab.cpp
	g++ -std=c++11 -c parser.tab.cpp -o parser.tab.o

lex.yy.c: lexer.l parser.tab.hpp
	flex lexer.l

parser.tab.cpp parser.tab.hpp: parser.ypp
	bison -d -v parser.ypp
