sadrzi(X, [X|_]).
sadrzi(X, [_|R]) :- sadrzi(X, R).

desno_od(X, Y, [Y,X|_]).
desno_od(X, Y, [_|R]) :- desno_od(X, Y, R).

sused(X, Y, [X,Y|_]).
sused(X, Y, [Y,X|_]).
sused(X, Y, [_|R]) :- sused(X, Y, R).

automobili(X) :- X = [a(_,bmw,_,_,_), a(francuska,_,_,_,_), a(_,_,_,benzin,_), a(_,_,_,_,_), a(_,_,_,_,_)],
				 sadrzi(a(japan,honda,_,_,_), X),
				 sadrzi(a(_,fiat,crvena,_,_), X),
				 sadrzi(a(sad,_,_,dizel,_), X),
				 sadrzi(a(_,reno,_,metanol,_), X),
				 desno_od(a(sad,_,_,_,_), a(italija,_,_,_,_), X),
				 sadrzi(a(_,_,plava,_,'60000'), X),
				 sadrzi(a(nemacka,_,_,_,'100000'), X),
				 sused(a(_,_,_,_,'40000'), a(_,_,crni,_,_), X),
				 sused(a(_,_,_,_,'100000'), a(_,_,zuti,_,_), X),
				 sadrzi(a(_,_,_,plin,'30000'), X),
				 sadrzi(a(_,ford,_,_,'50000'), X),
				 sadrzi(a(_,_,_,etanol,_), X),
				 sadrzi(a(_,_,zelena,_,_), X), !.