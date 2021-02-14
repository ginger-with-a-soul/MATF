-- 1 a)
SELECT p.bodovi, DECIMAL(p.bodovi*1.35, 3, 1) AS "Uvecani Bodovi"
FROM predmet p;

-- b)
SELECT CEIL(p.bodovi * 1.35) AS "Uvecani Bodovi"
FROM predmet p
WHERE p.bodovi * 1.35 > 8;


-- 2
SELECT d.indeks, d.ime || ' ' || d.prezime AS "Ime i prezime", CASE d.mesto_rodjenja
																   WHEN 'Beograd' THEN 'Bg'
																   ELSE 'Nije Bg'
															   END AS "Mesto rodjenja", LENGTH(d.ime) + LENGTH(d.prezime) AS "Duzina", SUBSTR(d.ime, 1, 1) || SUBSTR(d.prezime, 1, 1) AS "Inicijali"
FROM dosije d;


-- 3
VALUES (current time, current date, current user);


-- 4
VALUES CHAR(current date, ISO), CHAR(current date, EUR), CHAR(current date, USA), CHAR(current date, LOCAL), CHAR(current date, JIS);


-- 5
VALUES DAYNAME('18.11.2010');


-- 6
VALUES (DAYOFYEAR(current date), WEEK(current date), DAYOFWEEK(current date), DAYNAME(current date), MONTHNAME(current date));


-- 7
VALUES (HOUR(current time), MINUTE(current time), SECOND(current time));


-- 8
VALUES CHAR(current date + 12 years + 5 months + 25 days, EUR);


-- 9
SELECT *
FROM ispit i
WHERE i.datum_ispita > DATE('1.4.2011');


-- 10
SELECT *
FROM ispit i
WHERE YEAR(current date) - YEAR(i.datum_ispita) < 5;	    
