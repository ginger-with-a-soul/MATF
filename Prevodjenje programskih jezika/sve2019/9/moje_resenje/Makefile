EXEC = set
FLAGS = -Wall -Wextra -std=c++14

$(EXEC): set.o parser.tab.o lex.yy.o
	g++ $(FLAGS) -c $^ -o $@

set.o: set.cpp set.hpp
	g++ $(FLAGS) -c $< -o $@

lex.yy.o: lex.yy.c
	g++ $(FLAGS) -c $< -o $@

lex.yy.c: lexer.lex parser.tab.hpp
	flex $<

parser.tab.o: parser.tab.cpp parser.tab.hpp
	g++ $(FLAGS) -c $< -o $@

parser.tab.cpp parser.tab.hpp: parser.ypp
	bison -v -d $<

.PHONY: clean
clean:
	rm -rf *.tab.* $(EXEC) parser.o* *.yy.*