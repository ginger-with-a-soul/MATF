1: 1.o
	gcc -std=c99 -Wall -Wextra -o 1 1.o
1.o: 1.c
	gcc -std=c99 -Wall -Wextra -c -o 1.o 1.c

2: 2.o
	gcc -std=c99 -Wall -Wextra -o 2 2.o
2.o: 2.c
	gcc -std=c99 -Wall -Wextra -c -o 2.o 2.c

3: 3.o
	gcc -std=c99 -Wall -Wextra -o 3 3.o
3.o: 3.c
	gcc -std=c99 -Wall -Wextra -c -o 3.o 3.c

4: 4.o
	gcc -std=c99 -Wall -Wextra -o 4 4.o
4.o: 4.c
	gcc -std=c99 -Wall -Wextra -c -o 4.o 4.c

5: 5.o
	gcc -std=c99 -Wextra -Wall -o 5 5.o
5.o: 5.c
	gcc -std=c99 -Wextra -Wall -c -o 5.o 5.c

.PHONY: all clean

clean:
	rm -f *~ 1 2 3 4 5  *.o *.txt
all: 1 2 3 4 5