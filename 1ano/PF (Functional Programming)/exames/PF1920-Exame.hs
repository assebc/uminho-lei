module PF1920_Exame where

import Data.List
import System.Random

myinits :: [a] -> [[a]]
myinits [] = []
myinits l = myinits (init l) ++ [l]

myisPrefixOf :: Eq a => [a] -> [a] -> Bool
myisPrefixOf [] _ = True
myisPrefixOf _ [] = False
myisPrefixOf l ls = elem l (myinits ls)

data BTree a = Empty | Node a (BTree a) (BTree a) deriving Show


folhas :: BTree a -> Int
folhas Empty = 0 
folhas (Node a l r) = 1 + folhas l + folhas r

path :: [Bool] -> BTree a -> [a]
path _ Empty = []
path [] (Node a l r) = [a]
path (x:xs) (Node a l r) = case x of True -> a : path xs l
                                     False -> a : path xs r

type Coeficiente = Float
type Polinomio = [Coeficiente]

valor :: Polinomio -> Float -> Float
valor ps x = foldl(\acc p -> (p * x)^(just $ Data.List.elemIndex p ps) + acc) 0 ps

shiftLeft :: [a] -> [a]
shiftLeft [] = []
shiftLeft (x:xs) = xs

just :: Maybe a -> a 
just (Just a) = a

percent :: Int -> Int -> Float
percent x y =   100 * ( a / b )
  where a = fromIntegral x :: Float
        b = fromIntegral y :: Float

deriv :: Polinomio -> Polinomio
deriv ps = shiftLeft (foldl(\acc p -> acc ++ [p * percent (just $ Data.List.elemIndex p ps) 100] ) [] ps)

soma :: Polinomio -> Polinomio -> Polinomio
soma l@(x:xs) ls@(y:ys) = zipWith (+) l ls

type Mat a = [[a]]

nothere :: Eq a => [a] -> [a] -> [a]
nothere [] _ = []
nothere l [] = l
nothere l@(x:xs) (y:ys) = if (x==y) then nothere xs ys else l

quebraLinha :: Eq a => [Int] -> [a] -> Mat a
quebraLinha [] l = [l]
quebraLinha _ [] = []
quebraLinha [x] l = [take x l]
quebraLinha (x:xs) l = take x l : quebraLinha xs rest
    where
        rest = nothere l (take x l)

-- aux
rotateL :: Mat a -> Mat a 
rotateL = reverse . transpose

quebraCol :: Eq a => [Int] -> Mat a -> [Mat a]
quebraCol [] l = [l]
quebraCol _ [] = []
quebraCol l mat@(x:xs) = quebraLinha l y : quebraCol l ys
    where
        y = head (rotateL mat)
        ys = tail (rotateL mat)

quebraCols :: Eq a => [Int] -> [Mat a] -> [Mat a]
quebraCols l [] = []
quebraCols l (x:xs) = quebraCol l x ++ quebraCols l xs

quebraLinhav2 :: Eq a => [Int] -> Mat a -> [Mat a]
quebraLinhav2 l (x:xs) = quebraLinha l x : quebraLinhav2 l xs

-- to do
fragmenta :: Eq a => [Int] -> [Int] -> Mat a -> [Mat a]
fragmenta [] [] [] = []


--geraMat :: (Int,Int) -> (Int,Int) -> IO (Mat Int)
--geraMat (x,y) (a,b) = do
--                      r <- randomRIO(a,b)
--                      list <- replicate x r
--                      mat <- replicate y list
--                      return mat
                                       
                       
 