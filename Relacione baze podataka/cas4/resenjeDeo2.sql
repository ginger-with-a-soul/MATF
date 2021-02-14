 
-- 19
SELECT ime, prezime
FROM dosije
where mesto_rodjenja is NULL;

-- 20
SELECT ime, prezime
FROM dosije
WHERE mesto_rodjenja IS NOT NULL;

-- 21
SELECT ime, prezime
FROM dosije
WHERE mesto_rodjenja <> 'Kraljevo';

-- 22
VALUES 1, 2, 3;

-- 23
VALUES (1, 2, 3), (4, 5, 6);

-- 24
VALUES user;

-- 25
VALUES current time;

-- 26
VALUES current date;

-- 27
VALUES current timestamp;