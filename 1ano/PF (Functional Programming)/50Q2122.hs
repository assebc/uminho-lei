module FiftyQ where

import Data.List

enumFromTo' :: Int -> Int -> [Int]
enumFromTo' start end
    | start < end = start : enumFromTo' (start+1) end
    | end > start = end : enumFromTo' start (end-1)
    | otherwise = [start]

enumFromThenTo' :: Int -> Int -> Int -> [Int]
enumFromThenTo' start next end
    | start > end && next - start > 0 || start < end && next - start < 0 = []
    | otherwise = start : enumFromThenTo' next ( ( 2 * next) - start ) end


myconcat ::  [a] -> [a] -> [a]
myconcat [] l = l
myconcat (x:xs) l = x : myconcat xs l

getFromIndex' :: [a] -> Int -> a
getFromIndex' (x:xs) n
    | n == 0 = x
    | otherwise = getFromIndex' xs (n-1)

myreverse :: [a] -> [a]
myreverse [] = []
myreverse (x:xs) = myreverse xs ++ [x]

mytake :: Int -> [a] -> [a]
mytake n [] = []
mytake n (x:xs)
    | n == 0 = []
    | n > 0 = x : mytake (n-1) xs
    | otherwise = [] 

mydrop :: Int -> [a] -> [a]
mydrop n [] = []
mydrop n l@(x:xs)
    | n < 0 = l
    | n > 0 = mydrop (n-1) xs
    | otherwise = l

myzip :: [a] -> [b] -> [(a,b)]
myzip [] _ = []
myzip _ [] = []

myreplicate :: Int -> a -> [a] 
myreplicate n x
    | n <= 0 = []
    | otherwise = x : myreplicate (n-1) x

myintersperse :: a -> [a] -> [a]
myintersperse n [] = []
myintersperse n (x:xs) = x : n : myintersperse n xs

mygroup :: Eq a => [a] -> [[a]]
mygroup [] = []
mygroup (x:xs) = (x : takeWhile (==x) xs) : mygroup (dropWhile (==x) xs)

concatL :: [[a]] -> [a]
concatL [] = []
concatL (x:xs) = x ++ concatL xs

myinits :: [a] -> [[a]]
myinits [] = []
myinits l = myinits (init l) ++ [l] 

mytails :: [a] -> [[a]]
mytails [] = []
mytails l = [l] ++ mytails (tail l)

heads :: [[a]] -> [a]
heads [] = []
heads ([]:xs) = heads xs
heads (x:xs) = head x : heads xs

total :: [[a]] -> Int
total [] = 0
total ([]:xs) = total xs
total (x:xs) = length(x) + total xs

fun :: [(a,b,c)] -> [(a,c)]
fun [] = []
fun ((a,b,c):xs) = (a,c) : fun xs

cola :: [(String,b,c)] -> String
cola [] = []
cola ((a,b,c):t) = a ++ cola t

idade :: Int -> Int -> [(String,Int)] -> [String] 
idade x y [] = []
idade x y ((nom,nas):t)
    | x-y > nas = idade x y t
    | otherwise = nom : idade x y t

powerEnumFrom :: Int -> Int -> [Int]
powerEnumFrom n m  
    | m > 1 = powerEnumFrom n (m - 1) ++ [n^(m-1)]
    | otherwise = []

isPrime :: Int -> Bool
isPrime n 
    | n >= 2 = primeCheck n 2
    | otherwise = False
        where
            primeCheck :: Int -> Int -> Bool
            primeCheck n m
                | m * m > n = True -- equivalente a: m > √n (assim trabalhamos apenas com valores inteiros)
                | mod n m == 0 = False
                | otherwise = primeCheck n (m + 1)

sisPrefixOf :: Eq a => [a] -> [a] -> Bool
sisPrefixOf [] [] = True
sisPrefixOf _ [] = False
sisPrefixOf (x:xs) (y:ys) = x == y && sisPrefixOf xs ys

sisSuffixOf :: Eq a => [a] -> [a] -> Bool 
sisSuffixOf _ [] = False
sisSuffixOf [] _ = True
sisSuffixOf l ls@(x:xs) = l == l || sisSuffixOf l xs

