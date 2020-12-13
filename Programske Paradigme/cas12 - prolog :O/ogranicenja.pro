/*
1. generisanje promenljivih i njihovih domena
2. generisanje ogranicenja nad tim promeljivih
3. instanciranje promenljivih -> generisanje resenja

1.
	X in D
	X :: D
	Vars in D
	Vars :: D

Domen:
	[pocetak..korak..kraj]
		[1..2..11] -> [1, 3, 5, 7, 9, 11]
Predikati za ogranicenja:
	*Opsta ogranicenja:
		- alldifferent(Vars), alldistinct(Vars)
		- atmost(Num, ListOfTersm, Term)
		- atleast(Num, ListOfTerms, Term)
		- exactly(Num, ListOfTerms, Term)
	*Aritmeticka:
		- E1 R E2 (E1, E2 aritmeticki izrazi, R: #=, #>, #<, #>=, #=<, #\=)
		- min(ListOfTerms) (min(E1, E2))
		- max(ListOfTersm) (max(E1, E2))
		- sum(L) (mora da bude summable)

3. instanciranje (labeliranje) promenljivih:
	labeling(Options, Vars)
		*Options = [] (default)
				 = [minimize[E (E is INT)], maximize[E]]
*/

%1. Petocifren broj ABCDE za koji je izraz A+2*B-3*C+4*D-5*E minimalan
%a A, B, C, D, E razlicite cifre
%zbog toga sto nema (Vars) pored imena, daje samo jedno resenja (u ovom)
%slucaju samo jedno i postoji
petocifren :- Vars = [A, B, C, D, E],
					A :: 1..9,
					[B, C, D, E] :: 0..9,
					alldifferent(Vars),
					labeling([minimize(A+2*B-3*C+4*D-5*E)], Vars),
					Number is 10000 * A + 1000 * B + 100 * C + 10 * D + E,
					write(Number), nl.
	
%2. Magicni kvadrat(3x3 matrica gde je suma vrsta, kolona i dijagonala 15)
magicni(Vars) :- Vars = [X1, X2, X3, X4, X5, X6, X7, X8, X9],
		Vars :: 1..9,
		alldifferent(Vars),
		X1 + X2 + X3 #= 15,
		X4 + X5 + X6 #= 15,
		X7 + X8 + X9 #= 15,
		X1 + X4 + X7 #= 15,
		X2 + X5 + X8 #= 15,
		X3 + X6 + X9 #= 15,
		X1 + X5 + X9 #= 15,
		X3 + X5 + X7 #= 15,
		labeling(Vars),
		write(X1), write(' '), write(X2), write(' '), write(X3), nl,
		write(X4), write(' '), write(X5), write(' '), write(X6), nl,
		write(X7), write(' '), write(X8), write(' '), write(X9), nl.

%3. osmosmerka
%   T W O
% + T W O
% -------
% F O U R

osmosmerka(Vars) :- Vars = [T, W, O, F, U, R],
					Vars :: 0..9,
					T #\= 0,
					F #\= 0,
					alldifferent(Vars),
					2 * (100 * T + 10 * W + O) #= 1000 * F + 100 * O + 10 * U + R,
					labeling(Vars),
					write('  '), write(T), write(' '), write(W), write(' '), write(O), nl,
					write('+ '), write(T), write(' '), write(W), write(' '), write(O), nl,
					write('-------'), nl,
					write(F), write(' '), write(O), write(' '), write(U), write(' '), write(R), nl, nl, fail.

%4. Pekara "Kifilca"
%H(300g brasna, 10 minuta), K(120g brasna, 12 minuta) (broj komada)
%brasna: 20 000g
%	H: 20 000 / 300 == 66,67
%	K: 20 000 / 120 == 166,67
%vremena: 20h == 1200 minuta
%	H: 1200 / 10 == 120
%	K: 1200 / 12 == 100
% H -> 0..66
% K -> 0..100
kiflica :- Vars = [H, K],
					H :: 0..66,
					K :: 0..100,
					300 * H + 120 * K #=< 20000,
					10 * H + 12 * K #=< 1200,
					labeling([maximize(H * 7 + K * 9)], Vars),
					Zarada is H * 7 + K * 9,
					write('Zarada je: '), write(Zarada), nl,
					write('Odnosno '), write(H), write('H, '), write(K), write('K').