CF = -Wall -Wextra -std=c++11 -o

exec: lex.yy.o parser.tab.o
	g++ $(CF) $@ $^

lex.yy.o: lex.yy.c parser.tab.hpp
	g++ -c $(CF) $@ $<

lex.yy.c: lexer.lex parser.tab.hpp
	flex $<

parser.tab.o: parser.tab.cpp parser.tab.hpp
	g++ -c $(CF) $@ $<

parser.tab.cpp parser.tab.hpp: parser.ypp
	bison -d -v $<

.PHONY: clean
clean:
	@rm -rf *.output exec *.cpp *.c *.out *.o *.hpp