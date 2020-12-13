FINAL = highlight
STEP = lex.yy.c
CFLAGS = -Wall -Wextra -o

$(FINAL): $(STEP) colors.h
	gcc $(CFLAGS) $@ $<
$(STEP): 1.lex
	flex -o $@ $<
.PHONY: clean
clean:
	@rm $(FINAL) $(STEP)