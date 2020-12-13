-- data konstruise novi algebarski tip podataka. Posle data navodimo ima naseg tipa a zatim
-- razlicite kontruktore koji su razdvojeni |.
-- deriving govori da nas tip/klasa implementira default verziju odredjenih fja
-- show slican toString -> vraca string onoga sto mu prosledimo

module Student where
import Data.List as List (elemIndex, sortBy)

data StepenStudija = OsnovneStudije
				   | MasterStudije
				   | DoktorskeStudije
				   deriving (Show, Eq)

data KratkiStepenStudija = Kratko StepenStudija

instance Show KratkiStepenStudija where
	show (Kratko OsnovneStudije) = "BSc"
	show (Kratko MasterStudije) = "MSc"
	show (Kratko DoktorskeStudije) = "PhD"

data Student = MkStudent {
						  indeks :: String,
						  ime :: String,
						  prezime :: String,
						  stepen :: StepenStudija
			   			 }

formatirajStudent :: Student -> String
formatirajStudent s = 
	let
		id = indeks s
		ip = ime s ++ " " ++ prezime s
		ks = show $ Kratko $ stepen s
	in id ++ ": " ++ ip ++ " " ++ ks

instance Show Student where
	show s = formatirajStudent s

instance Eq Student where
	s1 == s2 = (indeks s1) == (indeks s2)

-- Maybe ostavlja mogucnost da odredjeni podatak postoji ili ne postoji. Ako ne postoji onda
-- je Nothing a ako postoji onda je Just /podatak/
-- Either je ili ili i sastoji se od Left i Right
type Rezultat = (Student, Maybe Int)

rezultati :: [Student] -> [Rezultat]
rezultati studenti = map (\s -> (s, Nothing)) studenti

--poeni :: Student -> [Rezultat] -> Either String (Maybe Int)
--poeni s rezultati = 
--	case mi of Nothing -> Left $ "Student sa indeksom " ++ (indeks s) ++ " nije na listi!"
--               Just i  -> Right $ snd $ rezultati !! i
--    where mi = List.elemIndex s $ map fst rezultati

-- foldl obrce redosled liste dok foldr cuva redosled
-- foldr (-) 0 [1,2,3,4] --> (1 - (2 - (3 - (4 - 0)))) = -2
-- foldl (-) 0 [1,2,3,4] --> ((((0 - 1) - 2) - 3) - 4) = -10
-- da smo u fji ispod koristili foldl morali bismo prvo da stavimo acc pa r u fji azuriraj jer
-- foldl hvata prvo akumulator pa pojedinacne elemente iz liste

ponisti :: Student -> [Rezultat] -> [Rezultat]
ponisti s rez = foldr azuriraj [] rez
	where azuriraj r acc = if fst r == s then (s, Nothing) : acc
									 else r : acc

ponistiSve :: [Rezultat] -> [Rezultat]
ponistiSve rez = map (\r -> (fst r, Nothing)) rez


studije :: StepenStudija -> [Rezultat] -> [Rezultat]
studije ss rez = filter (\r -> (stepen $ fst r) == ss) rez

polozeni :: [Rezultat] -> [Rezultat]
polozeni rez = filter (\(s, mozdaPoeni) -> (izvuci mozdaPoeni) > 50) rez
    where izvuci Nothing = 0
          izvuci (Just poeni) = poeni

upisi :: Student -> Int -> [Rezultat] -> [Rezultat]
upisi s p rez = if elem s $ map fst rez then foldr azuriraj [] rez
                                        else (s, Just p) : rez
    where azuriraj r acc = (fst r, Just p) : acc

najboljih :: Int -> [Rezultat] -> [Int]
najboljih n rez = take n $ sortBy (flip compare) $ map (\(Just p) -> p) $ filter (/=Nothing) $ map snd rez