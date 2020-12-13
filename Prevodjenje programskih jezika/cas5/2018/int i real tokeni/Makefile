FINAL = tokeni
STEP = lex.yy.c
CFLAGS = -Wall -Wextra

$(FINAL): $(STEP)
	gcc -o $@ $(CFLAGS) $<
$(STEP): 1.flex
	flex -o $@ $<
.PHONY: clear
clear:
	rm $(FINAL) $(STEP)