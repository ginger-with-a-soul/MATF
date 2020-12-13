CFLAGS = -Wall -Wextra -std=c++11 -o

exec: lex.yy.o parser.tab.o
	g++ $(CFLAGS) $@ $^

lex.yy.o: lex.yy.c parser.tab.hpp
	g++ -c $(CFLAGS) $@ $<

lex.yy.c: lexer.lex parser.tab.hpp
	flex $<

parset.tab.o: parser.tab.cpp parser.tab.hpp
	g++ -c $(CFLAGS) $@ $<

parser.tab.cpp parser.tab.hpp: parser.ypp
	bison -v -d $<

.PHONY: clean
clean:
	@rm -rf *.cpp *.o *.hpp *.c exec parser.output