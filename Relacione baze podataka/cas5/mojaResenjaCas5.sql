-- 1
SELECT d.ime, d.prezime
FROM dosije d JOIN ispit i ON d.indeks = i.indeks
WHERE i.id_predmeta = 2001 AND i.ocena > 5;


SELECT d.ime, d.prezime
FROM dosije d
WHERE d.indeks IN (SELECT indeks
				   FROM ispit
				   WHERE id_predmeta = 2001 AND ocena > 5);
				  
				  
SELECT d.ime, d.prezime
FROM dosije d
WHERE 2001 IN (SELECT id_predmeta
			   FROM ispit i
			   WHERE i.indeks = d.indeks AND i.ocena > 5);
			   
	
SELECT d.ime, d.prezime
FROM dosije d
WHERE EXISTS (SELECT *
			  FROM ispit i
			  WHERE i.indeks = d.indeks AND i.id_predmeta = 2001 AND i.ocena > 5);
			  
		
-- 2
SELECT d.ime, d.prezime
FROM dosije d
WHERE NOT EXISTS (SELECT *
				  FROM ispit i
				  WHERE i.indeks = d.indeks AND i.id_predmeta = 3001);
				  

-- 3
SELECT d.indeks, d.ime, d.prezime
FROM dosije d JOIN ispit i ON d.indeks = i.indeks JOIN predmet p ON p.id_predmeta = i.id_predmeta
WHERE p.bodovi = 5;

SELECT d.indeks, d.ime, d.prezime
FROM dosije d
WHERE d.indeks IN (SELECT i.indeks
				   FROM ispit i
				   WHERE i.id_predmeta IN (SELECT p.id_predmeta
				  						   FROM predmet p
				  						   WHERE p.bodovi = 5));
				  						  
				  						
-- 4
SELECT d.indeks, d.ime, d.prezime
FROM dosije d
WHERE NOT EXISTS (SELECT *
				  FROM predmet p
				  WHERE NOT EXISTS (SELECT *
				  					FROM ispit i
				  					WHERE i.id_predmeta = p.id_predmeta AND i.indeks = d.indeks AND i.ocena > 5));
				  					
				  					
-- 5
SELECT d.indeks
FROM dosije d
WHERE NOT EXISTS (SELECT *
				  FROM predmet p
				  WHERE EXISTS (SELECT *
				  				FROM ispit ix
				  				WHERE ix.indeks = 20140026 AND ix.id_predmeta = p.id_predmeta AND ix.ocena > 5)
				  AND NOT EXISTS (SELECT *
				  				  FROM ispit iy
				  				  WHERE iy.indeks = d.indeks AND iy.id_predmeta = p.id_predmeta AND iy.ocena > 5));
				  				  
				  		
-- CASE EXPRESSIONS

-- 1
SELECT i.indeks, i.id_predmeta, i.ocena, CASE i.ocena
											WHEN 5 THEN 'nepolozen'
											WHEN 6 THEN 'sest'
											WHEN 7 THEN 'sedam'
											WHEN 8 THEN 'osam'
											WHEN 9 THEN 'devet'
											WHEN 10 THEN 'deset'
											ELSE null
										 END AS "Opisna ocena"
FROM ispit i;


-- 2
SELECT p.*, CASE
		   	  WHEN bodovi < 6 THEN 'lak'
		   	  WHEN bodovi BETWEEN 6 AND 7 THEN 'srednje tezak'
		   	  WHEN bodovi > 6 THEN 'tezak'
		   	  ELSE null
		   END AS "Tezina predmeta"
FROM predmet p;


-- 3
SELECT d.indeks, d.ime, d.prezime, CASE
									  WHEN NOT EXISTS (SELECT *
									  				   FROM ispit
									  				   WHERE d.indeks = indeks) THEN 'brucos'
									  WHEN NOT EXISTS (SELECT *
									  				   FROM ispit
									  				   WHERE d.indeks = indeks AND ocena > 5) THEN 'nijedan polozen'
									  WHEN EXISTS (SELECT *
									  			   FROM ispit
									  			   WHERE d.indeks = indeks AND ocena > 5) THEN 'student'
									  ELSE null
								   END AS "Status studenta"	
FROM dosije d;

-- SKUPOVNE OPERACIJE

-- 1
SELECT i.id_predmeta
FROM ispit i
WHERE i.indeks = '20130024'
UNION 
SELECT p.id_predmeta
FROM predmet p
WHERE p.bodovi > 6;

-- 2
SELECT i.id_predmeta
FROM ispit i
WHERE i.oznaka_roka = 'jan' AND i.godina_roka = 2015
INTERSECT ALL
SELECT i.id_predmeta
FROM ispit i
WHERE i.oznaka_roka = 'feb' AND i.godina_roka = 2015;


SELECT DISTINCT i.id_predmeta
FROM ispit i
WHERE i.oznaka_roka = 'jan' AND i.godina_roka = 2015
	  AND EXISTS (SELECT i2.id_predmeta
	  			  FROM ispit i2
	  			  WHERE i2.oznaka_roka = 'feb' AND i2.godina_roka = 2015 AND i2.id_predmeta = i.id_predmeta);
	  	
SELECT DISTINCT i.id_predmeta
FROM ispit i
WHERE i.oznaka_roka = 'jan' AND i.godina_roka = 2015 AND i.id_predmeta IN (SELECT id_predmeta
																		   FROM ispit
																		   WHERE godina_roka = 2015 AND oznaka_roka = 'feb');
 	  
											
-- 3
SELECT i.id_predmeta
FROM ispit i
WHERE i.indeks = 20140021 AND ocena > 5
EXCEPT
SELECT i.id_predmeta
FROM ispit i
WHERE i.indeks = 20140025 AND ocena > 5
ORDER BY id_predmeta DESC;

SELECT i1.id_predmeta
FROM ispit i1
WHERE i1.indeks = 20140021 AND i1.ocena > 5 AND NOT EXISTS (SELECT *
														FROM ispit i2
														WHERE i1.id_predmeta = i2.id_predmeta AND i2.ocena > 5 AND i2.indeks = 20140025)
ORDER BY id_predmeta DESC;

SELECT i1.id_predmeta
FROM ispit i1
WHERE i1.ocena > 5 AND i1.indeks = 20140021 AND i1.id_predmeta NOT IN (SELECT id_predmeta
																	   FROM ispit i2
																	   WHERE i2.ocena > 5 AND i2.indeks = 20140025)
ORDER BY id_predmeta DESC;
