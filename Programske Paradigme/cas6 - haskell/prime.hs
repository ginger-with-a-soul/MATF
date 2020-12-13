prime :: Int -> Bool
prime 1 = False
prime n = primeLoop n 2
		where primeLoop n i
				| i == n = True
				| mod n i == 0 = False
				| otherwise = primeLoop n (i + 1)

prime' :: Int -> Bool
prime' 1 = False
--prvo izracuna divisorList n pa $ kaze da primeni fju null (koja ispituje da li list prazna
-- i vraca bool vrednost) nad tom listom
prime' n = null $ divisorList n
           where divisorList n = [x | x <- [2..n - 1], mod n x == 0]

qsort [] = []
qsort (x:xs) = (qsort lesser) ++ [x] ++ (qsort grOrEq)
    where
		lesser = [e | e <- xs, e < x]
		grOrEq = [s | s <- xs, s >= x]