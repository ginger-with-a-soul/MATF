GOAL = izvrsni

$(GOAL): lex.yy.o parser.o
	gcc -Wall -o $@ $^

parser.o: parser.c tokeni.h
	gcc -c -Wall $<

lex.yy.o: lex.yy.c tokeni.h
	gcc -c -Wall lex.yy.c

lex.yy.c: lexer.l
	flex $<

.PHONY: clean

clean:
	rm *.o lex.yy.c $(GOAL)
