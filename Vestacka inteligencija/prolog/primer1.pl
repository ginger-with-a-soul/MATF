% negacije uvek stavljati na kraj zbog nacina unifikacije i lenjog izracunavanja
% koje koristi prolog. Pravimo skup resenja a zatim ga negacijama koje su na kraju
% redukujemo do onih koja zadovoljavaju nas uslov

% =======================================================================================
% Logicki zadatak (zapisati tvrdjenja, otkriti ko je udario macku)
%
% Ko je udario macku Tunu?
% Macka je zivotinja.
% Vlasnik psa voli zivotinje.
% Janko ima psa. Marko nema psa.
% Ne bi udario zivotinju ko voli zivotinje.
% Macku bi udario onaj koji bi je mozda udario i nije da je ne bi udario.
% =======================================================================================

% ako zelimo da kazemo da je macka zivotinja ILI pas zivotinja ILI.. - onda samo nabrajamo jedno
% ispod drugog sta je sve zivotinja

macka(tuna).
vlasnik_psa(janko).

mozda_udario(janko, tuna).
mozda_udario(marko, tuna).

zivotinja(X) :- macka(X).
voli_zivotinje(X) :- vlasnik_psa(X).
ne_bi_udario(X, Y) :- voli_zivotinje(X), zivotinja(Y).

bi_udario(X, Y) :- mozda_udario(X, Y), \+(ne_bi_udario(X, Y)).

% sve "funkcije" u prologu su predikati, i kao takvi, uvek bivaju evaluirani na true ili false.
% Zato, kada zelimo da iz predikata vratimo resenje, unutar predikata moramo da prosledimo
% promenljivu koja ce da cuva to resenje

prestupna(G) :- G mod 400 =:= 0.
prestupna(G) :- G mod 4 =:= 0,
				G mod 100 =\= 0.

dana_u_mesecu(januar, _, 31).
dana_u_mesecu(februar, G, 29) :- prestupna(G).
dana_u_mesecu(februar, G, 28) :- \+(prestupna(G)).

% operator "is" je operator klasicne dodele kada radimo sa aritmetickim izrazima
% =:= poredjenje na jednakost, =\= razlicitost, // celobrojno deljenje, mod ostatak
% pri celobrojnom deljenju

abs(X, X) :- X >= 0.
abs(X, Res) :- X < 0, Res is -X.

prirodna_suma(1, 1).
prirodna_suma(N, S) :- N > 1,
					   M is N - 1,
					   prirodna_suma(M, S1),
					   S is N + S1.

suma_cifara(X, X) :- X < 10.
suma_cifara(X, S) :- X >= 10,
					 Y is X // 10,
					 suma_cifara(Y, S1),
					 S is S1 + (X mod 10).

% liste: [G|R]

dodaj_na_pocetak(X, L, [X|L]).


% setamo se po repu i kopiramo nasu listu u novu sve dok ne dodjemo do kraja
% a onda dodamo X
dodaj_na_kraj(X, [], [X]).
dodaj_na_kraj(X, [G|R], [G|NR]) :- dodaj_na_kraj(X, R, NR).

% sadrzi(X, [X|_]).
% sadrzi(X, [_|R]) :- sadrzi(X, R).

% prvo ispraznimo prvu listu a onda samo dopisemo drugu
spoji([], L, L).
spoji([G|R], L, [G|NR]) :- spoji(R, L, NR).


sadrzi(X, [X|_]).
sadrzi(X, [G|R]) :- X \== G,
					sadrzi(X, R).

% prvo "zameni" sluzi kao izlaz iz rekurzije
zameni(_, _, [], []).
zameni(X, Y, [G|R], [G|NR]) :- G \== X, 
							   zameni(X, Y, R, NR).
zameni(X, Y, [X|R], [Y|NR]) :- zameni(X, Y, R, NR).

brisi(_, [], []).
brisi(X, [G|R], [G|NR]) :- X \== G,
						   brisi(X, R, NR).
