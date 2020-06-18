get([], _, _) :- fail.
get([G|_], 0, G) :- !.
get([_|R], I, Z) :- I > 0, I1 is I - 1, get(R, I1, Z). 

/*
Ranac:
	i: 0		1		2		3 (pozicija predmeta u listi)
	v: 1000		2000	100		1 (vrednost)
	w: 50		10		5		1 (tezina)
	c: 1		1		1		4 (broj komada)

	Kapacitet ranca = 63
Uslovi: 
	maksimalna vrednost predmeta u rancu
	ne preci kapacitet ranca
	ne uzeti vise komada nekog predmeta nego sto imamo na raspolaganju
*/

ranac(X, Brojaci, Tezine, Vrednosti, Kapacitet) :- Vars = [L, D, P, C],
	get(Brojaci, 0, X0),
	get(Brojaci, 1, X1),
	get(Brojaci, 2, X2),
	get(Brojaci, 3, X3),
	get(Tezine, 0, T0),
	get(Tezine, 1, T1),
	get(Tezine, 2, T2),
	get(Tezine, 3, T3),
	get(Vrednosti, 0, V0),
	get(Vrednosti, 1, V1),
	get(Vrednosti, 2, V2),
	get(Vrednosti, 3, V3),
	L :: 0..X0,
	D :: 0..X1,
	P :: 0..X2,
	C :: 0..X3,
	L * T0 + D * T1 + P * T2 + C * T3 #=< Kapacitet,
	labeling([maximize(L * V0 + D * V1 + P * V2 + C * V3)], Vars),
	Zarada is L * V0 + D * V1 + P * V2 + C * V3,
	Tezina is L * T0 + D * T1 + P * T2 + C * T3,
	Y = [L, D, P, C],
	Z = [],
	append(Y, Z, X),
	write('Zarada: '), write(Zarada), nl,
	write('Tezina: '), write(Tezina), nl. 
