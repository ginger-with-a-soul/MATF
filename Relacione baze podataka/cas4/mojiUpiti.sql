-- 1
SELECT ime, prezime, id_predmeta
FROM dosije d JOIN ispit i ON d.indeks = i.indeks;

-- 2
SELECT DISTINCT d.indeks, ime, prezime, naziv
FROM (dosije d join ispit i ON d.indeks = i.indeks) JOIN predmet p ON i.id_predmeta = p.id_predmeta
WHERE i.ocena > 5;

-- 3
SELECT d1.indeks, d2.indeks
FROM dosije d1 JOIN dosije d2 ON d1.mesto_rodjenja = d2.mesto_rodjenja
	 AND d1.indeks < d2.indeks;

-- 4
SELECT indeks, naziv
FROM ispit i JOIN predmet p on i.id_predmeta = p.id_predmeta
WHERE ocena > 7
ORDER BY indeks;

-- 5
SELECT ir1.naziv, ir2.naziv
FROM ispit i1 JOIN ispitni_rok ir1 ON i1.oznaka_roka = ir1.oznaka_roka AND i1.godina_roka = ir1.godina_roka
	 JOIN ispit i2 ON i1.indeks = i2.indeks AND i1.id_predmeta = i2.id_predmeta and (i1.oznaka_roka <> i2.oznaka_roka OR i1.godina_roka <> i2.godina_roka)
	 JOIN ispitni_rok ir2 ON ir2.godina_roka = i2.godina_roka AND ir2.oznaka_roka = i2.oznaka_roka;

-- 6
SELECT naziv, godina_roka, oznaka_roka
FROM predmet p LEFT JOIN ispit i ON p.id_predmeta = i.id_predmeta
ORDER BY naziv;

-- 7
SELECT naziv, ocena
FROM ispitni_rok ir LEFT JOIN ispit i ON ir.godina_roka = i.godina_roka AND ir.oznaka_roka = i.oznaka_roka
ORDER BY naziv;

-- 8
SELECT i.indeks, p.id_predmeta, i.ocena, i.godina_roka, i.oznaka_roka
FROM predmet p LEFT JOIN ispit i ON p.id_predmeta = i.id_predmeta;