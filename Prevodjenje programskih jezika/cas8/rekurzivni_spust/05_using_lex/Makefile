izvrsni: lex.yy.o 3a.o
	gcc -o izvrsni -Wall lex.yy.o 3a.o

lex.yy.o: lex.yy.c
	gcc -c lex.yy.c

3a.o: 3a.c
	gcc -c 3a.c

lex.yy.c: 3a_la.l
	flex 3a_la.l