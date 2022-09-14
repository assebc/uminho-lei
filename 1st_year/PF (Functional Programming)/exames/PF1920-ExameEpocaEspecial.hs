module PF1920_ExameEpocaEspecial where

-- exercício 1

-- 1 a)

subst :: Eq a => (a,a) -> [a] -> [a]
subst (x,y) [] = []
subst (x,y) (a:as) 
    | a == x = y : subst (x,y) as
    | otherwise = a : subst (x,y) as

-- 1 b)

posicoes :: [a] -> [Int] -> [a]
posicoes [] _  = []
posicoes l []  = [] 
posicoes l (x:xs) = position x l : posicoes  l xs 
    where
        position :: Int -> [a] -> a
        position p (x:xs)
            | p == 1 = x
            | otherwise = position (p-1) xs

-- exercício 2

data Tree a b = Leaf b | Node a (Tree a b) (Tree a b)

-- 2 a)

folhas :: Tree a b -> [b]
folhas (Leaf b) = [b]
folhas (Node a e d) = folhas e ++ folhas d 

-- 2 b)

somas :: Tree Float Int -> (Float,Int)
somas l = (sum (somaB l) , sum (folhas l))
    where
        somaB :: Tree a b -> [a] 
        somaB (Leaf x) = []
        somaB (Node m (a) (b)) =  [m] ++ (somaB  a) ++ (somaB  b)

-- exercício 3

type Mat a = [[a]]

rotateLeft :: Mat a -> Mat a
rotateLeft [] = []
rotateLeft m = (rotateLeft (map tail m)) ++ [map head m]

-- exercício 4

type Filme = (Titulo,Realizador,[Actor],Genero,Ano)
type Titulo = String
type Realizador = String
type Actor = String
type Ano = Int
data Genero = Comedia | Drama | Ficcao | Accao | Animacao | Documentario deriving Eq
type Filmes = [Filme]

-- 4 a)

doRealizador :: Filmes -> Realizador -> [Titulo]
doRealizador [] _ = []
doRealizador ((t,r,as,gen,ano):fs) p
    | p == r = t : doRealizador fs p
    | otherwise = doRealizador fs p

-- 4 b)

doActor :: Filmes -> Actor -> [Titulo]
doActor [] _ = []
doActor _ [] = []
doActor ((t,r,act,gen,ano):fs) a
    | elem a act = t : doActor fs a
    | otherwise = doActor fs a

-- 4 c)

consulta :: Filmes -> Genero -> Realizador -> [(Ano, Titulo)]
consulta bd gen rea = map aux (filter (teste gen rea) bd)
    where 
        teste :: Genero -> Realizador -> Filme -> Bool
        teste g r (_,x,_,y,_) = g == y && r == x
        aux :: Filme -> (Ano, Titulo)
        aux (x,_,_,_,y) = (y, x)

-- exercício 5

data Avaliacao = NaoVi | Ponto Int -- pontuação entre 1 e 5
type FilmesAval = [(Filme,[Avaliacao])]

getGen :: Filme -> Genero
getGen (_,_,_,gen,_) = gen

getTit :: Filme -> Titulo
getTit (tit,_,_,_,_) = tit
