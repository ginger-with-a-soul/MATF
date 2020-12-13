import Data.Char

uzastopni :: [Char] -> [Char]
uzastopni [] = []
uzastopni (x:xs) = if isLower x then takeWhile isLower (x:xs)
 else takeWhile isUpper (x:xs)

sekvence :: [Char] -> [Int]
sekvence [] = []
sekvence lista = uz : ostatak
 where
  uz = length $ uzastopni lista
  ostatak = sekvence $ drop uz lista


listaSekvenci :: [[Char]] -> [[Int]]
listaSekvenci lista = map(\t -> sekvence t) lista