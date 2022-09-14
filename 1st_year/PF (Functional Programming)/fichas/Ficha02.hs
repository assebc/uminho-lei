module Ficha02 where

import Data.Char
import Data.List

-- exercício 1

-- 1 a)

funA :: [Double] -> Double
funA [] = 0
funA (y:ys) = y^2 + (funA ys)

{- 
funA [2,3,5,1]?
2*2 + 3*3 + 5*5 + 1*1 = 4 + 9 + 25 + 1 = 39
-}

-- 1 b)

funB :: [Int] -> [Int]
funB [] = []
funB (h:t) = if (mod h 2) == 0 
             then h : (funB t)
             else (funB t)

{-
funB [8,5,12]?
[8,12], pois 5 não é divisível por 2
-}

-- 1 c)

funC (x:y:t) = funC t
funC [x] = []
funC [] = []

{-
funC [1,2,3,4,5]?
[], qualquer que seja a lista dará lista vazia
-}

-- 1 d)

funD l = g [] l
g l [] = l
g l (h:t) = g (h:l) t

{-
funD "otrec"?
"certo", visto que a função é similar a uma pré-definida (flip) a qual inverte uma lista
-}

-- exercício 2 

-- 2 a)

dobros :: [Float] -> [Float]
dobros [] = []
dobros (x:xs) = 2 * x : dobros xs

-- 2 b)

numOcorre :: Char -> String -> Int
numOcorre _ [] = 0
numOcorre a (x:xs)
    | a == x = 1 + numOcorre a xs
    | otherwise = numOcorre a xs

-- 2 c)

positivos :: [Int] -> Bool
positivos [] = True
positivos (x:xs) = x > 0 && positivos xs

-- 2 d)

soPos :: [Int] -> [Int]
soPos [] = []
soPos l = filter (> 0) l

--ou//

soPos' :: [Int] -> [Int]
soPos' [] = []
soPos' (x:xs)
    | x > 0 = x : soPos' xs
    | otherwise = soPos' xs

-- 2 e)

somaNeg :: [Int] -> Int
somaNeg [] = 0
somaNeg l = sum (filter (< 0) l)

-- ou//

somaNeg' :: [Int] -> Int
somaNeg' [] = 0
somaNeg' (x:xs)
    | x < 0 = x + somaNeg' xs
    | otherwise = somaNeg' xs

-- 2 f)

tresUlt :: [a] -> [a]
tresUlt l
    | length l <= 3 = l
    | otherwise = drop (length l - 3) l

-- 2 g)

segundos :: [(a,b)] -> [b]
segundos [] = []
segundos ((a,b):as) = b : segundos as

-- ou//

segundos' :: [(a,b)] -> [b]
segundos' [] = []
segundos' (x:xs) = snd x : segundos' xs

-- 2 h)

nosPrimeiros :: Eq a => a -> [(a,b)] -> Bool
nosPrimeiros _ [] = False
nosPrimeiros x ((a,b):as) = x == a || nosPrimeiros x as

--ou//

nosPrimeiros' :: Eq a => a -> [(a,b)] -> Bool
nosPrimeiros' _ [] = False
nosPrimeiros' a (x:xs) = a == (fst x) || nosPrimeiros' a xs

-- 2 i)

sumTriplos :: (Num a,Num b,Num c) => [(a,b,c)] -> (a,b,c)
sumTriplos [] = (0,0,0)
sumTriplos [(a,b,c)] = (a,b,c)
sumTriplos ((a,b,c):(d,e,f):l) = sumTriplos ((a+d,b+e,c+f):l)

-- exercício 3

-- 3 a)

soDigitos :: [Char] -> [Char]
soDigitos l = filter (`elem` ['0'..'9']) l

-- 3 b)

minusculas :: [Char] -> Int
minusculas l = length(filter (`elem` ['a'..'z']) l)

-- ou//

minusculas' :: [Char] -> Int
minusculas' [] = 0
minusculas' (x:xs)
    | elem x ['a'..'z'] = 1 + minusculas' xs
    | otherwise = minusculas' xs

-- 3 c)

nums :: String -> [Int]
nums [] = []
nums (x:xs)
    | elem x ['0'..'9'] = ord x : nums xs
    | otherwise = nums xs

-- exercício 4

type Polinomio = [Monomio]
type Monomio = (Float,Int)

-- 4 a)

conta :: Int -> Polinomio -> Int
conta _ [] = 0
conta n ((b,e):p)
    | n == e = 1 + conta n p
    | otherwise = conta n p

-- 4 b)

grau :: Polinomio -> Int
grau [] = 0
grau (p:ps)
    | snd p > grau ps = snd p
    | otherwise = grau ps

-- 4 c)

selgrau :: Int -> Polinomio -> Polinomio
selgrau _ [] = []
selgrau n ((b,e):p)
    | n == e = (b,e) : selgrau n p
    | otherwise = selgrau n p

-- 4 d)

deriv :: Polinomio -> Polinomio
deriv [] = []
deriv ps@((b,e):p) = if e > 0 
                     then (b * fromIntegral e, e-1) : deriv ps 
                     else deriv p

-- 4 e)

calcula :: Float -> Polinomio -> Float
calcula _ [] = 0
calcula x ((b,e):p) = (b * x) ^ e + calcula x p

-- 4 f)

simp :: Polinomio -> Polinomio
simp [] = []
simp ((b,e):p) = if e == 0
                 then simp p
                 else (b,e) : simp p

-- 4 g)

mult :: Monomio -> Polinomio -> Polinomio
mult m [] = [m]
mult m@(b,e) ((b1,e1):p) = (b * b1, e + e1) : mult m p

-- 4 h)

normaliza :: Polinomio -> Polinomio
normaliza [] = []
normaliza ((b,e):(b1,e1):ps)
    | e == e1 = normaliza ((b+b1,e):ps)
    | conta e ps == 0 = (b,e) : normaliza ((b1,e1):ps)
    | otherwise = normaliza ((b,e) : ps ++ [(b1,e1)])
  
-- 4 i)

soma :: Polinomio -> Polinomio -> Polinomio
soma p ps
    | normaliza p == p && normaliza ps == ps = p ++ ps
    | otherwise = normaliza p ++ normaliza ps

-- 4 j)

produto :: Polinomio -> Polinomio -> Polinomio
produto _ [] = [] 
produto pl@(p:p1) ps
    | normaliza pl == pl && normaliza ps == ps = soma (mult p ps) (produto p1 ps)
    | otherwise = produto (normaliza pl) (normaliza ps)

-- 4 k)

ordena :: Polinomio -> Polinomio
ordena [] = []
ordena ((b,e):ps) = ordena (ma ps) ++ [(b,e)] ++ ordena (me ps)
     where 
        ma [] = []
        ma ((bx,ex):xs) = if (ex > e || (ex == e && bx >= b)) 
                          then (bx,ex):me xs 
                          else ma xs
        me [] = []
        me ((bx,ex):xs) = if (ex < e || (ex == e && bx < b)) 
                          then (bx,ex):me xs 
                          else me xs

-- 4 l)

equiv :: Polinomio -> Polinomio -> Bool
equiv [] [] = True
equiv _ [] = False
equiv [] _ = False
equiv p ps = ordena(normaliza p) == ordena(normaliza ps)