brisi(X, [X|R], NR) :- brisi(X, R, NR).

sadrzi_uzastopno(X, Y, Z, [X, Y, Z|_]).
sadrzi_uzastopno(X, Y, Z, [_|R]) :- sadrzi_uzastopno(X, Y, Z, R).

podeli_listu_prema_znaku([], [], []).
podeli_listu_prema_znaku([G|R], [G|NR1], NR2) :- G >= 0,
												 podeli_listu_prema_znaku(R, NR1, NR2).
podeli_listu_prema_znaku([G|R], NR1, [G|NR2]) :- G < 0,
												 podeli_listu_prema_znaku(R, NR1, NR2).

% findall(od_cega_zelimo, predikat(od_cega_zelimo,..), u_sta_pakujemo)
% findall pravi listu svih resenja koje neka promenljiva koja ucestvuje u nekom predikatu
% moze da uzme i to stavlja u poslednji argument

% =======================================================================================
% Cetiri coveka se zovu Pera, Mika, Laza i Jova, 
% a prezivaju Peric, Mikic, Lazic i Jovic.
% Oni imaju cetiri sina koji se takodje
% zovu Pera, Mika, Laza i Jova.
% Pretpostavimo sledece:
% (a) Niko od oceva se ne zove u skladu sa svojim prezimenom.
% (b) Niko od sinova se ne zove u skladu sa svojim prezimenom.
% (c) Niko od sinova se ne zove isto kao i otac.
% (d) Peric stariji se zove isto kao Mikin sin.
% (e) Lazin sin se zove Pera.
% Napisati predikat koji odredjuje imena oceva i sinova.
% =======================================================================================
% ime oca, ime sina, prezime


% sadrzi(X, [X|_]).
% sadrzi(X, [G|R]) :- X \== G,
%					sadrzi(X, R).

solver(L) :- L = [[X, _, peric], [mika, X, _], [_, _, _], [_, _, _]],
				 sadrzi([pera, _, _], L),
				 sadrzi([laza, pera, _], L),
				 sadrzi([jova, _, _], L),
				 sadrzi([_, mika, _], L),
				 sadrzi([_, laza, _], L),
				 sadrzi([_, jova, _], L),
				 sadrzi([_, _, lazic], L),
				 sadrzi([_, _, mikic], L),
				 sadrzi([_, _, jovic], L),
				 \+(sadrzi([pera, _, peric], L)),
				 \+(sadrzi([mika, _, mikic], L)),
				 \+(sadrzi([laza, _, lazic], L)),
				 \+(sadrzi([jova, _, jovic], L)),
				 \+(sadrzi([pera, pera, _], L)),
				 \+(sadrzi([mika, mika, _], L)),
                 \+(sadrzi([laza, laza, _], L)),
				 \+(sadrzi([jova, jova, _], L)),
				 \+(sadrzi([_, pera, peric], L)),
				 \+(sadrzi([_, mika, mikic], L)),
				 \+(sadrzi([_, laza, lazic], L)),
				 \+(sadrzi([_, jova, jovic], L)).

% =======================================================================================
%  1. There are five houses, each of a different color and inhabited by
%     people of different nationalities, with different pets, drinks, and
%     cigarette brands.
%  2. The English person lives in the red house.
%  3. The Spaniard owns a dog.
%  4. Coffee is drunk in the green house.
%  5. The Ukranian drinks tea.
%  6. The green house is immediately to the right of the ivory house.
%  7. The Old-Gold smoker has a pet snail.
%  8. Kools are being smoked in the yellow house.
%  9. Milk is drunk in the middle house.
% 10. The Norwegian lives in the first house on the left.
% 11. The Chesterfield smoker lives next to the fox owner.
% 12. Kools are smoked in the house next to the house where the horse is kept. 
% 13. The Lucky-Strike smoker drinks orange juice.
% 14. The Japanese smokes Parliament.
% 15. The Norwegian lives next to the blue house.
% 16. There is one house where drink is water.
% 17. There is one house where pet is zebra.
%
% Who owns the zebra?
% Redosled kodiranja:
% color, nationality, pets, drink, ciggarette
% =======================================================================================

