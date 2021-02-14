-- 1
SELECT *
FROM dosije;

-- 2
SELECT indeks
FROM ispit;

-- 3
SELECT DISTINCT indeks
FROM ispit;

-- 4
SELECT DISTINCT oznaka_roka, ocena
FROM ispit;

--5
SELECT indeks, prezime
FROM dosije
WHERE ime = 'Nikola' or mesto_rodjenja = 'Beograd';

-- 6
SELECT sifra
FROM predmet
WHERE bodovi >= 6;

-- 7
SELECT indeks, ocena, (bodovi - 1) / 10 + 1
FROM ispit
WHERE ocena >= 6;

||

SELECT indeks, ocena, 'Predlozena ocena je: ' as predlog_ocene, (bodovi - 1) / 10 + 1 as "Izracunato"
FROM ispit
WHERE ocena >= 6;

-- 8
SELECT indeks, datum_rodjenja
FROM dosije
WHERE indeks > 20140000
ORDER BY 2 desc;

-- 9
SELECT *
FROM ispit
WHERE ocena = 8
ORDER BY datum_ispita desc, indeks;

-- 10
SELECT naziv
FROM predmet
WHERE bodovi between 4 and 6;

-- 11
SELECT naziv
FROM predmet
WHERE NOT bodovi between 4 and 6;

-- 12
SELECT id_predmeta
FROM ispit
WHERE MOD(ocena, 2) = 1;

-- 13
SELECT naziv
FROM predmet
WHERE naziv LIKE '%a%';

-- 14
SELECT naziv
FROM predmet
WHERE naziv LIKE '%a';

-- 15
SELECT ime, prezime
FROM dosije
WHERE ime LIKE 'M___%';

-- 16
