FLAGS = -Wall -Wextra -std=c++14

out: parser.o lex.yy.o
	g++ $(FLAGS) $^ -o $@

lex.yy.o: lex.yy.c
	g++ $< -c $(FLAGS)

lex.yy.c: lexer.lex parser.tab.hpp
	flex $(FLAGS) $<

parser.o: parser.tab.cpp parser.tab.hpp
	g++ $< -c $(FLAGS) -o $@

parser.tab.cpp parser.tab.hpp: parser.ypp
	bison -v -d $<

.PHONY: clean
clean
	rm -rf *.o parser.output out *.tab.hpp *.tab.cpp