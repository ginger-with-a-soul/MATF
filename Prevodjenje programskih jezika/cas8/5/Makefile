CFLAGS = -Wall -Wextra -o
run: lex.yy.o 5c.o
	gcc $(CFLAGS) run lex.yy.o 5c.o

lex.yy.o: lex.yy.c
	gcc -c $(CFLAGS) $@ $<

5c.o: 5c.c
	gcc  -c $(CFLAGS) $@ $<

lex.yy.c: 5.l
	flex 5.l

.PHONY: clean
clean:
	@rm lex.yy.c 5c.o lex.yy.o