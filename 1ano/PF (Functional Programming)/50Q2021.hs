module FiftyQ where

-- 1

-- de forma recursiva
enumFromTo' :: Int -> Int -> [Int]
enumFromTo' start end
    | start < end = start : enumFromTo' (start+1) end
    | start > end = end : enumFromTo' (end+1) start
    | otherwise = [start]

-- de forma não recursiva
enumFromTo'' :: Int -> Int -> [Int]
enumFromTo'' start end 
    | start < end = [start..end]
    | end < start = enumFromTo'' end start
    | otherwise = [start] 

-- 2

enumFromThenTo' :: Int -> Int -> Int -> [Int]
enumFromThenTo' start next end
    | start > end && next - start > 0 || start < end && next - start < 0 = []
    | otherwise = start : enumFromThenTo' next ( (2 * next) - start ) end

-- 3

myconcat ::  [a] -> [a] -> [a]
myconcat [] l = l
myconcat (x:xs) l = x : myconcat xs l

-- 4

getFromIndex' :: [a] -> Int -> a
getFromIndex' (x:xs) n
    | n == 0 = x
    | otherwise = getFromIndex' xs (n-1)

-- 5

reverse' :: [a] -> [a]
reverse' [] = []
reverse' (x:xs) = reverse' xs ++ [x]

-- 6

take' :: Int -> [a] -> [a]
take' _ [] = []
take' 0 l = []
take' n (x:xs)
    | n < 0 = []
    | otherwise = x : take' (n-1) xs

-- 7

drop' :: Int -> [a] -> [a]
drop' _ [] = []
drop' 0 l = []
drop' n (x:xs)
    | n < 0 = []
    | otherwise = drop (n-1) xs

-- 8

zip' :: [a] -> [b] -> [(a,b)]
zip' [] _ = []
zip' _ [] = []
zip' (x:xs) (y:ys) = (x,y) : zip' xs ys

-- 9

elem' :: Eq a => a -> [a] -> Bool
elem' _ [] = False
elem' n (x:xs) = n == x || elem' n xs

-- 10

replicate' :: Int -> a -> [a]
replicate' 0 _ = []
replicate' n x
    | n < 0 = []
    | otherwise = x : replicate' (n-1) x

-- 11

intersperse' :: a -> [a] -> [a]
intersperse' n [] = [n]
intersperse' n (x:xs) = x : n : intersperse' n xs 

-- 12

group' :: Eq a => [a] -> [[a]]
group' [] = [[]]
group' (x:xs) = (x : takeWhile (== x) xs) : group' (dropWhile (== x) xs)

-- 13

concat' :: [[a]] -> [a]
concat' [] = []
concat' (x:xs) = x ++ concat' xs

-- 14

inits' :: [a] -> [[a]]
inits' [] = []
inits' l = inits' (init l) ++ [l]

-- 15

tails' :: [a] -> [[a]]
tails' [] = []
tails' l = [l] ++ tails' (tail l)

-- 16

isPrefixOf' :: Eq a => [a] -> [a] -> Bool
isPrefixOf' [] _ = True
isPrefixOf' _ [] = False
isPrefixOf' (x:xs) (y:ys) = x == y && isPrefixOf' xs ys

-- 17

isSuffixOf' :: Eq a => [a] -> [a] -> Bool
isSuffixOf' [] _ = False
isSuffixOf' _ [] = True
isSuffixOf' l ls@(x:xs) = l == l || isSuffixOf' l xs

-- 18

isSubsequeceOf' :: Eq a => [a] -> [a] -> Bool
isSubsequeceOf' [] _ = True
isSubsequeceOf' _  [] = True
isSubsequeceOf' l@(x:xs) (y:ys) = x == y && isSubsequeceOf' xs ys || isSubsequeceOf' l ys

-- 19

