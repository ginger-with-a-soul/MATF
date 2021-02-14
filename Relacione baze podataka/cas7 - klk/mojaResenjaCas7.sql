-- RELACIONA ALGEBRA I RELACIONI RACUN

-- 1
DEFINE ALIAS p1 FOR predmet
DEFINE ALIAS p2 FOR predmet

(p1[id_predmeta, naziv]
MINUS
(p1 TIMES p2 WHERE p1.bodovi < p2.bodovi)[p1.id_predmeta, p1.naziv])[naziv]


range of px1 is predmet
range of px2 is predmet

px1.naziv
where not exists px2(px2.bodovi > px1.bodovi)

-- 2
((predmet where naziv = 'Programiranje 1')[id_predmeta] join ispit)[oznaka_roka, godina_roka]
minus
((predmet where naziv = 'Programiranje 1')[id_predmeta] join ispit)[oznaka_roka, godina_roka, indeks]
divideby
dosije[indeks]


range of px is predmet
range of irx is ispitni_rok
range of dx is dosije
range of ix is ispit

irx.godina_roka, irx.oznaka_roka
where exists ix(ix.oznaka_roka = irx.oznaka_roka and ix.godina_roka = irx.godina_roka
	and exists px(px.id_predmeta = ix.id_predmeta and px.naziv_predmeta = 'Programiranje 1'))
	and exists dx(not exists ix(dx.indeks = ix.indeks and ix.oznaka_roka = irx.oznaka_roka
								and ix.godina_roka = irx.godina_roka
								and exists px(px.id_predmeta = ix.id_predmeta and px.naziv_predmeta = 'Programiranje 1')))
								

-- 3
range of ix is ispit
range of iy is ispit

ix.oznaka_roka, ix.godina_roka, ix.id_predmeta
where not exists iy(iy.id_predmeta = ix.predmeta and (ix.oznaka_roka <> iy.oznaka or ix.godina_roka <> iy.godina_roka))


-- 4
(((ispit where ocena = 5)[godina_roka, oznaka_roka, indeks]
divideby ispitni_rok[godina_roka, oznaka_roka]) join dosije)[ime, prezime]


range of ix is ispit
range of dx is dosije
range of irx is ispitni_rok

dx.ime, dx.prezime
where not exists irx(not exists ix(ix.indeks = dx.indeks and ix.godina_roka = irx.godina_roka
								   and ix.oznaka_roka = irx.oznaka_roka and ix.ocena = 5))
								   
								  
-- 6
(((ispit where indeks = 20140021 and ocena > 5)[oznaka_roka, godina_roka, id_predmeta]
divideby
(ispit where indeks = 20140021)[id_predmeta]) join ispitni_rok)[naziv]


range of ix is ispit
range of iy is ispit
range of irx is ispitni_rok

irx.naziv
where 


-- 7
((((dosije where mesto_rodjenja = 'Kraljevo')[indeks] join ispit)[oznaka_roka, godina_roka]
minus
(dosije where mesto_rodjenja = 'Kraljevo')[indeks] join (ispit where ocena > 5))[oznaka_roka, godina_roka, indeks])
join ispitni_rok)[naziv]


range of irx is ispitni_rok
range of dx is dosije
range of ix is ispit

irx.naziv
where exists ix(ix.oznaka_roka = irx.oznaka_roka and ix.godina_roka = irx.godina_roka
					and exists dx(dx.indeks = ix.indeks and dx.mesto_rodjenja = 'Kraljevo'))
  not exists ix(ix.oznaka_roka = irx.oznaka_roka and ix.godina_roka = irx.godina_roka
  				and exists dx(dx.indeks = ix.indeks and dx.mesto_rodjenja = 'Kraljevo' and ix.ocena > 5))
  				
  			
-- 8
(ispit where indeks = 20140021 and ocena > 5)[id_predmeta]
minus
(ispit where indeks <> 20140021 and ocena > 5)[id_predmeta]

range of ix is ispit
range of px is predmet

px.id_predmeta
where exists ix(ix.id_predmeta = px.id_predmeta and ix.indeks = 20140021 and ocena > 5) and
  not exists ix(ix.id_predmeta = px.id_predmeta and ix.indeks <> 20140021 and ocena > 5)
  

