module PF1718_Exame where

import Data.List

-- exercício 1

getFromIndex' :: [a] -> Int -> a
getFromIndex' (x:xs) n
    | n == 0 = x
    | otherwise = getFromIndex' xs (n-1)

-- exercício 2

data Movimento = Norte | Sul | Este | Oeste deriving Show

posicao :: (Int,Int) -> [Movimento] -> (Int,Int)
posicao (x,y) [] = (x,y)
posicao (x,y) (m:ms) = posicao (case m of Norte -> (x,y+1)
                                          Sul -> (x,y-1)
                                          Este -> (x+1,y)
                                          Oeste -> (x-1,y) ) ms

-- exercício 3

any' :: (a -> Bool) -> [a] -> Bool
any' f = foldl (\acc x -> if f x then True else acc) False

-- exercício 4

type Mat a = [[a]]

triSup :: (Num a,Eq a) => Mat a -> Bool
triSup [] = False
triSup matriz = all (\n -> all ((==) 0 . (!!) (matriz !! n)) [0..(n - 1)]) [1..(length matriz - 1)]

-- exercício 5

movimenta :: IO (Int,Int)
movimenta = move (0,0)

move :: (Int,Int) -> IO (Int,Int)
move (x,y) = do
            dir <- getChar
            case dir of 'n' -> move (x,y+1)
                        's' -> move (x,y-1)
                        'e' -> move (x+1,y)
                        'o' -> move (x-1,y)
                        'w' -> move (x-1,y)
                        'N' -> move (x,y+1)
                        'S' -> move (x,y-1)
                        'E' -> move (x+1,y)
                        'O' -> move (x-1,y)
                        'W' -> move (x-1,y)
                        otherwise -> return (x,y) 

-- exercício 6

data Imagem = Quadrado Int
            | Mover (Int,Int) Imagem
            | Juntar [Imagem]

-- 6 a)

vazia :: Imagem -> Bool
vazia (Quadrado _) = False
vazia (Mover _ img) = vazia img
vazia (Juntar imgs) 
    | null imgs = True
    | otherwise = or (map vazia imgs)

-- 6 b)

maior :: Imagem -> Maybe Int
maior (Quadrado n) = Just n
maior (Mover _ img) = maior img
maior (Juntar imgs) 
    | null imgs = Nothing
    | otherwise = maximum' (filter (/= Nothing) (map maior imgs))
        where 
            maximum' [] = Nothing
            maximum' l = maximum l

-- 6 c)

instance Eq Imagem where
    img1 == img2 = null $ (quadPos img1 (0,0)) \\ (quadPos img2 (0,0)) 

quadPos :: Imagem -> (Int,Int) -> [(Int,(Int,Int))]
quadPos (Quadrado n) pos = [(n,pos)]
quadPos (Mover (a,b) img) (x,y) = quadPos img (x+a,y+b)
quadPos (Juntar imgs) pos = concatMap (\x -> quadPos x (pos)) imgs
