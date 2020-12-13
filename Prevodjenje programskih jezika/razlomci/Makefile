FLAGS = -Wall -Wextra -std=c++14

out: razlomak.o lex.yy.o parser.o
	g++ $(FLAGS) $^ -o $@

razlomak.o: razlomci.cpp razlomci.hpp
	g++ $< -c $(FLAGS) -o $@

lex.yy.o: lex.yy.c
	g++ $< -c $(FLAGS)

lex.yy.c: lexer.lex parser.tab.hpp
	flex $<

parser.o: parser.tab.cpp parser.tab.hpp
	g++ $< -c $(FLAGS) -o $@

parser.tab.cpp parser.tab.hpp: parser.ypp
	bison -v -d $<

.PHONY: clean
clean:
	rm -rf *.o parser.output *.tab.hpp *.yy.c out parser.tab.cpp