-- 9
((ispit[id_predmeta, indeks]
divideby
(dosije where mesto_rodjenja = 'Beograd')[indeks])
join
predmet)[naziv]


range of dx is dosije
range of ix is ispit
range of px is predmet

px.naziv
where not exists dx(dx.mesto_rodjenja = 'Beograd' and
	  not exists ix(ix.indeks = dx.indeks and ix.id_predmeta = px.id_predmeta))
	  
	
-- 10
ispitni_rok[oznaka_roka, godina_roka]
minus
(ispit[oznaka_roka, godina_roka, id_predmeta]
divideby
predmet[id_predmeta]) 


range of ix is ispit
range of px is predmet
range of irx is ispitni_rok

irx.godina_roka, irx.oznaka_roka
where exists px(not exists ix(px.id_predmeta = ix.id_predmeta and ix.godina_roka = irx.godina_roka
															  and ix.oznaka_roka = irx.oznaka_roka))
															  
															  
-- 11


-- 12


-- 13



-- SQL

-- 1
SELECT d.indeks
FROM dosije d
WHERE d.mesto_rodjenja IN (SELECT mesto_rodjenja
						   FROM dosije
						   WHERE year(datum_upisa) < 2014);
						   
-- 2
SELECT ir.naziv
FROM ispitni_rok ir
WHERE NOT EXISTS (SELECT *
				  FROM ispit
				  WHERE ocena = 5 AND ir.godina_roka = godina_roka AND ir.oznaka_roka = oznaka_roka AND id_predmeta IN (SELECT id_predmeta
				  								      																	FROM predmet
				  								      																	WHERE bodovi = 8))
	  OR EXISTS (SELECT *
	  			 FROM ispit
	  			 WHERE ir.godina_roka = godina_roka and ir.oznaka_roka <> oznaka_roka AND ocena = 5 AND id_predmeta IN (SELECT id_predmeta
	  			 																										FROM predmet
	  			 																										WHERE bodovi = 8))
ORDER BY ir.naziv DESC;


-- 3
SELECT d.indeks, d.ime, d.prezime, CASE d.mesto_rodjenja
										WHEN d.mesto_rodjenja THEN d.mesto_rodjenja
										ELSE 'Nepoznato'
									END AS "mesto_rodjenja"
FROM dosije d
WHERE d.indeks < any (SELECT indeks
					  FROM dosije
					  WHERE ime = 'Marijana' and prezime = 'Savkovic');


-- 4
SELECT DISTINCT p.*
FROM predmet p
WHERE EXISTS (SELECT *
			  FROM ispit i1 JOIN dosije d1 ON i1.indeks = d1.indeks
			  WHERE i1.id_predmeta = p.id_predmeta AND i1.ocena > 5 and EXISTS (SELECT *
			  																	FROM ispit i2 JOIN dosije d2 ON i2.indeks = d2.indeks
			  																	WHERE i2.id_predmeta = p.id_predmeta AND i2.ocena > 5 AND i1.indeks <> i2.indeks AND d1.mesto_rodjenja = d2.mesto_rodjenja));
			  																	
			  																
-- 5
SELECT SUBSTR(char(indeks), 5, 4) || '/' || SUBSTR(char(indeks), 1, 4) as "Indeks"
FROM ispit
WHERE ocena = 10 AND NOT EXISTS (SELECT *
								 FROM ispit i2
								 WHERE i2.indeks <> indeks AND i2.id_predmeta = id_predmeta AND i2.ocena = 10);
			  														   

-- 6
SELECT ime || ' ' || prezime, MONTH(current_date - datum_ispita) + 12 * YEAR(current_date - datum_ispita) AS "broj_meseci"
FROM ispit i JOIN dosije d ON i.indeks = d.indeks
WHERE ocena IN (8, 9) AND DAY(datum_ispita) = 25;


-- 8
SELECT indeks, YEAR(datum_rodjenja) AS "godina", naziv
FROM dosije d FULL JOIN ispitni_rok ir ON YEAR(datum_rodjenja) = ir.godina_roka;
			  														   