desno(X, Y, [X, Y|_]).
desno(X, Y, [_|R]) :- desno(X, Y, R).

pored(X, Y, [X, Y|_]).
pored(X, Y, [Y, X|_]).
pored(X, Y, [_|R]) :- pored(X, Y, R).

einsteins_riddle(L) :- L = [[_, norwegian, _, _, _],
						   [_, _, _, _, _],
						   [_, _, _, milk, _],
						   [_, _, _, _, _],
						   [_, _, _, _, _]],
					   sadrzi([green, _, _, coffee, _], L),
					   sadrzi([_, ukranian, _, tea, _], L),
					   desno([ivory, _, _, _, _], [green, _, _, _, _], L),
					   sadrzi([_, _, snail, _, olg_gold], L),
					   sadrzi([yellow, _, _, _, kools], L),
					   pored([_, _, _, _, chesterfield], [_, _, fox, _, _], L),
					   pored([_, _, _, _, kools], [_, _, horse, _, _], L),
					   sadrzi([_, _, _, orange_juice, lucky_strike], L),
					   sadrzi([_, japanese, _, _, parlament], L),
					   pored([_, norwegian, _, _, _], [blue, _, _, _, _], L),
					   sadrzi([_, _, _, water, _], L),
					   sadrzi([_, _, zebra, _, _], L),
					   sadrzi([red, english, _, _, _], L),
					   sadrzi([_, spanish, dog, _, _], L).

% =======================================================================================
% Three friends took the first, second and third places in the Universiade competitions.
% Friends - of different nationalities, call them differently and they like different
% kinds of sports. Michael prefers basketball and plays better than the American.
% Israeli David plays better than someone who plays tennis. The cricketer took first place.
% Who is an Australian? What kind of sport does Kostya do?
% nationality, name, sport
% =======================================================================================

% BAS DOBRA FORICA OVAJ PREDIKAT BOLJI

bolji(X, Y, [X|R]) :- sadrzi(Y, R).
bolji(X, Y, [_|R]) :- bolji(X, Y, R).

competition(L) :- L = [[_, _, cricket],
					   [_, _, _],
					   [_, _, _]],
				  sadrzi([american, _, _], L),
				  sadrzi([_, michael, basketball], L),
				  bolji([_, michael, basketball], [american, _, _], L),
				  sadrzi([israeli, david, _], L),
				  bolji([israeli, david, _], [_, _, tennis], L),
				  sadrzi([australia, _, _], L),
				  sadrzi([_, kostya, _], L).

% =======================================================================================
% Napisati PROLOG program koji resava sledecu zagonetku. Cetiri gospodje se sastaju
% svakog cetvrtka da igraju bridz.
% Svaki put se dogovaraju ko ce sta da donese sledeci put.
% - Gospodja Andric ce doneti cokoladnu tortu.
% - Ni gospodja Brankovic, ni Vladislava nece doneti kolacice.
% - Ruska, koja nije Davidovic, ce doneti kafu.
% - Marija ce doneti vino.
% - Ana se preziva Petrovic
% Kako se koja gospodja zove i ko sta doneti sledece nedelje?
% ime, prezime, hrana
% =======================================================================================

bridz(L) :- L = [[_, _, _],
				 [_, _, _],
				 [_, _, _],
				 [_, _, _]],
			sadrzi([_, andric, cokoladna_torta], L),
			sadrzi([ruska, _, kafa], L),
			sadrzi([marija, _, vino], L),
			sadrzi([ana, petrovic, _], L),
			\+(sadrzi([ruska, davidovic, _], L)),
			\+(sadrzi([vladislava, _, kolacici], L)),
			\+(sadrzi([_, brankovic, kolacici], L)),
			\+(sadrzi([vladislava, brankovic, _], L)).