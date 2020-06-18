/*
Rafinerija - B (cena: 2), D(cena: 1)
	ogranicenja: max 600 000 galona
				 galona D / galona B = 2 / 1
				 min 150 000 B
				 max 325 000 D
*/

rafinerija :- Vars = [B, D],
			  D :: 0..325000,
			  B :: 150000..600000,
			  B + D #=< 600000,
			  D / B #= 2,
			  labeling([maximize(2 * B + D)], Vars),
			  Zarada is 2 * B + D,
			  write('Maksimalna zarada je: '), write(Zarada), write(' dolara'), nl,
			  write('Kolicina benzina: '), write(B), write(' galona'), nl,
			  write('Kolicina dizela: '), write(D), write(' galona'), nl.

			  