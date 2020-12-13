SOURCE = 03_pascal.lex
PROGRAM = lexer
CC = gcc
CFLAGS = -Wall

$(PROGRAM): lex.yy.c
	$(CC) $(CFLAGS) -o $@ $<

lex.yy.c: $(SOURCE)
	flex $<

.PHONY: clean

clean:
	rm lex.yy.c lexer
