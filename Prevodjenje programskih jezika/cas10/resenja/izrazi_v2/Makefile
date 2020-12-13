TARGET = izrazi_v2
CXX = g++
CFLAGS=-Wall -std=c++11


	
$(TARGET): parser.tab.o lex.yy.o
	$(CXX) $(CFLAGS) -o $@ $^

lex.yy.o: lex.yy.c parser.tab.hpp
	$(CXX) $(CFLAGS) -c -o $@ $<
	
lex.yy.c: lexer.lex parser.tab.hpp
	flex $<

parser.tab.o: parser.tab.cpp parser.tab.hpp
	$(CXX) $(CFLAGS) -c -o $@ $<

parser.tab.cpp parser.tab.hpp: parser.ypp
	bison -d -v $<


.PHONY: clean

clean:
	rm $(TARGET) lex.yy.* *.tab.* *.output *~ 
	
	
