uni(X, Y) :- X = Y.

jed(X, Y) :- X == Y.

op_is(X, Y) :- X is Y. %ako Y ima vrednost, onda X dobija tu vrednost
					   %inace, proverava se da li je X =:= (ar. jednako) Y

abs(X, X) :- X >= 0, !. %! sece dalju pretragu
abs(X, AX) :- X < 0, AX is -X.

musko(dimitrije).
musko(nikola).
musko(valeri).
musko(zlatomir).
musko(milko).

zensko(slavica).
zensko(verica).
zensko(bosanka).
zensko(jelica).

roditelj(valeri, dimitrije).
roditelj(valeri, nikola).
roditelj(slavica, dimitrije).
roditelj(slavica, nikola).
roditelj(bosanka, slavica).
roditelj(zlatomir, slavica).
roditelj(zlatomir, verica).
roditelj(bosanka, verica).
roditelj(milko, valeri).
roditelj(jelica, valeri).


majka(X, Y) :- zensko(X), roditelj(X, Y).
otac(X, Y) :- musko(X), roditelj(X, Y).

brat(X, Y) :- musko(X), roditelj(Z, X), roditelj(Z, Y), X \== Y, !.
braca(X, Y) :- brat(Y, X), braca(X, Z).

sestra(X, Y) :- zensko(X), roditelj(Z, X), roditelj(Z, Y), X \== Y, !.

ujak(X, Y) :- sestra(Z, X), majka(Z, Y), musko(X).

deda(X, Y) :- roditelj(Z, Y), otac(X, Z).

predak(X, Y) :- roditelj(X, Y).
predak(X, Y) :- roditelj(Z, Y), predak(X, Z).