-- 1
predmet[naziv, bodovi]

-- 2
dosije where mesto_rodjenja = 'Beograd'

-- 3
dosije times ispit
where dosije.indeks = ispit.indeks 

ili 

dosije join ispit

-- 4
define alias d1 for dosije
define alias d2 for dosije

((d1 times d2)
where d1.mesto_rodjenja = d2.mesto_rodjenja and d1.indeks < d2.indeks)[d1.indeks, d2.indeks]

-- 5
(dosije join (ispit where id_predmeta = 2001))[ime, prezime]

-- 6
(((ispit where ocena > 5)[indeks, id_predmeta] join ((predmet where bodovi = 6)[id_predmeta]))[indeks] join (dosije[indeks, ime, prezime]))[ime, prezime]

-- 7
ispit[indeks, id_predmeta] divideby predmet[id_predmeta]

-- 8
(ispit where ocena > 5)[indeks, id_predmeta] divideby (ispit where indeks = 20130023)[id_predmeta]

-- 9
((predmet[id_predmeta, naziv] join (ispit where ocena > 5)[id_predmeta, indeks]) divideby (dosije where indeks > 201300000 and indeks < 201400000)[indeks])[naziv]

-- 10
((dosije[indeks] minus (ispit where id_predmeta = 1021)[indeks]) join dosije[indeks, ime, prezime])[ime, prezime]

-- 11
(((predmet where bodovi = 6)[id_predmeta] union (ispit where ocena > 5 and oznaka_roka = 'jan' and godina_roka = 2015)[id_predmeta]) join predmet[id_predmeta, sifra])[sifra]

-- 12
(((ispit where ocena = 6)[indeks] intesect (ispit where ocena = 10)[indeks]) join dosije[indeks, ime, prezime])[ime, prezime]

-- 13
(((predmet where naziv = 'Programiranje 1')[id_predmeta] join ispit[id_predmeta, godina_roka, oznaka_roka])[godina_roka, oznaka_roka] join ispitni_rok)[naziv]

-- 14
(predmet where bodovi < (predmet where id_predmeta = 2004)[bodovi])[id_predmeta]

-- 15

(((dosije where ime = 'Nikola' and prezime = 'Vukovic')[indeks] join (ispiti where ocena > 5)[indeks, id_predmeta])[id_predmeta] join predmet[id_predmeta, naziv])[naziv]

-- 16
(((dosije where mesto_rodjenja = 'Beograd')[indeks] join (ispit where oznaka_roka = 'apr' and godina_roka = 2015 and ocena > 5)[indeks, id_predmeta])[id_predmeta] join predmet[id_predmeta, naziv])[naziv]

-- 17
(((ispit where ocena > 5 and indeks = 20140025)[id_predmeta] join (ispit where ocena > 5)[id_predmeta, indeks])[indeks] join dosije[indeks, ime, prezime])[ime, prezime]

-- 18
(((ispit where ocena > 5)[indeks, id_predmeta, godina_roka, oznaka_roka] join (predmet where bodovi = 4)[id_predmeta])[indeks] minus (dosije where mesto_rodjenja = 'Kraljevo')[indeks])[oznaka_roka, godina_roka]
