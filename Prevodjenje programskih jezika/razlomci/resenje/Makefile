GOAL = fracthon
CXX = g++
FLAGS = -Wall -Wextra -std=c++14

$(GOAL): lex.yy.o parser.tab.o razlomak.o
	$(CXX) $^ $(FLAGS) -o $@ 

lex.yy.o: lex.yy.c
	$(CXX) $< -c $(FLAGS)

parser.tab.o: parser.tab.cpp parser.tab.hpp
	$(CXX) $< -c $(FLAGS)

razlomak.o: razlomak.cpp razlomak.hpp
	$(CXX) $< -c $(FLAGS) -o $@

lex.yy.c: lexer.lex parser.tab.hpp
	flex $<

parser.tab.hpp parser.tab.cpp: parser.ypp
	bison -v -d $<

clean:
	rm -rf *.o parser.tab.* lex.yy.* parser.output $(GOAL)