elemIndices' :: Eq a => a -> [a] -> [Int]
elemIndices' _ [] = []
elemIndices' n (x:xs)
    | n == x = 0 : map (+1) (elemIndices' n xs)
    | otherwise = map (+1) (elemIndices' n xs)

-- 20

nub' :: Eq a => [a] -> [a]
nub' [] = []
nub' (x:xs) = x : filter (/= x) (nub' xs)

-- 21

delete' :: Eq a => a -> [a] -> [a]
delete' _ [] = []
delete' n (x:xs)
    | n == x = xs
    | otherwise = x : delete' n xs

-- 22

remove :: Eq a => [a] -> [a] -> [a]
remove l [] = l
remove [] _ = []
remove l (x:xs) = remove (delete' x l) xs

-- 23

union' :: Eq a => [a] -> [a] -> [a]
union' l [] = l
union' l (x:xs)
    | elem x l = union' l xs
    | otherwise = union' (l ++ [x]) xs

-- 24

intersect' :: Eq a => [a] -> [a] -> [a]
intersect' l [] = []
intersect' [] l = l
intersect' (x:xs) l
    | elem x l = x : intersect' xs l
    | otherwise = intersect' xs l

-- 25

insert' :: Ord a => a -> [a] -> [a]
insert' n [] = [n]
insert' n (x:xs)
    | n > x = x : insert' n xs
    | otherwise = n : x : xs

-- 26

unwords' :: [String] -> String
unwords' [] = []
unwords' (x:xs) = x ++ (if null xs then "" else " " ) ++ unwords' xs 

-- 27

unlines' :: [String] -> String
unlines' [] = []
unlines' (x:xs) = x ++ "\n" ++ unlines' xs

-- 28

pMaior :: Ord a => [a] -> Int
pMaior [n] = 0
pMaior (x:xs)
    | x > (xs !! maior) = 0
    | otherwise = 1 + maior
        where
            maior = pMaior xs

-- 29

temRepetidos :: Eq a => [a] -> Bool
temRepetidos [] = False
temRepetidos (x:xs) = elem x xs || temRepetidos xs

-- 30

algarismos :: [Char] -> [Char]
algarismos [] = []
algarismos (x:xs) 
    | elem x ['0'..'9'] = x : algarismos xs 
    | otherwise = algarismos xs

-- 31

posImpares :: [a] -> [a]
posImpares [] = []
posImpares [x] = []
posImpares (h:x:xs) = x : posImpares xs

-- 32

posPares :: [a] -> [a]
posPares [] = []
posPares [x] = [x]
posPares (h:x:xs) = h : posPares xs

-- 33

isSorted :: Ord a => [a] -> Bool
isSorted [] = True
isSorted [x] = True
isSorted (h:x:xs) = x >= h && isSorted (x:xs)

-- 34

iSort :: Ord a => [a] -> [a]
iSort [] = []
iSort (x:xs) = insert' x (iSort xs)

-- 35

menor :: String -> String -> Bool
menor [] _ = True
menor _ [] = False
menor (x:xs) (y:ys) = x < y || menor xs ys

-- 36

elemMSet :: Eq a => a -> [(a,Int)] -> Bool
elemMSet _ [] = False
elemMSet x ((a,n):as) = x == a || elemMSet x as

-- 37

lengthMSet :: [(a,Int)] -> Int
lengthMSet [] = 0
lengthMSet ((a,n):as) = n + lengthMSet as

-- 38

converteMSet :: [(a,Int)] -> [a]
converteMSet [] = []
converteMSet ((a,n):as) = replicate n a ++ converteMSet as

-- 39

insereMSet :: Eq a => a -> [(a,Int)] -> [(a,Int)]
insereMSet a [] = [(a,1)]
insereMSet x ((a,n):as)
    | x == a = (a,n+1) : as
    | otherwise = (a,n) : insereMSet x as

-- 40

removeMSet :: Eq a => a -> [(a,Int)] -> [(a,Int)]
removeMSet _ [] = []
removeMSet x ((a,n):as)
    | x == a && n == 1 = as
    | x == a = (a,n-1) : as
    | otherwise = (a,n) : removeMSet x as

-- 41

constroiMSet :: Ord a => [a] -> [(a,Int)]
constroiMSet [] = []
constroiMSet (x:xs) = (x,1 + length (filter (==x) xs) ) : constroiMSet (filter (/=x) xs)

-- 42

partitionEithers :: [Either a b] -> ([a],[b])
partitionEithers [] = ([],[])
partitionEithers ((Left a):b) = (a:as,bs)
    where
        (as,bs) = partitionEithers b
partitionEithers ((Right a):b) = (as,a:bs)
    where
       (as,bs) = partitionEithers b 

-- 43

catMaybes :: [Maybe a] -> [a]
catMaybes [] = []
catMaybes (x:xs) = case x of Nothing -> catMaybes xs
                             Just x -> x : catMaybes xs

{-=======================================-}
data Movimento = Norte | Sul | Este | Oeste
               deriving Show
{-=======================================-}

-- 44

posicao :: (Int,Int) -> [Movimento] -> (Int,Int)
posicao (x,y) [] = (x,y)
posicao (x,y) (m:ms) = posicao (case m of Norte -> (x,y+1)
                                          Sul -> (x,y-1)
                                          Este -> (x-1,y)
                                          Oeste -> (x+1,y)) ms

-- 45

caminho :: (Int,Int) -> (Int,Int) -> [Movimento]
caminho (x,y) (x1,y1)
    | y < y1 = Norte : caminho (x,y+1) (x1,y1)
    | y > y1 = Sul : caminho (x,y-1) (x1,y1)
    | x < x1 = Este : caminho (x+1,y) (x1,y1)
    | x > x1 = Oeste : caminho (x-1,y) (x1,y1)
    | otherwise = []

-- 46

vertical :: [Movimento] -> Bool
vertical [] = False
vertical (m:ms) = case m of Este -> False
                            Oeste -> False
                            Norte -> vertical ms 
                            Sul -> vertical ms

{-=======================================-}
data Posicao = Pos Int Int
               deriving Show
{-=======================================-}

-- 47

maisCentral :: [Posicao] -> Posicao
maisCentral [Pos x y] = Pos x y
maisCentral ((Pos x y):(Pos x1 y1):cs) = if (x^2 + y^2) <= (x1^2 + y1^2) 
                                         then maisCentral (Pos x y : cs) 
                                         else maisCentral (Pos x1 y1 : cs)

-- 48

vizinhos ::  Posicao -> [Posicao] -> [Posicao]
vizinhos (Pos x y) ((Pos x1 y1):cs) = if (abs (x-x1) + abs (y-y1)) == 1
                                      then (Pos x1 y1) : vizinhos (Pos x y) cs
                                      else vizinhos (Pos x y) cs

-- 49

mesmaOrdenada :: [Posicao] -> Bool
mesmaOrdenada [Pos x y] = True
mesmaOrdenada ((Pos x y):(Pos x1 y1):cs) = y == y1 && mesmaOrdenada ((Pos x y):cs)

{-=======================================-}
data Semaforo = Verde | Amarelo | Vermelho
                deriving Show
{-=======================================-}

-- 50

interseccaoOk :: [Semaforo] -> Bool
interseccaoOk ss = length [s | s <- ss, case s of Vermelho -> False ; _ -> True] < 2