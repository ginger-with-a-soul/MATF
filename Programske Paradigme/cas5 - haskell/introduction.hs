-- sqrt of int

squareRoot :: Int -> Double
squareRoot n = sqrt (fromIntegral n)

-- sum of first n

sum :: Int -> Int
sum n = 
	if n == 0 then 0
	else n + sum(n - 1)

-- pari max

pairMax :: (Double, Double) -> Double

pairMax (l, r) = max l r