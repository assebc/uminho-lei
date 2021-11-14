module PF1920_Teste where

import Data.List

-- exercício 1

-- 1 a)

intersect' :: Eq a => [a] -> [a] -> [a]
intersect' l [] = []
intersect' [] l = []
intersect' (x:xs) l = if elem x l 
                      then x : intersect' xs l 
                      else intersect' xs l

-- 1 b)

tails' :: [a] -> [[a]]
tails' [] = []
tails' l = [l] ++ tails' (tail l)

-- exercício 2

type ConjInt = [Intervalo]
type Intervalo = (Int,Int)

-- 2 a)

elems :: ConjInt -> [Int]
elems [] = []
elems ((n,ns):es)
    | n == ns = n : elems es
    | otherwise = n : elems ((succ n, ns) : es)

-- 2 b)

geraconj :: [Int] -> ConjInt
geraconj [] = []
geraconj (x:xs) = (x, s) : geraconj (dropWhile (<= s) xs)
    where
        s = foldl (\acc a -> if a == succ acc then a else acc) x xs

-- exercício 3

data Contacto = Casa Integer
              | Trab Integer
              | Tlm Integer
              | Email String
              deriving (Show)

type Nome = String
type Agenda = [(Nome, [Contacto])]

-- 3 a)

acrescEmail :: Nome -> String -> Agenda -> Agenda
acrescEmail nome email [] = [(nome, [Email email])]
acrescEmail nome email ((n,c):a)
    | nome == n = (nome, (Email email) : c) : a
    | otherwise = (n,c) : acrescEmail nome email a

-- 3 b)

verEmails :: Nome -> Agenda -> Maybe [String]
verEmails nome [] = Nothing
verEmails nome ((n,c):a)
    | nome == n = case c of [Email email] -> Just [email]
                            _ -> Nothing
    | otherwise = verEmails nome a

-- 3 c)

consulta :: [Contacto] -> ([Integer],[String])
consulta = foldr (\x (i,s) -> case x of Email email -> (i,email:s) ; otherwise -> (n x:i,s) ) ([],[])
    where
        n x = case x of  Casa n1 -> n1
                         Trab n2 -> n2
                         Tlm n3 -> n3

-- 3 d)

consultaIO :: Agenda -> IO ()
consultaIO agenda = do
    nome <- getLine
    let contactos = aux nome agenda
    putStr (concat [show x ++ "\n" | x <- contactos])
        where 
            aux _ [] = []
            aux nome ((name,contactos):t) = if name == nome 
                                            then contactos 
                                            else aux nome t

-- exercício 4

data RTree a = R a [RTree a] deriving (Show, Eq)

-- 4 a)

paths :: RTree a -> [[a]]
paths (R node []) = [[node]]
paths (R node branches) = [ node : x | x <- concat [paths branch | branch <- branches]]

-- 4 b)

unpaths :: Eq a => [[a]] -> RTree a
unpaths [[x]] = R x []
unpaths list = R n [unpaths (foldl (\acc branch -> if head branch == y then branch:acc else acc) [] branches) | y <- heads]
    where 
        n = head $ head list
        branches = [tail x | x <- list]
        heads = Data.List.nub [head x | x <- branches]