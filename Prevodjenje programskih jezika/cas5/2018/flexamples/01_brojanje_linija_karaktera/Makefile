# 'brojac': cilj
# Nakon dvotacke ide 'lista zavisnosti' od koje 'cilj' zavisi.
# Kako bi dobili izvrsivu datoteku 'brojac' moramo da imamo dostupnu datoteku
# 'lex.yy.c' koju generise sistem flex.
#
# Pravilo koje definise kako se dobija cilj:
# gcc -Wall -o $@ $<
#
# $@ <=> cilj (treba izbegavati da ponavljamo isti string vise puta)
# $< <=> prvi element liste zavisnosti (ovde je to 'lex.yy.c')
# Dakle: gcc -Wall -o brojac lex.yy.c
brojac: lex.yy.c
	gcc -Wall -o $@ $<

lex.yy.c: 01_brojanje_linija_karaktera.lex
	flex $<
