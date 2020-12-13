%1. prestupna(godina)
prestupna(X) :- X mod 4 =:= 0, X mod 100 =\= 0.
prestupna(X) :- X mod 400 == 0.

%2. brdana(mesec, godina, rezultat)
brdana(januar, _, 31).
brdana(mart, _, 31).
brdana(maj, _, 31).
brdana(jul, _, 31).
brdana(avgust, _, 31).
brdana(oktobar, _, 31).
brdana(decembar, _, 31).
brdana(februar, X, 28) :- not(prestupna(X)).
brdana(februar, X, 29) :- prestupna(X).
brdana(april, _, 30).
brdana(jun, _, 30).
brdana(septembar, _, 30).
brdana(novembar, _, 30).

%3. maksimum(A, B, M)
maksimum(A, B, M) :- A >= B, M is A.
maksimum(A, B, M) :- A < B, M is B.

%efikasnije
maksimumV2(A, B, A) :- A >= B, !.
maksimumV2(_, B, B).

%4. suma prvih N prirodnih brojeva(N, S)
suma(1, 1).
suma(N, S) :- N > 1, N1 is N - 1, suma(N1, S1), S is S1 + N.

%5. suma parnih
sumaParnih(2, 2).
sumaParnih(N, S) :- N > 2, N1 is N - 2, sumaParnih(N1, S1), S is S1 + N.

%6. proizvod
proizvod(1, 1).
proizvod(N, P) :- N > 1, N1 is N - 1, proizvod(N1, S1), S is S1 * N.

%7. proizvod parnih
proizvodParnih(2, 2).
proizvodParnih(N, S) :- N > 2, N1 is N - 2, proizvodParnih(N1, S1), S is S1 * N.

%8. cifre(prirodni brojevi)
cifra(0, nula).
cifra(1, jedan).
cifra(2, dva).
cifra(3, tri).
cifra(4, cetiri).
cifra(5, pet).
cifra(6, sest).
cifra(7, sedam).
cifra(8, osam).
cifra(9, devet).

cifre(N) :- N < 0, !.
cifre(N) :- N >= 0, N < 10, cifra(N, R), write(R), nl, !.
cifre(N) :- N >= 10, N1 is (N // 10), cifre(N1), N2 is (N mod 10), cifre(N2).