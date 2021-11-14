module Ficha01 where

import Data.Char

-- exercício 1

-- 1 a)

perimetro :: Double -> Double
perimetro x = 2 * x * pi

-- 1 b)

dist :: (Double,Double) -> (Double,Double) -> Double
dist (x1,y1) (x2,y2) = sqrt (x ^ 2 + y ^ 2)
    where 
        x= x1-x2
        y= y1-y2

-- 1 c)

primUlt :: [Double] -> (Double,Double)
primUlt l = (head l,last l)

-- 1 d)

multiplo :: Int -> Int -> Bool
multiplo m n = mod m n == 0

-- 1 e)

truncaImpar :: [Int] -> [Int]
truncaImpar l = if odd (length l)
                then tail l
                else l 

-- 1 f)

max2 :: Int -> Int -> Int
max2 x y = if x > y
           then x
           else y

-- 1 g)

max3 :: Int -> Int -> Int -> Int
max3 x y z = if x > w
             then x
             else w
    where
        w = max2 y z

-- exercício 2

-- 2 a)

nRaizes :: Double -> Double -> Double -> Int
nRaizes a b c
    | b ^ 2 - 4 * a * c == 0 = 1
    | b ^ 2 - 4 * a * c < 0 = 0
    | otherwise = 2

-- 2 b)

raizes :: Double -> Double -> Double -> [Double]
raizes a b c = case (nRaizes a b c) of 1 -> [(-b) / 2 * a]
                                       2 -> [((-b + sqrt(b ^ 2 - 4 * a * c)) / 2 * a), ((-b - sqrt(b ^ 2 - 4 * a * c)) / 2 * a)]
                                       _ -> []

-- exercício 3

type Hora = (Int,Int)

testHora :: Hora -> Bool
testHora (h,m) = elem h [0..23] && elem m [0..59]

-- 3 b)

compareHora :: Hora -> Hora -> Hora
compareHora (h,m) (h1,m1) = if testedhour1 && testedhour2
                            then if (h * 60 + m) >= (h1 * 60 + m1)
                                 then (h,m)
                                 else (h1,m1)
                            else error "no valid hours"
    where
        testedhour1 = testHora (h,m)
        testedhour2 = testHora (h1,m1)

-- 3 c)

hora2minutes :: Hora -> Int
hora2minutes (h,m) = h * 60 + m

-- 3 d)

minutes2hora :: Int -> Hora
minutes2hora m = (div m 60,mod m 60)

-- 3 e)

diffHora :: Hora -> Hora -> Int
diffHora (h,m) (h1,m1) = abs (min1 - min2)
    where
        min1 = hora2minutes (h,m)
        min2 = hora2minutes (h1,m1)

-- 3 f)

addMin :: Int -> Hora -> Hora
addMin m1 (h,m)
    | m + m1 == 60 = (h+1,0)
    | m + m1 > 60 = (h+1,(m+m1)-60)
    | otherwise = (h,m+m1)

-- exercício 4

data Hour = H Int Int deriving (Show,Eq)

-- 4 a)

testHour :: Hour -> Bool
testHour (H h m) = elem h [0..23] && elem m [0..59]

-- 4 b)

compareHour :: Hour -> Hour -> Hour
compareHour (H h m) (H h1 m1) = if testedhour1 && testedhour2
                                then if (h * 60 + m) >= (h1 * 60 + m1)
                                     then (H h m)
                                     else (H h1 m1)
                            else error "no valid hours"
    where
        testedhour1 = testHour (H h m)
        testedhour2 = testHour (H h1 m1)

-- 4 c)

hours2minutes :: Hour -> Int
hours2minutes (H h m) = h * 60 + m

-- 4 d)

minutes2hours :: Int -> Hour
minutes2hours m = (H (div m 60) (mod m 60) )

-- 4 e)

diffHours :: Hour -> Hour -> Int
diffHours (H h m) (H h1 m1) = abs (min1 - min2)
    where
        min1 = hours2minutes (H h m)
        min2 = hours2minutes (H h1 m)

-- 4 f)

addMinutes :: Int -> Hour -> Hour
addMinutes m1 (H h m)
    | m + m1 == 60 = (H (h+1) 0)
    | m + m1 > 60 = (H (h+1) ((m+m1)-60) )
    | otherwise = (H h (m+m1) )

-- exercício 5

data Semaforo = Verde | Amarelo | Vermelho deriving (Show,Eq)

-- 5 a)

next :: Semaforo -> Semaforo
next s = case s of Verde -> Amarelo
                   Amarelo -> Vermelho
                   Vermelho -> Verde

-- 5 b)

stop :: Semaforo -> Bool
stop s = if s == Vermelho
         then True
         else False

-- 5 c)

safe :: Semaforo -> Semaforo -> Bool
safe s s1 = if s == Verde && s1 == Verde
            then True
            else False

-- exercício 6

data Ponto = Cartesiano Double Double | Polar Double Double
             deriving (Show,Eq)

-- 6 a)

posx :: Ponto -> Double 
posx (Cartesiano x y) = abs x
posx (Polar x y) = abs ((cos y) * x)

-- 6 b)

posy :: Ponto -> Double 
posy (Cartesiano x y) = abs y
posy (Polar x y) = abs ((sin y) * x)

