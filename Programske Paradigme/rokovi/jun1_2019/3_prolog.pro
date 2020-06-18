clan(X, [X|_]).
clan(X, [_|R]) :- clan(X, R).

drugarice(X) :- X = [d(milica,_,_,_), d(jelena,_,_,_), d(anja,_,_,_), d(kaca,_,_,_)],
				clan(d(kaca,andonov,_,_), X),
				clan(d(_,_,cizme,_), X),

				clan(d(_,ranisavljevic,_,zelena), X),
				clan(d(milica,_,sandale,_), X),
				clan(d(_,_,_,crna), X),

				clan(d(_,_,cipele,_), X),
				clan(d(_,_,_,pink), X),
				clan(d(anja,_,cipele,_), X),

				%cizme su braon boje a njih nije kupila devojka koja se preziva Cugurovic
				clan(d(_,_,cizme,braon), X),
				clan(d(_,cugurovic,_,_), X),
				
				clan(d(_,bogdanovic,_,_), X),
				clan(d(_,_,patike,_), X),

				%Milicino prezime nije Ranisavljevic, i dodatno ona je kupila sandale koje nisu crne	
				
				not(clan(d(anja,bogdanovic,_,_), X)),
				not(clan(d(kaca,andonov,cizme,_), X)),
				not(clan(d(_,_,cipele,pink), X)),
				not(clan(d(milica,_,sandale,crna), X)),
				not(clan(d(milica,ranisavljevic,_,_), X)),
				not(clan(d(_,cugurovic,cizme,braon), X)),
				not(clan(d(jelena,_,patike,_), X)).