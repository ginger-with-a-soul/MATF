module Point2D where

type Point = (Float, Float)

point :: Float -> Float -> Point
point x y = (x, y)

o :: Point
o = point 0.0 0.0

type Path = [Point]

path :: [Point] -> Path
path = id

pathLength :: Path -> Int
pathLength p = length p

translate :: Point -> Float -> Float -> Point
translate t x1 y1 = (fst t + x1, snd t + y1)

distance :: Point -> Point -> Float
distance t1 t2 = sqrt $ (fst t1 - fst t2)^2 + (snd t1 - snd t2)^2

inRadius :: Float -> [Point] -> [Point]
inRadius r lst = [t | t <- lst, distance t o < r]

-- map primenjuje fju nad svim elementima liste i vraca novu, izmenjenu listu
-- koja ne mora da bude istog tipa (u c++ to je transform)
-- filter primenjuje fju nad listom i vraca izmenjenu listu prema tome kakva fja je primenjena
-- ali nova lista ostaje istog tipa
-- all primenjuje predikatsku fju (ona koja se evaluira na bool) na listu i vraca true ako svi
-- elementi fje imaju evaluaciju true u predikatskoj fji. Analogno za any
-- foldl primenjuje binarni operator tako sto uzme akumulator i uraditi operator u odnosu na
-- elemente liste
-- foldr uzme element po element i primeni na akumulator
-- foldl1 i foldr1 kao akumulator uzimaju prvi element

translatePath :: Path -> Float -> Float -> Path
translatePath p x y = map (\t -> translate t x y) p

connect :: Point -> Path -> Path
connect t p = reverse $ t : (reverse p)

connectPaths :: Path -> Path -> Path
connectPaths = (++)

centroid :: [Point] -> Point
centroid pts = point avrgX avrgY
	where
		avrgX = avrg $ map fst pts
		avrgY = avrg $ map snd pts
		avrg pts = (sum pts) / (fromIntegral $ length pts)

quadPoint :: Point -> Int
quadPoint (x, y)
	| x > 0 && y > 0 = 1
	| x < 0 && y > 0 = 2
	| x < 0 && y < 0 = 3
	| x > 0 && y < 0 = 4

quadPath :: Path -> Int
quadPath lst = if sameQuad then head quads else 0
	where
		quads = map quadPoint lst
		sameQuad = all (==head quads) (tail quads)

pointsInQuad :: Int -> [Point] -> [Point]
pointsInQuad k lst = filter (\t -> quadPoint t == k) lst

maxis :: [Point] -> (Float, Float)
maxis lts = (maximum $ map fst lts, maximum $ map snd lts)
	where
		maximum lts = foldl1 max lts
