% ime, sport, dres

sadrzi(X, [X|_]).
sadrzi(X, [G|R]) :- X \== G,
					sadrzi(X, R).

visi(X, Y, [X|R]) :- sadrzi(Y, R).
visi(X, Y, [_|R]) :- visi(X, Y, R).


solverL) :- L = [
					[_, _, _],
					[_, _, _],
					[_, _, _],
					[_, _, zeleni]
				 ],
				sadrzi([janko, rukomet, _], L),
				sadrzi([_, odbojka, zeleni], L),
				sadrzi([marko, _, _], L),
				sadrzi([darko, _, _], L),
				sadrzi([rajko, _, _], L),
				sadrzi([_, fudbal, _], L),
				sadrzi([_, kosarka, _], L),
				sadrzi([_, _, plavi], L),
				sadrzi([_, _, crveni], L),
				sadrzi([_, _, zuti], L),
				visi([_, kosarka, _], [_, fudbal, _], L),
				visi([_, _, crveni], [darko, _, _], L),
				visi([janko, _, _], [marko, _, _], L),
				visi([rajko, _, _], [darko, _, _], L),
				\+sadrzi([darko, fudbal, _], L),
				\+sadrzi([darko, _, crveni], L),
				\+sadrzi([marko, _, plavi], L),
				\+sadrzi([marko, kosarka, _], L),
				\+visi([_, kosarka, _], [_, rukomet, _], L),
				\+sadrzi([rajko, _, plavi], L),
				\+sadrzi([_, fudbal, crveni], L),
				\+sadrzi([janko, _, zuti], L).

