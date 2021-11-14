module PF1819_Teste where

import Data.Char
import System.Random

-- exercício 1 

-- 1 a)

elemIndices' :: Eq a => a -> [a] -> [Int]
elemIndices' n [] = []
elemIndices' n (x:xs)
    | n == x = 0 : map (+1) (elemIndices' n xs)
    | otherwise = map (+1) (elemIndices' n xs) 

-- 1 b)

isSubsequenceOf' :: Eq a => [a] -> [a] -> Bool
isSubsequenceOf' [] _ = True
isSubsequenceOf' _ [] = True
isSubsequenceOf' l@(x:xs) (y:ys) = x == y && isSubsequenceOf' xs ys || isSubsequenceOf' l ys

-- exercício 2

data BTree a = Empty | Node a (BTree a) (BTree a)

-- 2 a)

lookupAP :: Ord a => a -> BTree (a,b) -> Maybe b
lookupAP _ Empty = Nothing
lookupAP n (Node (a,b) l r)
    | n == a = Just b
    | n < a = lookupAP n l
    | otherwise = lookupAP n r

-- 2 b)

zipWithBT :: (a -> b -> c) -> BTree a -> BTree b -> BTree c
zipWithBT _ Empty _ = Empty
zipWithBT _ _ Empty = Empty
zipWithBT f (Node m l r) (Node a b c) = Node (f m a) (zipWithBT f l b) (zipWithBT f r c)

-- exercício 3

digitAlpha :: String -> (String,String)
digitAlpha = foldr (\x (as,ds) -> if isAlpha x then (x:as,ds) else if isDigit x then (as,x:ds) else (as,ds) ) ([],[])

-- exercício 4

data Seq a = Nil | Cons a (Seq a) | App (Seq a) (Seq a)

-- 4 a)

firstSeq :: Seq a -> a
firstSeq (Cons a s) = a
firstSeq (App Nil s) = firstSeq s
firstSeq (App s _) = firstSeq s

-- 4 b)

dropSeq :: Int -> Seq a -> Seq a
dropSeq _ Nil = Nil
dropSeq n (Cons a s) = dropSeq (n - 1) s
dropSeq n (App s1 s2) 
    | n > nx = dropSeq (n - nx) s2
    | n == nx = s2
    | otherwise = (App (dropSeq n s1) s2)
        where 
            nx = contaCons s1

contaCons :: Seq a -> Int
contaCons Nil = 0
contaCons (Cons _ s) = 1 + contaCons s
contaCons (App s1 s2) = contaCons s1 + contaCons s2

-- 4 c)

instance Show a => Show (Seq a) where
    show x = "<<" ++ mostra x ++ ">>"

mostra :: Show a => Seq a -> String
mostra Nil = ""
mostra (Cons a Nil) = show a
mostra (Cons a s) = show a ++ "," ++ mostra s
mostra (App s1 s2) = mostra s1 ++ "," ++ mostra s2

-- exercício 5

type Mat a = [[a]]

-- 5 a)

getElem :: Mat a -> IO a
getElem mat = do
    let (linhas,colunas) = (length mat, length (head mat))
    randLine <- randomRIO (0,linhas - 1)
    randRow <- randomRIO (0,colunas - 1)
    return $ (mat !! randLine) !! randRow

-- 5 b)

magic :: Mat Int -> Bool
magic mat = linhasIguaisA n mat && colunasIguaisA n mat && diagonaisIguaisA n mat
    where 
        n = sum (head mat)

linhasIguaisA :: Int -> Mat Int -> Bool
linhasIguaisA n = foldl (\acc l -> sum l == n && acc) True 

colunasIguaisA :: Int -> Mat Int -> Bool
colunasIguaisA n mat = foldl (\acc x -> sum (map (\l -> l !! x) mat) == n && acc) True [0..(length mat - 1)]

diagonaisIguaisA :: Int -> Mat Int -> Bool
diagonaisIguaisA n mat = sum (map (\n -> (mat !! n) !! n) [0..ln]) == n && sum (map (\n -> (mat !! n) !! (ln - n)) [0..ln]) == n
    where 
        ln = length mat - 1