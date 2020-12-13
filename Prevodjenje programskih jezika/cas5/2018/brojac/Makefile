FINAL = brojac
STEP = lex.yy.c
CFLAGS = -Wall -Wextra

$(FINAL): $(STEP)
	gcc $(CFLAGS) -o $@ $<
$(STEP): 1.flex
	flex -o $@ $<
.PHONY: clean
clean:
	rm $(FINAL) $(STEP)