SOURCE = 08_syntax_highlight.lex
PROGRAM = lexer
CC = gcc
CFLAGS = -Wall

# Dodajemo 08_colors.h u listu zavisnosti, jer pri menjanju njega
# zelimo da ponovo pokrenemo kompilaciju.
$(PROGRAM): lex.yy.c 08_colors.h
	$(CC) $(CFLAGS) -o $@ $<

lex.yy.c: $(SOURCE)
	flex $<

.PHONY: clean

clean:
	rm lex.yy.c $(PROGRAM) *.o
