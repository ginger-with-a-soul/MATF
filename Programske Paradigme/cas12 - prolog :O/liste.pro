/* Lista je niz termova. Moze biti prazna [], ili sa nekim elementom.
Sastoji se iz .(G, R) glave liste koja je term i repa koji je lista.
[] - prazna lista
.(a, []) - lista sa 1 elementom
.(a, .(b, [])) - lista sa 2 elementa == [a, b]
[a, b, c] == [G|R] (G = A; R = [b, c])
[a, b, c] == [G, R1|R2]
*/

%1. sadrzi(element, lista)
sadrzi(X, [X|_]) :- !.
sadrzi(X, [_|R]) :- sadrzi(X, R).

sadrziV2(X, [G|R]) :- X == G; sadrziV2(X, R).

%2. duzina(lista, len)
duzina([], 0).
duzina([_|R], D) :- duzina(R, D1), D is D1 + 1.

%3. suma(lista, S)
suma([], 0).
suma([G|R], S) :- number(G), suma(R, S1), S is S1 + G.

%4. aritmeticka_sredina(lista, REZ)
aritmeticka_sredina(L, REZ) :- suma(L, S), duzina(L, D), D > 0, REZ is S/D.

%5. ucitaj(N, L)
%kraj read-a signalizira se tackom
ucitaj(N, _) :- N < 0, !.
ucitaj(0, []):- !.
ucitaj(N, [G|R]) :- N1 is N - 1, write('element: '), read(G), nl, ucitaj(N1, R).

%6. dodajPocetak(X, L, NL)
dodajPocetak(X, L, [X|L]).
%dodajPocetak(X, L, [G2|R2]) :- G2 = X, R2 = L.

%7. dodajKraj(X, L, NL)
%u svakom pozivu kopira se glava prve liste u glavu nove liste
%zatim se to rekurzivno radi za repove obe liste
%kada prva postane prazna, ona ne moze da se podeli na glavu i rep
%tada se samo dodaje element X u novu listu i to u njenu glavu a
%ona je na kraju same liste, tj. poslednji je element
dodajKraj(X, [], [X]).
dodajKraj(X, [G|R], [G|NL]) :- dodajKraj(X, R, NL).

%8. obrisiPrvi(L, NL)
obrisiPrvi([], _) :- fail.
obrisiPrvi([_|R], R).

%9. obrisiPoslednji(L, NL)
obrisiPoslednji([_], []) :- !.
obrisiPoslednji([G|R], [G|NL]) :- obrisiPoslednji(R, NL).

%10. podeli(lista, pozDeoListe, negDeoListe)
%podeli([], [], []) :- !.
%podeli([G|R], [G|PL], NL) :- G >= 0, podeli(R, PL, NL), !.
%podeli([G|R], PL, [G|NL]) :- G < 0, podeli(R, PL, NL).

%11. zameni(X, Y, L, NL)
zameni(_, _, [], []) :- !.
zameni(X, Y, [G|R], [Y|R1]) :- G == X, zameni(X, Y, R, R1), !.
zameni(X, Y, [G|R], [G|R1]) :- zameni(X, Y, R, R1).

%12. mergeSort(L, NL)
mergeSort([], []).
mergeSort([X], [X]) :- !.
mergeSort(L, NL) :- podeli(L, A, B), mergeSort(A, NA), mergeSort(B, NB), spoji(NA, NB, NL).

podeli([], [], []).
podeli([X], [X], []).
podeli([G1,G2|R], [G1|R1], [G2|R2]) :- podeli(R, R1, R2).

spoji(L, [], L).
spoji([], L, L).
spoji([G1|R1], [G2|R2], [G1|R]) :- G1 < G2, spoji(R1, [G2|R2], R).
spoji([G1|R1], [G2|R2], [G2|R]) :- G1 >= G2, spoji([G1|R1], R2, R).