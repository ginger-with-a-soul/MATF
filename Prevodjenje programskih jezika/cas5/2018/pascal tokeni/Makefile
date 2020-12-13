FINAL = pascal_tokeni
STEP = lex.yy.c
CFLAGS = -Wall -Wextra

$(FINAL): $(STEP)
	gcc -o $@ $(CFLAGS) $<
$(STEP): 1.lex
	flex -o $@ $<
.PHONY: clear
clear:
	rm $(FINAL) $(STEP)