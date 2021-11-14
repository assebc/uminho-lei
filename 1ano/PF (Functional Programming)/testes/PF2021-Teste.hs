module PF2021_Teste where

import Data.List

--exercício 1

-- com import Data.List
remove :: Eq a => [a] -> [a] -> [a]
remove l [] = l
remove [] _ = []
remove l (x:xs) = remove (delete x l) xs

-- sem import Data.List
remove' :: Eq a => [a] -> [a] -> [a]
remove' l [] = l
remove' [] _ = []
remove' l (x:xs) = remove (delete' x l) xs
    where
        delete' :: Eq a => a -> [a] -> [a]
        delete' _ [] = []
        delete' n (x:xs)
            | n == x = xs
            | otherwise = n : delete' n xs

-- exercício 2

type MSet a = [(a,Int)]

-- 2 a)

removeMset :: Eq a => a -> MSet a -> MSet a
removeMset n [] = []
removeMset x ((a,n):as)
    | x == a = as
    | otherwise = (a,n) : removeMset x as

-- exercício 3

partes :: String -> Char -> [String]
partes [] a = []
partes l@(x:xs) a
    | a == x = partes xs a
    | otherwise = [[x]] ++ partes xs a
