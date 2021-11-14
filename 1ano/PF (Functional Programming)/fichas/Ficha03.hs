module Ficha03 where

import Ficha01

-- exercício 1

type Etapa = (Hour,Hour)
type Viagem = [Etapa]

-- 1 a)

testEtapa :: Etapa -> Bool
testEtapa (H h m, H h1 m1) = h < h1 || h == h1 && m < m1

-- 1 b)

testViagem :: Viagem -> Bool
testViagem [] = False
testViagem (e:es) = testEtapa e && testViagem es

-- 1 c)

calcViagem :: Viagem -> Etapa
calcViagem [] = (H 0 0,H 0 0)
calcViagem v = (fst(head v),snd(last v))

-- 1 d)

calctime :: Viagem -> Int
calctime [] = 0
calctime (e:es) = diffHours (fst e) (snd e) + calctime es
        
-- 1 e)

calcwaitime :: Viagem -> Int
calcwaitime [] = 0
calcwaitime [e] = 0
calcwaitime ((h1,h2):(h3,h4):es) = diffHours h2 h3 + (calcwaitime ((h3,h4):es))

-- 1 f)

calcViagemT :: Viagem -> Int
calcViagemT [] = 0
calcViagemT [v] = calctime [v]
calcViagemT v = calctime v + calcwaitime v

-- exercício 2

type Poligonal = [Ponto]

-- 2 a)

distPoligonal :: Poligonal -> Double
distPoligonal [] = 0
distPoligonal [(Polar x y)] = 0
distPoligonal [(Cartesiano x y)] = 0
distPoligonal (p:p1:ps) = distP p p1 + distPoligonal (p1:ps)

-- 2 b)

closeLine :: Poligonal -> Bool
closeLine [] = False
closeLine [(Cartesiano x y)] = False
closeLine [(Polar x y)] = False
closeLine p = head p == last p

-- 2 c)

triangula :: Poligonal -> [Figura]
triangula [p,p1,p2] = [(Triangulo p p1 p2)]
triangula (p:p1:p2:ps) = (Triangulo p p1 p2):triangula (p:p2:ps)

-- 2 d)

areaPoligonal :: Poligonal -> Double
areaPoligonal p = sum (map (\fig -> area fig) (triangula p))

-- 2 e)

mover :: Poligonal -> Ponto -> Poligonal
mover pol p = p:pol

-- 2 f)

zoom :: Double -> Poligonal -> Poligonal
zoom z [p1@(Cartesiano x y),p2@(Cartesiano a b)] = p1:(Cartesiano (z*a) (z*b)):[]
zoom z (p1@(Cartesiano x y):p2@(Cartesiano a b):pol) = p1:zoom z (p3:pol)
    where 
        p3 = (Cartesiano (z*a) (z*b))

-- exercício 3

data Contacto = Casa Integer
              | Trab Integer
              | Tlm Integer
              | Email String
              deriving Show

type Nome = String
type Agenda = [(Nome, [Contacto])]

-- 3 a)

acrescEmail :: Nome -> String -> Agenda -> Agenda
acrescEmail nome email agenda = agenda ++ [(nome, [Email email])]

-- 3 b)

verEmails :: Nome -> Agenda -> Maybe [String]
verEmails nome agenda@[(n,c)] = if nome == n 
                                then Just (map (\x -> case x of Email e -> e) c)
                                else Nothing
verEmails nome ((n,c):agenda) = if nome == n
                                then verEmails nome [(n,c)]
                                else verEmails nome agenda

-- 3 c)

consTelefs :: [Contacto] -> [Integer]
consTelefs [] = []
consTelefs (c:cs) = case c of Casa c -> c : consTelefs cs
                              Trab c -> c : consTelefs cs
                              Tlm c -> c : consTelefs cs
                              otherwise -> consTelefs cs

-- 3 d)

casa :: Nome -> Agenda -> Maybe Integer
casa nome [(n,(c:cs))] = if nome == n
                         then case c of Casa x -> Just x
                                        otherwise -> casa nome [(n,cs)]
                         else Nothing
casa nome ((n,c):agenda) = if nome == nome
                           then casa nome [(n,c)]
                           else casa nome agenda

-- exercício 4

type Dia = Int
type Mes = Int
type Ano = Int

data Data = D Dia Mes Ano deriving Show

type TabDN = [(Nome,Data)]

-- 4 a)

procura :: Nome -> TabDN -> Maybe Data
procura nome [] = Nothing
procura nome ((n,d):t) = if nome == n
                         then Just d
                         else procura nome t

-- 4 b)

idade :: Data -> Nome -> TabDN -> Maybe Int
idade date@(D dx mx ax) nome ((n,D d m a):ts) = if nome == n 
                                                  then if mx > m || mx == m && dx > d 
                                                       then Just (ax - a) 
                                                       else Just ((ax - a) - 1) 
                                                  else idade date nome ts

-- 4 c)

anterior :: Data -> Data -> Bool
anterior (D d m a) (D dx mx ax) = a < ax || (a == ax && m < mx) || (a == ax && m == mx && d < dx)

-- 4 d)

ordena :: TabDN -> TabDN
ordena [] = []
ordena ((n,d):ts) = insert (n,d) (ordena ts)
    where 
        insert (n,d) [] = [(n,d)]
        insert (n,d) ((nx,dx):t) 
            | anterior dx d = (nx,dx):insert (n,d) t
            | otherwise = (n,d):(nx,dx):t

--4 e)

porIdade :: Data -> TabDN -> [(Nome,Int)]
porIdade _ [] = []
porIdade (D d m a) tabela = (n,idade) : porIdade (D d m a) ts
    where 
        ((n,D dx mx ax):ts) = ordena tabela
        idade = if m > mx || (mx == m && d > dx) 
                then (a - ax) 
                else ((a - ax) - 1)

-- exercício 5 

data Movimento = Credito Float | Debito Float deriving Show
data Extracto = Ext Float [(Data,String,Movimento)] deriving Show

-- 5 a)

extValor :: Extracto -> Float -> [Movimento]
extValor (Ext x []) _ = []
extValor (Ext x ((_,_,mov):ls)) valor = case mov of Credito n -> if n >= valor 
                                                                 then mov : extValor (Ext x ls) valor 
                                                                 else extValor (Ext x ls) valor
                                                    Debito n -> if n >= valor 
                                                                then mov : extValor (Ext x ls) valor 
                                                                else extValor (Ext x ls) valor

-- 5 b)

filtro :: Extracto -> [String] -> [(Data,Movimento)]
filtro (Ext x []) _ = []
filtro (Ext x ((dat,desc,mov):ls)) l = if elem desc l 
                                       then (dat,mov) : filtro (Ext x ls) l 
                                       else filtro (Ext x ls) l

-- 5 c)

creDeb :: Extracto -> (Float,Float)
creDeb (Ext x lm) = foldl (\(c,d) (_,_,mov) -> case mov of Credito x -> (c + x, d)
                                                           Debito x -> (c, d + x)) (0,0) lm

-- 5 d)

saldo :: Extracto -> Float
saldo (Ext x lm) = foldl (\acc (_,_,mov) -> case mov of Credito n -> (acc + n)
                                                        Debito n -> (acc - n)) x lm