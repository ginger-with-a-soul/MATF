EXEC = nums
FLAGS = -Wall -Wextra -std=c++14

$(EXEC): numbers.o lex.yy.o parser.tab.o
	g++ $(FLAGS) $^ -o $@

numbers.o: numbers.cpp numbers.hpp
	g++ $(FLAGS) -c $< -o $@

lex.yy.o: lex.yy.c
	g++ $(FLAGS) -c $< -o $@

lex.yy.c: lexer.lex parser.tab.hpp
	flex $<

parser.tab.o: parser.tab.cpp
	g++ $(FLAGS) -c $< -o $@

parser.tab.cpp parser.tab.hpp: parser.ypp
	bison -v -d $<

.PHONY: clean
clean:
	rm -rf *.o* $(EXEC) *.c *.tab.*