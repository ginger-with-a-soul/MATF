-- 1
range of px is predmet

px.naziv, px.bodovi

-- 2
range of dx is dosije

dx.indeks, dx.ime, dx.prezime, dx.datum_rodjenja, dx.mesto_rodjenja, dx.datum_upisa
where dx.mesto_rodjenja = 'Beograd'

-- 3
range of dx is dosije
range of ix is ispit

dx.indeks, dx.ime, dx.prezime, dx.datum_rodjenja, dx.mesto_rodjenja, dx.datum_upisa, 
ix.id_predmeta, ix.godina_roka, ix.oznaka_roka, ix.ocena, ix.datum_ispita, ix.bodovi
where dx.indeks = ix.indeks

-- 4
range of dx is dosije
range of ix is ispit 

dx.ime, dx.prezime
where exists ix(ix.indeks = dx.indeks and ix.id_predmeta = 2001)

-- 5
range of dx is dosije
range of ix is ispit
range of px is predmet

dx.indeks
where forall px(exists ix(ix.id_predmeta = px.id_predmeta and dx.indeks = ix.indeks))

-- 6
range of dx is dosije
range of px is predmet
range of ix is ispit

dx.ime, dx.prezime
where exists ix(ix.indeks = dx.indeks and ix.ocena > 5 and exists px(px.id_predmeta = ix.id_predmeta and px.bodovi = 6))

-- 7
range of dx is dosije
range of ix is ispit

dx.indeks
where forall px(if exists ix(ix.indeks = 20130023 and px.id_predmeta = ix.id_predmeta)
				then exists ix(ix.indeks = dx.indeks and ix.ocena > 5 and ix.id_predmeta = px.id_predmeta))

-- 8
range of px is predmet
range of dx is dosije
range of ix is ispit

px.naziv
where forall dx(if dx.indeks > 20130000 and dx.indeks < 20140000
				then exists ix(ix.indeks = dx.indeks and ix.ocena > 5 and ix.id_predmeta = px.id_predmeta))

-- 9
range of dx is dosije
range of ix is ispit

dx.ime, dx.prezime
where not exists ix(ix.indeks = dx.indeks and and ix.id_predmeta = 1021)

-- 10
range of ix is ispit
range of px is predmet

px.sifra
where px.bodovi = 6 or exists ix(ix.godina_roka = 2015 and ix.oznaka_roka = 'jan' and ix.ocena > 5 and px.id_predmeta = ix.id_predmeta)

-- 11
range of ix is ispit
range of px is predmet
range of irx is ispitni_rok

irx.naziv
where exists ix(ix.godina_roka = irx.godina_roka and ix.oznaka_roka = irx.oznaka_roka
				and exists px(ix.id_predmeta = ix.id_predmeta and px.naziv = 'Programiranje 1'))

-- 12
range of px is predmet
range of py is predmet

px.id_predmeta
where exists py(py.id_predmeta = 2004 and px.bodovi < py.bodovi)

-- 13
range of dx is dosije
range of ix is ispit
range of iy is ispit

dx.ime, dx.prezime
where exists ix(ix.indeks = dx.indeks and ix.ocena = 6 and exists iy(iy.indeks = dx.indeks and iy.ocena = 10))

-- 14
range of px is predmet
range of ix is ispit
range of dx is dosije

px.naziv
where exists ix(ix.ocena > 5 and ix.id_predmeta = px.id_predmeta
				and exists dx(dx.indeks = ix.indeks and dx.ime = 'Nikola' and dx.prezime = 'Vukovic'))

-- 15
range of dx is dosije
range of dy is dosije

dx.indeks, dy.indeks
where dx.mesto_rodjenja = dy.mesto_rodjenja and dx.indeks < dy.indeks

-- 16
range of dx is dosije
range of px is predmet
range of ix is ispit

px.naziv
where exists ix(ix.ocena > 5 and px.id_predmeta = ix.id_predmeta
				and exists dx(dx.indeks = ix.indeks and dx.mesto_rodjenja = 'Beograd')
				and exists irx(irx.godina_roka = ix.godina_roka and irx.oznaka_roka = ix.oznaka_roka and irx.naziv = 'April 2015'))
		
-- 17
range of dx is dosije
range of ix is ispit

dx.ime, dx.prezime
where exists ()

-- 18
range of dx is dosije
range of ix is ispit
range of irx is ispitni_rok
range of px is predmet

irx.oznaka_roka, irx.godina_roka
where forall dx(if dx.mesto_rodjenja = 'Kraljevo'
				then not exists ix(ix.indeks = dx.indeks and ix.ocena > 5 and irx.godina_roka = ix.godina_roka and irx.oznaka_roka = ix.oznaka_roka
				and exists px(px.id_predmeta = ix.id_predmeta and px.bodovi = 4)))