module Resol4 where

import Cp
import Nat
import Svg
import Probability
import LTree

type Team = String
type Group = [Team]
type Match = (Team,Team)

-- Data of exercise 4

groups::[Group]
groups = [["Qatar","Ecuador","Senegal","Netherlands"],
          ["England","Iran","USA","Wales"],
          ["Argentina","Saudi Arabia","Mexico","Poland"],
          ["France","Denmark","Tunisia","Australia"],
          ["Spain","Germany","Japan","Costa Rica"],
          ["Belgium","Canada","Morocco","Croatia"],
          ["Brazil","Serbia","Switzerland","Cameroon"],
          ["Portugal","Ghana","Uruguay","Korea Republic"]]


rankings = [
    ("Argentina",4.8),
    ("Australia",4.0),
    ("Belgium",5.0),
    ("Brazil",5.0),
    ("Cameroon",4.0),
    ("Canada",4.0),
    ("Costa Rica",4.1),
    ("Croatia",4.4),
    ("Denmark",4.5),
    ("Ecuador",4.0),
    ("England",4.7),
    ("France",4.8),
    ("Germany",4.5),
    ("Ghana",3.8),
    ("Iran",4.2),
    ("Japan",4.2),
    ("Korea Republic",4.2),
    ("Mexico",4.5),
    ("Morocco",4.2),
    ("Netherlands",4.6),
    ("Poland",4.2),
    ("Portugal",4.6),
    ("Qatar",3.9),
    ("Saudi Arabia",3.9),
    ("Senegal",4.3),
    ("Serbia",4.2),
    ("Spain",4.7),
    ("Switzerland",4.4),
    ("Tunisia",4.1),
    ("USA",4.4),
    ("Uruguay",4.5),
    ("Wales",4.3)]


-- Resolution of exercise 4

-- points for group phase
win = 3 
draw = 1
lose = 0

-- Each team rank
rank x = 4 ∗∗ (pap rankings x−3.8)

-- Generate group phase games
generateMatches = pairup

pairup :: Eq b => [b] -> [(b,b)]

-- Disqualification phase tree
arrangement = (>>=swapTeams) . chunksOf 4 
    where
        swapTeams [[a1,a2],[b1,b2],[c1,c2],[d1,d2]] = [a1,b2,c1,d2,b1,a2,d1,c2]


-- Not probabilistic version

-- Winner of not probabilistic simulation
winner::Team
winner = wcup groups 

wcup = knockoutStage . groupStage 
    where
        knockoutStage = cata . either id koCriteria

groupStage ::[Group] → LTree Team
groupStage = initKnockoutStage · simulateGroupStage · genGroupStageMatches
    where
        initKnockoutStage = cata (glt) . arrangement
        glt = undefined
        arrangement = undefined

genGroupStageMatches::[Group] → [[Match]]
genGroupStageMatches = map generateMatches

simulateGroupStage ::[[Match]] → [[Team]]
simulateGroupStage = map (groupWinners gsCriteria)
    where
        groupWinners criteria = best 2 . consolidate' .(>>=matchResult criteria)

consolidate'::(Eq a,Num b) ⇒ [(a,b)] → [(a,b)]
consolidate' = cata (cgene)
    where
        cgene = undifined

matchResult :: (Match -> Maybe Team) -> Match -> [(Team,Int)]

-- Criteria for the not probabilistic simulation of the group phase games
gsCriteria :: Match -> (Maybe Team)
gsCriteria = s . split(id >< id,rank >< rank) 
    where
        s ((s1,s2),(r1,r2)) = let d = r1 − r2 in
            if d > 0.5 then Just s1
            else if d <− 0.5 then Just s2
            else Nothing

-- Criteria for the not probabilistic simulation of disqualification phase 
koCriteria = s . split (id >< id,rank >< rank)
    where
        s ((s1,s2),(r1,r2)) = let d = r1 − r2 in
            if d == 0 then s1
            else if d >0 then s1 else s2

-- Probabilistic version

pwinner::Dist Team
pwinner = pwcup groups

pwcup = pknockoutStage .! pgroupStage

pknockoutStage = mcataLTree' [return,pkoCriteria]
mcataLTree0 g = k 
    where
        k (Leaf a) = g1 a
        k (Fork (x, y)) = mmbin g2 (k x, k y)
        g1 = g . i1
        g2 = g . i2

pgroupStage = pinitKnockoutStage .! psimulateGroupStage . genGroupStageMatches

-- Otimized pwinner version
pwinner2::Dist Team
pwinner2 = mbin f x>>=pknockoutStage 
    where
        f (x, y) = initKnockoutStage (x++y)
        x = split(hg . take 4,g . drop 4) groups
        g = psimulateGroupStage . genGroupStageMatche

-- Criteria for the probabilistic simulation of the group phase games
pgsCriteria :: Match -> Dist (Maybe Team)
pgsCriteria = s . split(id >< id,rank >< rank)
    where
        s ((s1,s2),(r1,r2)) = if abs (r1 −r2)>0.5 
                              then fmap Just (pkoCriteria (s1,s2)) 
                              else f (s1,s2)


-- Probabilistic version of group phase simultation
psimulateGroupStage = trim . map(pgroupWinners pgsCriteria)
trim = top 5 . sequence . map (filterP. norm) 
    where
        filterP (D x) = D [(a,p) | (a,p) <- x,p>0.0001]
        top n = vec2Dist . take n . reverse . presort p2 . unD
        vec2Dist x = D [(a,n / t) | (a,n)<- x] 
            where 
                t = sum (map p2 x)

-- Criteria for the probabilistic simulation of disqualification phase 
pkoCriteria (e1, e2) = D [((e1,1 − r2 / (r1 + r2)),(e2,1 − r1 / (r1 + r2)))]
    where
        r1 = rank e1
        r2 = rank e2

f = D . ((Nothing,0.5):) . map(Just >< (/2)) . unD . pkoCriteria

-- Auxiliar methods

best n = map p1 . take n . reverse . presort p2

consolidate :: (Num d,Eq d,Eq b) => [(b,d)] -> [(b,d)]
consolidate = map (id >< sum) . collect

collect :: (Eq a,Eq b) => [(a,b)] -> [(a,[b])]
collect x = [(a, [b | (a', b) <- x, a == a']) | (a, b) <- x]


-- Monadic binary function
mmbin :: Monad m => ((a,b) -> m c) -> (m a,m b) -> m c
mmbin f (a,b) = do {
    x <- a; 
    y <- b;
    f (x, y)}

-- Monadification of binary function
mbin :: Monad m => ((a,b) -> c) -> (m a,m b) -> m c
mbin = mmbin . (return .)