CF = -Wall -Wextra -c -std=c++11 -o

exec: lex.yy.o parser.tab.o
	g++ -Wall -Wextra -std=c++11 -o $@ $^

lex.yy.o: lex.yy.c parser.tab.hpp
	g++ $(CF) $@ $<

lex.yy.c: lexer.lex parser.tab.hpp
	flex $<

parser.tab.o: parser.tab.cpp parser.tab.hpp
	g++ $(CF) $@ $<

parser.tab.cpp parser.tab.hpp: parser.ypp
	bison -d -v $<

.PHONY: clean
clean:
	@rm -rf *.output exec *.out *.o *.hpp *.cpp *.c