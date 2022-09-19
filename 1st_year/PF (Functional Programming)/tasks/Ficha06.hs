module Ficha06 where


-- exercício 1

data BTree a = Empty
             | Node a (BTree a) (BTree a)
             deriving Show

-- 1 a)

altura :: BTree a -> Int
altura Empty = 0
altura (Node a l r) = max (1 + altura l) (1 + altura r)

-- 1 b)

contaNodos :: BTree a -> Int
contaNodos Empty = 0
contaNodos (Node a l r) = 1 + contaNodos l + contaNodos r

-- 1 c)

folhas :: BTree a -> Int
folhas Empty = 0
folhas (Node a Empty Empty) = 1
folhas (Node a l r) = folhas l + folhas r

-- 1 d)

prune :: Int -> BTree a -> BTree a
prune _ Empty = Empty
prune 0 _ = Empty
prune n (Node a l r) = Node a (prune (n-1) l ) (prune (n-1) r)

-- 1 e)

path :: [Bool] -> BTree a -> [a]
path _ Empty = []
path [] (Node a l r) = [a]
path (x:xs) (Node e l r) = e : path xs (if x then r else l)  

-- 1 f)

mirror :: BTree a -> BTree a
mirror Empty = Empty
mirror (Node e l r) = Node e (mirror r) (mirror l)

-- 1 g)

zipWithBT :: (a -> b -> c) -> BTree a -> BTree b -> BTree c
zipWithBT f (Node e l r) (Node a b c) = Node (f e a) (zipWithBT f l b) (zipWithBT f r c)
zipWithBT _ _ _ = Empty


-- 1 h)

unzipBT :: BTree (a,b,c) -> (BTree a,BTree b,BTree c)
unzipBT Empty = (Empty, Empty, Empty)
unzipBT (Node (a,b,c) l r) = (Node a unzipL1 unzipR1,Node b unzipL2 unzipR2,Node c unzipL3 unzipR3)
    where 
        (unzipL1,unzipL2,unzipL3) = unzipBT l
        (unzipR1,unzipR2,unzipR3) = unzipBT r

-- exercício 2

-- 2 a)

minimo :: (Ord a) => BTree a -> a
minimo (Node e Empty _) = e
minimo (Node e l r) = minimo l

-- 2 b)

semMinimo :: Ord a => BTree a -> BTree a
semMinimo (Node _ Empty _) = Empty
semMinimo (Node e l r) = Node e (semMinimo l) r

-- 2 c)

minSmin :: Ord a => BTree a -> (a,BTree a)
minSmin (Node e Empty _) = (e,Empty)
minSmin (Node e l r) = (a,Node e b r)
    where 
        (a,b) = minSmin l

-- 2 d)

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

-- Exercicio 3

type Aluno = (Numero,Nome,Regime,Classificacao)
type Numero = Int
type Nome = String
data Regime = ORD | TE | MEL  deriving Show
data Classificacao = Aprov Int | Rep | Faltou deriving Show
type Turma = BTree Aluno  --  árvore binária de procura (ordenada por número)

-- 3 a)

inscNum :: Numero -> Turma -> Bool
inscNum _ Empty = False
inscNum n (Node (num,_,_,_) l r) = n == num || inscNum n (if n < num then l else r)

-- 3 b)

inscNome :: Nome -> Turma -> Bool
inscNome _ Empty = False
inscNome n (Node (_,nom,_,_) l r) = n == nom || inscNome n l || inscNome n r

-- 3 c)

trabEst :: Turma -> [(Numero,Nome)]
trabEst Empty = []
trabEst (Node (num,nom,reg,_) l r) = (case reg of TE -> [(num,nom)];otherwise -> []) ++ trabEst l ++ trabEst r

-- 3 d)

nota :: Numero -> Turma -> Maybe Classificacao
nota n (Node (num,_,_,clas) l r) 
    | n == num = Just clas
    | n < num = nota n l
    | otherwise = nota n r
nota _ _ = Nothing

-- 3 e)

percFaltas :: Turma -> Float
percFaltas Empty = 0
percFaltas turma = sumFaltas turma / numAlunos turma * 100
    where 
        sumFaltas Empty = 0
        sumFaltas (Node (_,_,_,clas) l r) = (case clas of Faltou -> 1;otherwise -> 0) + sumFaltas l + sumFaltas r
        numAlunos Empty = 0
        numAlunos (Node e l r) = 1 + numAlunos l + numAlunos r

-- 3 f)

mediaAprov :: Turma -> Float
mediaAprov Empty = 0
mediaAprov turma = sumNotas turma / numNotas turma
    where 
        sumNotas :: Turma -> Float
        sumNotas Empty = 0
        sumNotas (Node (_,_,_,Aprov nota) l r) = fromIntegral nota + sumNotas l + sumNotas r
        sumNotas (Node e l r) = sumNotas l + sumNotas r
        numNotas :: Turma -> Float
        numNotas (Node (_,_,_,clas) l r) = (case clas of Aprov nota -> 1;otherwise -> 0) + numNotas l + numNotas r
        numNotas _ = 0

-- 3 g)

aprovAv :: Turma -> Float
aprovAv Empty = 0
aprovAv turma = a / b
    where 
        (a,b) = aux turma
        aux Empty = (0,0)
        aux (Node (_,_,_,clas) l r) = case clas of Aprov nota -> (x+1,y) ; Rep -> (x,y+1) ; otherwise -> (x,y)
            where 
                (x,y) = (c+e,d+f)
                (c,d) = aux l
                (e,f) = aux r