CFLAGS = -Wall -Wextra -o
TK = tokeni.h

exec: parser.o lex.yy.o
	gcc $(CFLAGS) $@ $^

parser.o: parser.c
	gcc -c $(CFLAGS) $@ $<

lex.yy.o: lex.yy.c
	gcc -c $(CFLAGS) $@ $<

lex.yy.c: lexer.l
	flex $<

.PHONY: clean

clean:
	@rm -rf *.o lex.yy.c