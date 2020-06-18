sadrzi(X, [X|_]).
sadrzi(X, [_|R]) :- sadrzi(X, R).

prijatelji(X) :- X = [f(_,_,_,_), f(_,_,_,_), f(_,_,_,_), f(_,_,_,_)],
				 sadrzi(f(marko,_,_,_), X),
				 sadrzi(f(_,_,'stoni fudbal',_), X),
				 sadrzi(f(marko,_,_,nacosi), X),
				 sadrzi(f(_,markovic,_,kokice), X),
				 sadrzi(f(milica,_,_,_), X),
				 sadrzi(f(_,milic,_,_), X),
				 sadrzi(f(_,_,bilijar,pica), X),
				 sadrzi(f(ivana,stefanovic,_,_), X),
				 sadrzi(f(nemanja,_,_,_), X),
				 sadrzi(f(_,radosavljevic,_,_), X),
				 sadrzi(f(nemanja,_,'mini golf',_), X),
				 sadrzi(f(_,_,kuglanje,_), X),
				 sadrzi(f(_,_,_,sladoled), X),
				 not(sadrzi(f(marko,_,'stoni fudbal',_), X)),
				 not(sadrzi(f(milica,milic,_,_), X)),
				 not(sadrzi(f(milica,_,bilijar,_), X)),
				 not(sadrzi(f(nemanja,radosavljevic,_,_), X)),
				 not(sadrzi(f(_,radosavljevic,kuglanje,_), X)), !.