iasSubsequeceOf :: Eq a => [a] -> [a] -> Bool
iasSubsequeceOf [] _ = True
iasSubsequeceOf _  [] = True
iasSubsequeceOf l@(x:xs) (y:ys) = x == y && iasSubsequeceOf xs ys || iasSubsequeceOf l ys

elemIndices' :: Eq a => a -> [a] -> [Int]
elemIndices' _ [] = []
elemIndices' n (x:xs)
    | n == x = 0 : map (+1) (elemIndices' n xs)
    | otherwise = map (+1) (elemIndices' n xs)

nub' :: Eq a => [a] -> [a]
nub' [] = []
nub' (x:xs) = x : filter (/= x) (nub' xs)

delete' :: Eq a => a -> [a] -> [a]
delete' _ [] = []
delete' n (x:xs)
    | n == x = xs
    | otherwise = x : delete' n xs

remove :: Eq a => [a] -> [a] -> [a]
remove l [] = l
remove [] _ = []
remove l (x:xs) = remove (delete' x l) xs

union' :: Eq a => [a] -> [a] -> [a]
union' l [] = l
union' l (x:xs)
    | elem x l = union' l xs
    | otherwise = union' (l ++ [x]) xs

intersect' :: Eq a => [a] -> [a] -> [a]
intersect' l [] = []
intersect' [] l = l
intersect' (x:xs) l
    | elem x l = x : intersect' xs l
    | otherwise = intersect' xs l

insert' :: Ord a => a -> [a] -> [a]
insert' n [] = [n]
insert' n (x:xs)
    | n > x = x : insert' n xs
    | otherwise = n : x : xs

aunwords :: [String] -> String
aunwords [] = []
aunwords (x:xs) = x ++ (if null xs then "" else " " ) ++ aunwords xs 

aunlines :: [String] -> String
aunlines [] = []
aunlines (x:xs) = x ++ "\n" ++ aunlines xs

pMaior :: Ord a => [a] -> Int
pMaior [n] = 0
pMaior (x:xs)
    | x > (xs !! maior) = 0
    | otherwise = 1 + maior
        where
            maior = pMaior xs

temRepetidos :: Eq a => [a] -> Bool
temRepetidos [] = False
temRepetidos (x:xs) = elem x xs || temRepetidos xs

algarismos :: [Char] -> [Char]
algarismos [] = []
algarismos (x:xs) 
    | elem x ['0'..'9'] = x : algarismos xs 
    | otherwise = algarismos xs

posImpares :: [a] -> [a]
posImpares [] = []
posImpares [x] = []
posImpares (h:x:xs) = x : posImpares xs

posPares :: [a] -> [a]
posPares [] = []
posPares [x] = [x]
posPares (h:x:xs) = h : posPares xs

isSorted :: Ord a => [a] -> Bool
isSorted [] = True
isSorted [x] = True
isSorted (h:x:xs) = x >= h && isSorted (x:xs)

iSort :: Ord a => [a] -> [a]
iSort [] = []
iSort (x:xs) = insert' x (iSort xs)

menor :: String -> String -> Bool
menor [] _ = True
menor _ [] = False
menor (x:xs) (y:ys) = x < y || menor xs ys

preCrescente :: Ord a => [a] -> [a]
preCrescente [] = []
preCrescente (x:y:xs) = if(x<=y) then x:y:preCrescente xs else [x]

data Movimento = Norte | Sul | Este | Oeste deriving Show

hasLoops :: (Int,Int) -> [Movimento] -> Bool
hasLoops (x,y) [] = False
hasLoops (x,y) mr = posicao (x,y) (movimento (x,y) mr)

posicao :: (Int,Int) -> (Int,Int) -> Bool
posicao (x,y) (x1,y1) = x == x1 && y == y1

movimento :: (Int,Int) -> [Movimento] -> (Int,Int)
movimento (x,y) [] = (x,y)
movimento (x,y) (m:ms) = movimento (case m of Norte -> (x,y+1)
                                              Este -> (x+1,y)
                                              Oeste -> (x-1,y)
                                              Sul -> (x,y-1)) ms

data Equipamento = Bom | Razoavel | Avariado deriving Show

naoReparar :: [Equipamento] -> Int
naoReparar e = foldl(\acc x -> case x of Avariado -> 1 + acc
                                         Razoavel -> acc
                                         Bom -> acc) 0 e
