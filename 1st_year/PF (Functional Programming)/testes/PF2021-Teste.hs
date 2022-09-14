module PF2021_Exame where

import Data.List

deletes :: Eq a => a -> [a] -> [a]
deletes n [] = []
deletes n (x:xs)
    | n == x = xs
    | otherwise = x : deletes n xs

removes :: Eq a => [a] -> [a] -> [a]
removes l [] = l 
removes [] _ = []
removes l (y:ys) = removes (deletes y l) ys

type MSet a = [(a,Int)]

removeMSet :: Eq a => a -> [(a,Int)] -> [(a,Int)]
removeMSet _ [] = []
removeMSet x ((a,n):xs)
    | x == a && n > 1 = (a,n-1) : xs
    | x == a = xs
    | otherwise = (a,n) : removeMSet x xs

concats :: [a] -> a -> [a]
concats [] a = [a]
concats l@(x:xs) a = x : concats xs a

calcula :: MSet a -> ([a],Int)
calcula ms = foldl(\(l,n) m -> (concats l (fst m), n + (snd m)) ) ([],0) ms                  

partes :: String -> Char -> [String]
partes string delim = let 
                        repl ';' = ' '
                        repl c = c
                      in words (map repl string)

data BTree a = Empty | Node a (BTree a) (BTree a)

a1 =  Node 5 (Node 3 Empty Empty) (Node 7 Empty (Node 9 Empty Empty))

minSmin :: Ord a => BTree a -> (a,BTree a)
minSmin (Node e Empty _) = (e,Empty)
minSmin (Node e l r) = (a,Node e b r)
    where 
        (a,b) = minSmin l


remove :: Ord a => a -> BTree a -> BTree a
remove _ Empty = Empty
remove x (Node e l r) 
    | x < e = Node e (remove x l) r
    | x > e = Node e l (remove x r)
    | otherwise = aux x (Node e l r)
        where
            (g,h) = minSmin r
            aux n (Node a b c) = case b of Empty -> c
                                           otherwise -> case c of Empty -> b
                                                                  otherwise -> Node g b h

instance Show a => Show (BTree a) where
    show Empty = "*"
    show (Node a l r) = "(" ++ (show l) ++ " <-" ++ show a ++ "-> " ++ (show r) ++ ")"

type Nome = String
data FileSystem = File Nome | Dir Nome [FileSystem]

fs1 = Dir "usr" [Dir "xxx" [File "abc.txt", File "readme", Dir "PF" [File "exemplo.hs"]], Dir "yyy" [], Dir "zzz" [Dir "tmp" [], File "teste.c"] ]

fichs :: FileSystem -> [Nome]
fichs (File n) = [n]
fichs (Dir n l) = foldl(\acc f -> acc ++ fichs f) [] l

firstJust :: Maybe a -> Maybe a -> Maybe a
firstJust mb@(Just _) _ = mb
firstJust _ mb' = mb'

isFile :: FileSystem -> Bool
isFile (File _) = True
isFile _ = False

getNome :: FileSystem -> Nome
getNome (File n) = n
getNome (Dir n _) = n

dirFiles :: FileSystem -> [Nome] -> Maybe [Nome]
dirFiles (Dir n fs) [p] 
    | n == p = Just $ map getNome $ filter isFile fs
dirFiles (Dir n fs) (p:ps)
    | n == p = foldr (\v acc -> firstJust acc (dirFiles v ps)) Nothing fs
dirFiles _ _ = Nothing
