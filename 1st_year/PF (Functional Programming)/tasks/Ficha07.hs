module Ficha07 where

-- exercício 1

data ExpInt = Const Int
            | Simetrico ExpInt
            | Mais ExpInt ExpInt
            | Menos ExpInt ExpInt
            | Mult ExpInt ExpInt

-- 1 a)

calcula :: ExpInt -> Int
calcula (Const num) = num
calcula (Simetrico exp) = (- calcula exp)
calcula (Mais a b) = calcula a + calcula b
calcula (Menos a b) = calcula a - calcula b
calcula (Mult a b) = calcula a * calcula b

-- 1 b)

infixa :: ExpInt -> String
infixa (Const num) = show num
infixa (Simetrico exp) = "(-" ++ infixa exp ++ ")"
infixa (Mais a b) = '(':infixa a ++ "+" ++ infixa b ++ ")"
infixa (Menos a b) = '(':infixa a ++ "-" ++ infixa b ++ ")"
infixa (Mult a b) = '(':infixa a ++ "*" ++ infixa b ++ ")"

-- 1 c)

posfixa :: ExpInt -> String
posfixa (Const num) = show num ++ " "
posfixa (Simetrico exp) = '-':posfixa exp
posfixa (Mais a b) = posfixa a ++ posfixa b ++ "+ "
posfixa (Menos a b) = posfixa a ++ posfixa b ++ "- "
posfixa (Mult a b) = posfixa a ++ posfixa b ++ "* "

-- exercicio 2

data RTree a = R a [RTree a] deriving Show

-- 2 a)

soma :: Num a => RTree a -> a
soma (R e []) = e
soma (R e es) = e + sum (map (soma) es)

-- 2 b)

altura :: RTree a -> Int
altura (R e []) = 1
altura (R e es) = 1 + maximum (map altura es)

-- 2 c)

prune :: Int -> RTree a -> RTree a
prune 0 (R e es) = R e []
prune n (R e es) = R e (map (prune (n - 1)) es)

-- 2 d)

mirror :: RTree a -> RTree a
mirror (R e es) = R e (map mirror (reverse es))

-- 2 e)

postorder :: RTree a -> [a]
postorder (R e []) = [e]
postorder (R e es) = concatMap postorder es ++ [e]

-- exercicio 3

data LTree a = Tip a | Fork (LTree a) (LTree a) deriving Show

-- 3 a)

ltSum :: Num a => LTree a -> a
ltSum (Tip n) = n
ltSum (Fork a b) = ltSum a + ltSum b 

-- 3 b)

listaLT :: LTree a -> [a]
listaLT (Tip n) = [n]
listaLT (Fork a b) = listaLT a ++ listaLT b

-- 3 c)

ltHeight :: LTree a -> Int
ltHeight (Tip _) = 0
ltHeight (Fork a b) = 1 + max (ltHeight a) (ltHeight b)

-- exercicio 4

data BTree a = Empty | Node a (BTree a) (BTree a) deriving Show
data FTree a b = Leaf b | No a (FTree a b) (FTree a b) deriving Show

-- 4 a)

splitFTree :: FTree a b -> (BTree a, LTree b)
splitFTree (Leaf n) = (Empty, Tip n)
splitFTree (No a b c) = (Node a (fst (splitFTree b)) (fst (splitFTree c)), Fork (snd (splitFTree b)) (snd (splitFTree c)))

-- 4 b)

joinTrees :: BTree a -> LTree b -> Maybe (FTree a b)
joinTrees (Empty) (Tip n) = Just (Leaf n)
joinTrees (Node e l r) (Fork a b) = Just (No e aux aux2)
    where 
        Just aux = joinTrees l a
        Just aux2 = joinTrees r b
joinTrees _ _ = Nothing