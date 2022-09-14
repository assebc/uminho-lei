module Ficha05 where

import Data.List

-- exercício 1

-- 1 a)

any' :: (a -> Bool) -> [a] -> Bool
any' f [] = False
any' f (x:xs) =  f x || any' f xs

-- 1 b)

zipWith' :: (a->b->c) -> [a] -> [b] -> [c] 
zipWith' f (x:xs) (y:ys) = f x y : zipWith' f xs ys
zipWith' _ _ _ = []

-- 1 c)

takeWhile' :: (a->Bool) -> [a] -> [a]
takeWhile' _ [] = []
takeWhile' f (x:xs) 
    | f x = x : takeWhile' f xs
    | otherwise = []

-- 1 d)

dropWhile' :: (a->Bool) -> [a] -> [a]
dropWhile' _ [] = []
dropWhile' f (x:xs)
    | f x = dropWhile' f xs
    | otherwise = xs

-- 1 e)

span' :: (a-> Bool) -> [a] -> ([a],[a])
span' _ [] = ([],[])
span' f (x:xs)
    | f x = (x:s1,s2)
    | otherwise = ([],[])
        where 
            (s1,s2) = span' f xs

-- 1 f)

deleteBy' :: (a -> a -> Bool) -> a -> [a] -> [a]
deleteBy' f e (x:xs)
    | f e x = xs
    | otherwise = x : deleteBy' f e xs

-- 1 g)

sortOn' :: Ord b => (a -> b) -> [a] -> [a]
sortOn' f [] = []
sortOn' f (x:xs) = insere x (sortOn' f xs)
    where
        insere ac [] = [ac]
        insere ac (y:ys) = if f ac < f y
                           then y : insere ac ys
                           else ac : y : ys

-- exercício 2

type Polinomio = [Monomio]
type Monomio = (Float,Int)

-- 2 a)

selgrau :: Int -> Polinomio -> Polinomio
selgrau n p = filter (\x -> snd x == n) p

-- 2 b)

conta :: Int -> Polinomio -> Int
conta n p = length (filter (\x -> snd x == n) p)

-- 2 c)

grau :: Polinomio -> Int
grau p = foldl (\acc x -> if acc > snd x then acc else snd x) 0 p

-- 2 d)

deriv :: Polinomio -> Polinomio
deriv p = filter (/= (0,0))  (map (\(b,e) -> if e > 0 then (b * fromIntegral e, e - 1) else (0,0)) p)

-- 2 e)

calcula :: Float -> Polinomio -> Float
calcula a = foldl (\acc (b,e) -> acc + b * (a ^ e)) 0

-- 2 f)

simp :: Polinomio -> Polinomio
simp p = filter (\(b,e) -> b /= 0 ) p

-- 2 g)

mult :: Monomio -> Polinomio -> Polinomio
mult (b1,e1) p = map (\(b,e) -> (b*b1,e+e1)) p

-- 2 h)

ordena :: Polinomio -> Polinomio
ordena p = sortOn' (snd) p

-- 2 i)

normaliza :: Polinomio -> Polinomio
normaliza [] = []
normaliza ((b,e):ps) = (sum [bs | (bs,es) <- selgrau e ps] + b,e) : normaliza [(bo,eo) | (bo,eo) <- ps, eo /= e]

-- 2 j)

soma :: Polinomio -> Polinomio -> Polinomio
soma p ps = normaliza ((++) p ps)

-- 2 k)

produto :: Polinomio -> Polinomio -> Polinomio
produto p ps = foldl (\acc x -> soma (mult x ps) acc) [] p

-- 2 l)

equiv :: Polinomio -> Polinomio -> Bool
equiv p ps = null (simp (soma p (mult (-1,0) ps) ) )

-- exercício 3

type Mat a = [[a]]

-- 3 a)

dimOK :: Mat a -> Bool
dimOK [] = True
dimOk (m:ms) = all (\x -> length m == length x) ms

-- 3 b)

dimMat :: Mat a -> (Int,Int)
dimMat m = (length m, length (head m))

-- 3 c)

addMat :: Num a => Mat a -> Mat a -> Mat a
addMat = zipWith (zipWith (+))

-- 3 d)

transpose :: Mat a -> Mat a
transpose m = [ [(m !! j) !! i | j <- [0..l-1] ] | i <- [0..c-1]]
    where 
        (l,c) = dimMat m

-- 3 e)

multMat :: Num a => Mat a -> Mat a -> Mat a
multMat m1 m2 = [ [ sum (zipWith (*) (m1 !! j) [ x !! i | x <- m2 ]) | i <- [0..c-1] ] | j <- [0..l-1] ]
    where 
        (l,_) = dimMat m1
        (_,c) = dimMat m2

-- 3 f)

zipWMat :: (a -> b -> c) -> Mat a -> Mat b -> Mat c
zipWMat = zipWith . zipWith


-- 3 g)

triSup :: Real a => Mat a -> Bool
triSup = snd . foldl (\(acc1,acc2) line -> (acc1+1, all (== 0) (take acc1 line) && acc2)) (0,True)

-- 3 h)

rotateLeft :: Mat a -> Mat a
rotateLeft m = [ [ map (!! i) m !! j | j <- [0..l-1] ] | i <- [c-1,c-2..0]] 
    where 
        (l,c) = dimMat m