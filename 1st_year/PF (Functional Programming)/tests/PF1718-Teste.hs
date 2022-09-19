module PF1718_Teste where

import Data.List
import System.Random

-- exercicio 1

insert :: Ord a => a -> [a] -> [a]
insert x l 
    | null l = [x] 
    | x > h = h:insert x t
    | otherwise = x:h:t
        where 
            (h:t) = l

-- exercicio 2

catMaybes :: [Maybe a] -> [a]
catMaybes [] = []
catMaybes (h:t) = case h of Just x -> x:catMaybes t
                            otherwise -> catMaybes t

-- exercicio 3

data Exp a = Const a | Var String | Mais (Exp a) (Exp a) | Mult (Exp a) (Exp a)

instance Show a => Show (Exp a) where
    show (Const a) = show a
    show (Var a) = a
    show (Mais a b) = "(" ++ show a ++ " + " ++ show b ++ ")"
    show (Mult a b) = "(" ++ show a ++ " * " ++ show b ++ ")"

-- exercicio 4

sortOn ::  Ord b => (a -> b) -> [a] -> [a]
sortOn _ [] = []
sortOn f (h:t) = insert' h (sortOn f t)
    where 
        insert' a [] = [a]
        insert' a (x:y) = if f a > f x then x:insert' a y else a:x:y

-- exercicio 5

-- 5 a)
amplitude ::  [Int] -> Int
amplitude [] = 0
amplitude l = mx - mn
    where 
        (mx,mn) = foldl (\(a,b) n -> (if n > a then n else a,if n < b then n else b)) (head l,head l) l 

-- 5 b)

parte :: [Int] -> ([Int],[Int])
parte l = foldl1 (\(acc1,acc2) (a,b) -> if amplitude acc1 + amplitude acc2 < amplitude a + amplitude b then (acc1,acc2) else (a,b)) combinacoes
    where 
        combinacoes = foldl (\acc n -> splitAt n sl : acc) [] [1..(length l - 1)]
        sl = sort l

-- Exercicio 6

data Imagem = Quadrado Int
            | Mover (Int,Int) Imagem
            | Juntar [Imagem] deriving (Show)

-- 6 a)

conta :: Imagem -> Int
conta (Quadrado _) = 1
conta (Mover (_,_) im) = conta im
conta (Juntar l) = sum (map conta l)

-- 6 b)

apaga :: Imagem -> IO Imagem
apaga im = do
    let indquad = indices_quadrados im
    randNum <- randomRIO (1,length indquad)
    let indtoremove = indquad !! (randNum - 1)
    return $ apaga_indice indtoremove im 

-- 6 c)

indices_quadrados :: Imagem -> [Int]
indices_quadrados (Quadrado n) = [n]
indices_quadrados (Mover (_,_) im) = indices_quadrados im
indices_quadrados (Juntar l) = concatMap indices_quadrados l

-- 6 d)

apaga_indice :: Int -> Imagem -> Imagem
apaga_indice x (Quadrado n) = if x == n then Juntar [] else Quadrado n
apaga_indice x (Mover (a,b) im) = Mover (a,b) (apaga_indice x im)
apaga_indice x (Juntar l) = Juntar (map (apaga_indice x) l)