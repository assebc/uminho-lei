module PF1617_Teste where

import Data.Maybe

-- exercício 1

type MSet a = [(a,Int)]

-- 1 a)

cardMSet ::  MSet a -> Int
cardMSet = foldr ((+) . snd) 0

-- 1 b)
moda :: MSet a -> [a]
moda = fst . foldr (\(x,n) (acc,accn) -> if n >= accn then (if n > accn then [x] else x:acc,n) else (acc,accn)) ([],0)

-- 1 c)
converteMSet :: MSet a -> [a]
converteMSet = foldr (\(x,n) -> (++) $ replicate n x) []

-- 1 d)
addNcopies :: Eq a => MSet a -> a -> Int -> MSet a
addNcopies mset elm num = foldr (\(x,n) -> (:) (x,n + (if x == elm then num else 0))) [] mset

-- exercicio 2

data SReais = AA Double Double | FF Double Double
            | AF Double Double | FA Double Double
            | Uniao SReais SReais

-- 2 a)

instance Show SReais where
    show (Uniao a b) = "(" ++ show a ++ " U " ++ show b ++ ")"
    show intv = ch1 ++ num1 ++ "," ++ num2 ++ ch2
        where (ch1,num1,num2,ch2) = case intv of AA a b -> ("]",show a,show b,"[")
                                                 AF a b -> ("]",show a,show b,"]")
                                                 FA a b -> ("[",show a,show b,"[")
                                                 FF a b -> ("[",show a,show b,"]")
-- 2 b)

pertence :: Double -> SReais -> Bool
pertence num (Uniao a b) = pertence num a || pertence num b
pertence num intv = (af1 && num >= num1 || num > num1) && (af2 && num <= num2 || num < num2)
    where 
        (af1,num1,num2,af2) = case intv of AA a b -> (False,a,b,False)
                                           AF a b -> (False,a,b,True)
                                           FA a b -> (True,a,b,False)
                                           FF a b -> (True,a,b,True)

-- 2 c)

tira ::  Double -> SReais -> SReais
tira n (Uniao a b) 
    | pertence n a = Uniao (tira n a) b
    | pertence n b = Uniao a (tira n b)
    | otherwise = (Uniao a b)
tira n intv = case intv of AA a b -> if n > a && n < b then (Uniao (AA a n) (AA n b)) else intv
                           AF a b -> if n == b then AA a b else if n > a && n < b then (Uniao (AA a n) (AF n b)) else intv
                           FA a b -> if n == a then AA a b else if n > a && n < b then (Uniao (FA a n) (AA n b)) else intv
                           FF a b -> if n == b then FA a b else if n == a then AF a b else if n > a && n < b then (Uniao (FA a n) (AF n b)) else intv

-- exercicio 3

data RTree a = R a [RTree a]


-- 3 a)

percorre :: [Int] -> RTree a -> Maybe [a]
percorre [] (R a _) = Just [a]
percorre _ (R a []) = Nothing
percorre (h:t) (R a r) 
    | length r < h || null auxX = Nothing
    | otherwise = Just (a:auxX)
        where 
            aux = percorre t (r !! (h - 1))
            auxX = fromMaybe [] aux

-- 3 b) 

procura :: Eq a => a -> RTree a -> Maybe [Int]
procura n (R a r) 
    | n == a = Just []
    | null r = Nothing
    | otherwise = foldl (\acc num -> if procura n (r !! (num - 1)) == Nothing then acc else Just (num:fromMaybe [] (procura n (r !! (num - 1))))) Nothing [1..length r]