-- 6 c)

raio :: Ponto -> Double
raio (Cartesiano x y) = sqrt(x ^ 2 + y ^ 2)
raio (Polar x y) = abs x

-- 6 d)

angulo :: Ponto -> Double
angulo (Polar x y) = y
angulo (Cartesiano x y)
    | y == 0 && x > 0  = 0 --eixo x+
    | y == 0 && x < 0  = 180 --eixo x-
    | x == 0 && y > 0  = 90 --eixo y+
    | x == 0 && y < 0  = -90 --eixo y-
    | x == 0 && y == 0 = 0 --centro
    | x > 0 && y > 0 || x > 0 && y < 0 = atan (y/x) * 180/pi --1/4 quadrante
    | x < 0 && y > 0 = -atan (y/x)*180/pi + 90 --2 quadrante
    | x < 0 && y < 0 = -atan (y/x)*180/pi -90 --3 quadrante
    | otherwise = error "missing coords"

-- 6 e)

distP :: Ponto -> Ponto -> Double
distP (Cartesiano x y) (Cartesiano x1 y1) = sqrt( ( (x - x1) ^ 2) + ((y - y1) ^ 2) )
distP (Cartesiano x y) (Polar x1 y1) = sqrt( ( (x - (x1 * (cos y1))) ^ 2 + ((y - (x1 * (sin y1))) ^ 2) ) ) 
distP (Polar x y) (Polar x1 y1) = sqrt( (((x * (cos y)) - (x1 * (cos y1))) ^ 2) + (((x * sin y) - (x1 * cos y1)) ^ 2) )
distP (Polar x1 y1) (Cartesiano x y) = sqrt( ( (x - (x1 * (cos y1))) ^ 2 + ((y - (x1 * (sin y1))) ^ 2) ) ) 

-- exercício 7

data Figura = Circulo Ponto Double
            | Retangulo Ponto Ponto
            | Triangulo Ponto Ponto Ponto
              deriving (Show,Eq)

-- 7 a)

poligono :: Figura -> Bool
poligono (Circulo _ r) = r > 0
poligono (Retangulo (Cartesiano x1 y1) (Cartesiano x2 y2)) = ((x1 /= x2) && (y1 /= y2))
poligono (Triangulo (Cartesiano x1 y1) (Cartesiano x2 y2) (Cartesiano x3 y3)) = ((x1 /= x2) && (x2 /= x3) && (x1 /= x3) && (y1 /= y2) && (y2 /= y3) && (y1 /= y3))

-- 7 b)

vertices :: Figura -> [Ponto]
vertices (Retangulo (Cartesiano x1 y1) (Cartesiano x2 y2)) = [(Cartesiano x1 y1),(Cartesiano x1 y2),(Cartesiano x2 y2),(Cartesiano x2 y1)]
vertices (Triangulo (Cartesiano x1 y1) (Cartesiano x2 y2)(Cartesiano x3 y3)) = [(Cartesiano x1 y1),(Cartesiano x2 y2),(Cartesiano x3 y3)]

-- 7 c)

area :: Figura -> Double
area (Circulo _ r) = r ^ 2 * pi
area (Retangulo (Cartesiano x1 y1)(Cartesiano x2 y2)) = abs(x1 - x2) * abs(y1 - y2)
area (Triangulo (Cartesiano x1 y1) (Cartesiano x2 y2) (Cartesiano x3 y3)) = sqrt (s*(s-a)*(s-b)*(s-c)) -- fórmula de Heron
    where
        a = distP (Cartesiano x1 y1) (Cartesiano x2 y2) 
        b = distP (Cartesiano x2 y2) (Cartesiano x3 y3)
        c = distP (Cartesiano x3 y3) (Cartesiano x1 y1)
        s = (a+b+c) / 2 --semi-perimetro

-- 7 d)

perimetro2 :: Figura -> Double
perimetro2 (Circulo _ r) = 2*pi*r
perimetro2 (Retangulo (Cartesiano x1 y1) (Cartesiano x2 y2)) = 2 * (abs(x1-x2) + abs(y1-y2))
perimetro2 (Triangulo (Cartesiano x1 y1)(Cartesiano x2 y2)(Cartesiano x3 y3)) = (distP (Cartesiano x1 y1) (Cartesiano x2 y2)) + (distP (Cartesiano x2 y2) (Cartesiano x3 y3) ) + (distP(Cartesiano x1 y1) (Cartesiano x3 y3))

-- exercício 8

{-
=========================TABELA DE ASCII=============================
https://hackage.haskell.org/package/base-4.14.0.0/docs/Data-Char.html
=====================================================================
-}

-- 8 a)

isLower' :: Char -> Bool 
isLower' x = elem(ord x) [97..122]

-- 8 b)

isDigit' :: Char -> Bool
isDigit' x = elem(ord x) [48..57]

-- 8 c)

isAlpha' :: Char -> Bool
isAlpha' x = elem(ord x) [97..122] || elem(ord x) [65..90]

-- 8 d)

toUpper' :: Char -> Char
toUpper' x = chr((ord x) - 32)

-- 8 e)

intToDigit' :: Int -> Char
intToDigit' x = chr(x + 48)

-- 8 f)

digitToInt' :: Char -> Int
digitToInt' x = ord(x) - 48