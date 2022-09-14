module PF1617_Exame where



-- exercício 1

-- 1 a)

unline :: [String] -> String
unline [] = []
unline (x:xs) = x ++ "\n" ++ unline xs

-- 1 b)

remove :: Eq a => [a] -> [a] -> [a]
remove [] _ = []
remove l [] = l
remove (x:xs) l = remove (delete' x l) xs
    where
        delete' :: Eq a => a -> [a] -> [a]
        delete' _ [] = []
        delete' a (x:xs)
            | a == x = xs
            | otherwise = x : delete' a xs 

-- exercício 2

data Seq a = Nil | Inicio a (Seq a) | Fim (Seq a) a

-- 2 a)

primeiro :: Seq a -> a
primeiro (Inicio a s) = a
primeiro (Fim Nil a) = a
primeiro (Fim a s) = primeiro a

-- 2 b)

semUltimo :: Seq a -> Seq a
semUltimo (Inicio a Nil) = Nil
semUltimo (Inicio a s) = Inicio a (semUltimo s)
semUltimo (Fim s a) = s

-- exercício 3

data BTree a = Empty | Node a (BTree a) (BTree a)

-- 3 a)

prune :: Int -> BTree a -> BTree a
prune _ Empty = Empty
prune 0 _ = Empty
prune n (Node a l r) = (Node a (prune (n - 1) l) (prune (n - 1) r) )

-- 3 b)

semMinimo :: Ord a => BTree a -> BTree a
semMinimo Empty = Empty
semMinimo (Node a Empty r) = r
semMinimo (Node a l r) = (Node a (semMinimo l) r)

-- exercício 4

type Tabuleiro = [String]

-- 4 a)

posicoes :: Tabuleiro -> [(Int,Int)]
posicoes tab = foldl (\acc y -> acc ++ (foldl (\acc2 x -> if (tab !! y) !! x == 'R' then acc2 ++ [(x,y)] else acc2)) [] [0..(length (head tab) - 1)]) [] [0..(length tab - 1)]

-- 4 b)

valido :: Tabuleiro -> Bool
valido tab = foldl (\acc (x,y) -> if length (filter (\(a,b) -> (a,b) /= (x,y) && (a == x || b == y || a - b == x - y || b - a == y - x)) (posicoes tab)) > 0 then False else acc) True (posicoes tab)

-- 4 c)

bemFormado ::  Int -> Tabuleiro -> Bool
bemFormado n tab = length tab == n && foldr (\x -> (&&) $ (==) n $ length x) True tab && foldl (\acc (x,y) -> if (tab !! y) !! x == 'R' then acc + 1 else acc) 0 [(a,b) | a <- [0..n - 1], b <- [0..n - 1]] == n