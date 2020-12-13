% Jelena   Bogdanovic    cizme braon
% Milica   Cugurovic     sandale pink
% Kaca     Andonov       patike crne
% Anja     Ranisavljevic cipele zelene 

clan(X, [X|_]).
clan(X, [_|R]):- clan(X, R).

drugarice(X):-
    X = [d(jelena,_,_,_), d(milica,_,_,_), d(kaca,_,_,_), d(anja,_,_,_)],
    %clan(d(jelena,bogdanovic,cizme,braon), X),
    %clan(d(milica,cugurovic,sandale,pink), X),
    %clan(d(kaca,andonov,patike,crna), X),
    %clan(d(anja,ranisavljevic,cipele,zelena), X),

    clan(d(anja,_,cipele,_), X),

    % 1. Kaca Andonov nije kupila cizme
    clan(d(kaca,andonov,_,_), X),
    clan(d(_,_,cizme,_), X),

    % 2. Devojka koja se preziva ranisavljevic kupila je zelenu obucu
    clan(d(_,ranisavljevic,_,zelena), X),

    % 3. Cipele nisu pink boje, to bi bio veliki modni promasaj
    clan(d(_,_,_,pink), X),
    clan(d(_,_,cipele,_), X),

    % 4. Cizme su braon boje a njih nije kupila devojka koja se preziva cugurovic
    clan(d(_,_,cizme,braon), X),
    clan(d(_,cugurovic,_,_), X),

    % 5. Anjino prezime nije bogdanovic. Jelena nije kupila patike
    clan(d(_,bogdanovic,_,_), X),
    clan(d(_,_,patike,_), X),

    % 6. Milicino prezime nije ranisavljevic, i dodatno ona je kupila sandale koje nisu crne
    clan(d(milica,_,sandale,B), X),
    clan(d(_,_,_,crna), X),
    B\=crna,

    not(clan(d(kaca,andonov,cizme,_), X)),
    not(clan(d(_,_,cipele,pink), X)),
    not(clan(d(_,cugurovic,cizme,_), X)),
    not(clan(d(anja,bogdanovic,_,_), X)),
    not(clan(d(jelena,_,patike,_), X)),
    not(clan(d(milica,ranisavljevic,_,_), X)).				