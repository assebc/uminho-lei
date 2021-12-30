module PF2021_Teste where

-- exercicio 1
deletes :: Eq a => a -> [a] -> [a]
deletes x [] = []
deletes x (y:ys) 
    | x == y = ys
    | otherwise = y : deletes x ys

remove1 :: Eq a => [a] -> [a] -> [a]
remove1 l [] = l
remove1 [] _ = []
remove1 l (x:xs) = remove1 (deletes x l) xs

-- exercicio 2 a)

type MSet a = [(a,Int)]

removeMSet :: Eq a => a -> MSet a -> MSet a
removeMSet _ [] = []
removeMSet x ((a,n):xs)
    | x == a && n == 1 = xs
    | x == a = (a,n-1):xs
    | otherwise = (a,n) : removeMSet x xs

-- exercicio 2 b)

concats :: [a] -> a -> [a]
concats [] a = [a]
concats l@(x:xs) a = x : concats xs a

calcula :: MSet a -> ([a],Int)
calcula l = foldl(\(l,y) x -> (concats l (fst x),y+snd x) ) ([],0) l

-- exercicio 3

partes :: String -> Char -> [String]
partes string delim = foldl f [] string
  where f (h:t) char | char == delim = undefined
                     | otherwise = undefined

-- exercicio 4 a)

data BTree a = Empty | Node a (BTree a) (BTree a)

a1 =  Node 5 (Node 3 Empty Empty) (Node 7 Empty (Node 9 Empty Empty))

remove2 :: Ord a => a -> BTree a -> BTree a
remove2 x Empty = Empty
remove2 x b@(Node e l r) 
    | x < e = Node e (remove2 x l) r
    | x > e = Node e l (remove2 x r)
    | otherwise = l

-- exercicio 4 b)

instance Show (BTree a) where
    show Empty = "*"
    show (Node a l r) = "("++(show l)++" <-"++"a"++"-> "++(show r)++")"
        