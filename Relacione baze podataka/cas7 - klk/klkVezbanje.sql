-- 1
-- Relaciona algebra
(((dosije where mesto_rodjenja = 'Kraljevo')[indeks] join (ispit where ocena > 5) join predmet)[id_predmeta, naziv]
minus
((ispit where oznaka_roka = 'jan' and godina_roka = 2015) join predmet)[id_predmeta, naziv])[naziv]


-- Relacioni racun
range of dosije is dx
range of ispit is ix
range of predmet is px

px.naziv
where exists ix(ix.id_predmeta = px.id_predmeta and ix.ocena > 5
				and exists dx(dx.indeks = ix.indeks and dx.mesto_rodjenja = 'Kraljevo'))
	  and not exists ix(ix.id_predmeta = px.id_predmeta and ix.godina_roka = 2015 and ix.oznaka_roka = 'jan'))
	  
	  
-- 2
-- SQL
SELECT DISTINCT ir.naziv
FROM ispitni_rok ir JOIN ispit i ON ir.oznaka_roka = i.oznaka_roka AND ir.godina_roka = i.godina_roka
WHERE i.ocena > 5
EXCEPT
SELECT DISTINCT ir.naziv
FROM (ispitni_rok ir JOIN ispit i ON ir.oznaka_roka = i.oznaka_roka AND ir.godina_roka = i.godina_roka) JOIN predmet p ON i.id_predmeta = p.id_predmeta
WHERE p.bodovi = 8

-- 3
SELECT p.naziv, ime || ' ' || prezime AS "Student"
FROM predmet p LEFT JOIN (ispit i JOIN dosije d ON i.indeks = d.indeks) ON p.id_predmeta = i.id_predmeta
WHERE i.ocena > 5 AND (MONTH(current_date) - 63 < MONTH(i.datum_ispita))
UNION
SELECT p.naziv, 'Nema studenta' AS "Student"
FROM predmet p LEFT JOIN (ispit i JOIN dosije d ON i.indeks = d.indeks) ON p.id_predmeta = i.id_predmeta
WHERE i.indeks IS null
ORDER BY naziv;

