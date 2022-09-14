module Ficha04 where

import Data.Char

-- exercício 1

-- 1 a)

-- [x | x <- [1..20], mod x 2 == 0, mod x 3 == 0]
-- R : [2,4,5,8,10,12,14,16,18,20] && [3,6,9,12,15,18] = [6,12,18]

-- 1 b)

-- [x | x <- [y | y <- [1..20], mod y 2 == 0], mod x 3 == 0]
-- R : [2,4,5,8,10,12,14,16,18,20] && [3,6,9,12,15,18] == [6,12,18]

-- 1 c)

-- [(x,y) | x <- [0..20], y <- [0..20], x+y == 30]
-- R : [(20,10),(10,20),(15,15),(11,19),(19,11),(12,18),(18,12),(13,17),(17,13),(14,16),(16,14)]

-- 1 d)

-- [sum [y | y <- [1..x], odd y] | x <- [1..10]]
-- R : sum [1,3,5,7,9] [1..10] == [1,1,4,4,9,9,16,16,25,25]

-- exercício 2

-- 2 a)

-- [1,2,4,8,16,32,64,128,256,512,1024]
doisA = [2 ^ x | x <- [0..10]]

-- 2 b)

-- [(1,5),(2,4),(3,3),(4,2),(5,1)]
doisB = [(x,y) | x <- [1..5], y <- [1..5], x + y == 6]

-- 2 c)

-- [[1],[1,2],[1,2,3],[1,2,3,4],[1,2,3,4,5]]
doisC = [[1..x] | x <- [1..5]]

-- 2 d)

-- [[1],[1,1],[1,1,1],[1,1,1,1],[1,1,1,1,1]]
doisD = [replicate x 1 | x <- [1..5]]

-- 2 e)

-- [1,2,6,24,120,720]
doisE = [factorial x | x <- [1..6]]
    where
        factorial 0 = 1
        factorial x = x * factorial (x - 1)

-- exercício 3

digitAlpha :: String -> (String,String)
digitAlpha s = foldl (\(alpha,digit) x -> if isDigit x 
                                          then (alpha ,digit ++ [x]) 
                                          else if isAlpha x 
                                               then (alpha ++ [x],digit) 
                                               else (alpha,digit) ) ("","") s

-- exercício 4

nzp :: [Int] -> (Int,Int,Int)
nzp = foldl (\(n,z,p) x -> if x < 0
                           then (n+1,z,p)
                           else if x == 0
                                then (n,z+1,p)
                                else (n,z,p+1) ) (0,0,0)

-- exercício 5

divMod :: Integral a => a -> a -> (a,a)
divMod x y = foldl (\(a,r) n -> (a+1,r-y)) (0,x) [y,2*y..x]

-- exercício 6

{-
fromDigits :: [Int] -> Int
fromDigits [] = 0
fromDigits (h:t) = h*10^(length t) + fromDigits t
-}

fromDigits :: [Int] -> Int
fromDigits = foldl (\acc x -> x * 10 * acc ) 0 


