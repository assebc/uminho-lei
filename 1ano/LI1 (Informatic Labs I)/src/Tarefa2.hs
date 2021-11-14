{-|
Module      : Tarefa2
Description : Task 2 - Pacman: creating /Plays/
Copyright   : (c) Claudio Bessa, 2020
                  Ana Pires, 2020 
License     : GPL-3

= INTRODUCTION

In this task we wanted to set the function /Play/, where given the current state of the game and a movement made by a player, 
it determines the subsequent state of the game. Of all the tasks in the first part of the project, this was undoubtedly the most
challenging. 
 
= STRATEGY

Here, we had to consider several variants: the /Players/ (that can be /Ghost's/ or a /Pacman's/), their states (in other words,
their identification, coordinates, velocity, orientation, points and number of remaining lifes) and the actions (for example,
if the /Player/ is a /Pacman/ and there's a small consumable next to him, it should move for that position, eat the food and win one 
more point). In this task, we had to define each subject and it's sub-divisions precisely so that we could evaluate each move's 
possibilities. However, in this module We only set the /Plays/ for the /Pacman/, as requested by the teaching team. 

= CONCLUSION

This task was one of the most crucial ones, since it was this step that allowed us to start reaching the end result. We
were successful in thinking and getting all the cases for a /Play/. Although we are happy with the results, we believe that our
code could be cleaner and simplified.

-}
{-# OPTIONS_HADDOCK prune #-}
module Tarefa2 where 

import Tarefa1
import TypesandDatas
import FileUtils

-- ((ID,  (y,x), velocity, orientation, points, lives), timemega, mouth, pacmode)
-- Coords are (y,x) to be equal to the test program

-- ** All players or pacman management

-- | Creates the identification (id) of a /Player/
idplayer :: Int -> [Player] -> Player 
idplayer nplayer [x] = x
idplayer nplayer ((Pacman (PacState ps t o pacman)):xs) 
    | nplayer == getPlayerID p = p
    | otherwise = idplayer nplayer xs 
        where
            p = (Pacman (PacState ps t o pacman))
idplayer nplayer ((Ghost (GhoState ps deadoralive)):xs) 
    | nplayer == getPlayerID g = g
    | otherwise = idplayer nplayer xs
        where
            g = (Ghost (GhoState ps deadoralive))


-- | Do the /Pacman's/ path
absorvePiece :: Maze -> Coords -> Maze 
absorvePiece maze@(m:ms) (y,x) = replaceElemInMaze (y,x) (Empty) maze

-- | Returns the piece before some coords
nextPiece :: Maze -> Coords -> Orientation -> Piece 
nextPiece maze (y,x) o = case o of R -> (maze!!y)!!(x+1)
                                   L -> (maze!!y)!!(x-1)
                                   U -> (maze!!(y-1))!!(x)
                                   D -> (maze!!(y+1))!!(x)

-- | Checks if there's a piece next
pieceNext :: Maze -> Coords -> Orientation -> Bool                             
pieceNext maze@(m:ms) (y,x) orientation 
    | x == 0 && L == orientation = True
    | x == ((length(m))-1) && R == orientation = True
    | otherwise = False

-- | Verify if there is a ghost in certain coords
spookyscary :: [Player] -> Coords -> Bool 
spookyscary [] coords = False
spookyscary (p1:ps) coords = (getPlayerCoords p1) == coords || spookyscary ps coords

-- | See if a Ghost is dead or alive
checkghost :: Player -> GhostMode
checkghost (Ghost (GhoState ps deadoralive)) = deadoralive

-- | Select the ghost from the list of /Players/
chooseGhost :: [Player] -> Coords -> Player
chooseGhost (p1:ps) coords  
    | getPlayerCoords p1 == coords = p1
    | otherwise = chooseGhost ps coords

-- | Adds a new /Player/ into the /Maze/ in certain orientation
newplayer :: Player -> Orientation -> Player
newplayer (Pacman (PacState (id, coords, v, or, p, l) t o pacman)) orientation = (Pacman (PacState (id, coords, v, orientation, p, l) t o pacman))
newplayer (Ghost (GhoState (id, coords, v, or, p, l) deadoralive)) orientation = (Ghost (GhoState (id, coords, v, orientation, p, l) deadoralive))

-- | Substitues /Players/
subPlayer :: Player ->  [Player]  -> [Player]
subPlayer p [] = []
subPlayer p@(Pacman (PacState p1 t o pacman)) (ps@((Pacman (PacState p2 t2 o2 pacman2))):xs) 
        | getPlayerID p == getPlayerID ps = p:xs
subPlayer p@(Ghost (GhoState p1 deadoralive)) (ps@(Ghost (GhoState p2 deadoralive2)):xs)                   
        | getPlayerID p == getPlayerID ps = p:xs 
subPlayer p (x:xs) = x:(subPlayer p xs) 

-- | Pass through the empty tunel to the other side of the /Maze/
coordstunnel :: Coords -> Maze -> Coords 
coordstunnel (y,x) maze@(m:ms) 
    | x == 0 = (y,(length(m))-1)
    | x == (length(m))-1 = (y,0)
    | otherwise = (y,x)

-- | Transform the coords with an eye on the orientation
auxo :: Orientation -> Coords -> Coords
auxo L (y,x) = (y,(x-1))
auxo R (y,x) = (y,(x+1))
auxo U (y,x) = ((y-1),x)
auxo D (y,x) = ((y+1),x)

-- | Add integers into score of /Players/
addscore :: Int -> Player -> Player
addscore n (Pacman (PacState (id, coords, v, or, points, l) t o pacman)) = (Pacman (PacState (id, coords, v, or, points+n, l) t o pacman))
addscore n (Ghost (GhoState (id, coords, v, or, points, l) pacman)) = (Ghost (GhoState (id, coords, v, or, points+n, l) pacman))

-- | Takes lives from /Players/, when 0 equals Dying
lives :: Player -> Player 
lives (Pacman (PacState (id, coords, v, or, p, life) t o pacman))
    | life > 0 = (Pacman (PacState (id, coords, v, or, p, life+(-1)) t o pacman))
    | otherwise = (Pacman (PacState (id, coords, v, or, p, 0) t o Dying))

-- | Takes lives from /Pacman's/, when hitting /Ghost's/
liv :: [Player] -> [Player]
liv ps@(p:ap)
    | isPacman p = lives p : ap
    | otherwise = p : liv ap

-- ** Ghosts management

-- | Changes /Ghost's/ orientation when they're death
changeGhostOrientation :: PlayerState  -> PlayerState
changeGhostOrientation (i, c, v , o, p, l) = (i, c, v, opositeDirection o, p, l)
    where 
        opositeDirection L = R
        opositeDirection R = L
        opositeDirection U = D
        opositeDirection D = U
        opositeDirection Null = Null
        
-- | Turns all ghosts to dead
allghostsdead :: [Player] -> [Player]
allghostsdead [] = []
allghostsdead ((Ghost (GhoState (i, c, v , o, p, l) deadoralive)):xs) = (Ghost (GhoState (changeGhostOrientation (i, c, 0.5 , o, p, l)) Dead)):(allghostsdead xs)
allghostsdead ((Pacman (PacState p t o pacman)):xs) = (Pacman (PacState p t o pacman)):(allghostsdead xs)

-- | Turns all ghosts to alive
allghostsalive :: [Player] -> [Player]
allghostsalive [] = []
allghostsalive ((Ghost (GhoState (i, c, v , o, p, l) deadoralive)):xs) = (Ghost (GhoState ((i, c, 1 , o, p, l)) Alive)):(allghostsalive xs)
allghostsalive ((Pacman (PacState p t o pacman)):xs) = (Pacman (PacState p t o pacman)):(allghostsalive xs)

-- | Changes the state of a ghost to alive
aliveghost :: Player -> Player
aliveghost (Ghost (GhoState p deadoralive)) = (Ghost (GhoState p Alive))
aliveghost (Pacman (PacState p t o deadoralive)) = (Pacman (PacState p t o deadoralive)) 

-- | Turns into mega
turnsmega :: Player -> Player 
turnsmega (Ghost gs) = Ghost gs
turnsmega (Pacman (PacState ps t o Normal))  = (Pacman (PacState ps 10000 o Mega))
turnsmega (Pacman ps) = Pacman ps

-- | Auxiliar of turnsNormal
pacmanNormal :: Player -> Player
pacmanNormal (Pacman (PacState ps tm m pm)) = Pacman (PacState ps tm m Normal)

-- | Turn /Pacman/ into /Normal/ again
turnsNormal :: Int -> [Player] -> [Player]
turnsNormal id [] = []
turnsNormal id (x:xs) 
 | id == getPlayerID x = pacmanNormal x : xs
 | otherwise = x : turnsNormal id xs

-- ** Final Functions

-- | Do a /Play/ if it's valid
validPlay :: Play -> State -> State
validPlay (Move id o) (State maze ap l)
    | wallnotinfront && isPacman (selectPlayer) /= True && getPiece (PacPlayer (getPacman ap) ) && (ghost Alive) = killingpacman  
    | wallnotinfront && isPacman (selectPlayer) /= True = ghostmove
    | not(wallnotinfront) && isPacman (selectPlayer) /= True = (State maze (subPlayer (newplayer selectPlayer o) ap) l)               
    | wallnotinfront && (ghost Alive) = hitingghost
    | wallnotinfront && (ghost Dead) = hitingghost2  
    | wallnotinfront && (ghost Dead) && getPiece (Food Little) = eatingfoodlittleM
    | wallnotinfront && (ghost Dead) && getPiece (Food Big)  = eatingfoodbigM
    | wallnotinfront && getPiece (Food Little) = eatingfoodlittle
    | wallnotinfront && getPiece (Food Big) = eatingfoodbig 
    | wallnotinfront = (State maze (subPlayer move ap) l)   
    | otherwise = (State maze (subPlayer (newplayer selectPlayer o) ap) l)                                                                            
        where
            selectPlayer = (idplayer id ap)
            notWall = (Wall /= (nextPiece maze (getPlayerCoords selectPlayer) o)) 
            wallnotinfront = o == (getPlayerOrientation selectPlayer) && notWall
            getPiece p = (p == (nextPiece maze (getPlayerCoords selectPlayer) o))
            path = (absorvePiece maze (auxo o (getPlayerCoords(selectPlayer))))
            move = (setPlayerCoords selectPlayer (auxo o (getPlayerCoords selectPlayer)))
            doublespeed = ((aliveghost(selectghost)))
            ghostrider = (setPlayerCoords doublespeed (y,x))
            addscore1 = (addscore 1 move) 
            addscore5 = (addscore 5 (turnsmega move))
            addscore10 = (addscore 10 move)
            addscore11 = (addscore 11 move)
            addscore15 = (turnsmega(addscore 15 move))
            eatingfoodlittle = (State path (subPlayer addscore1 ap) l)
            eatingfoodbig = (State path (allghostsdead((subPlayer addscore5 ap))) l)
            killingpacman = (State maze (liv (subPlayer move ap) ) l)
            ghostmove = (State maze (subPlayer move ap) l)
            hitingghost = (State maze (subPlayer (lives move) ap) l)
            hitingghost2 = (State maze (subPlayer ghostrider (subPlayer addscore10 ap)) l)
            eatingfoodlittleM = (State path (subPlayer ghostrider (subPlayer addscore11 ap)) l)
            eatingfoodbigM = (State path (subPlayer ghostrider (subPlayer addscore15 ap)) l)
            ghost g = spookyscary ap (auxo o (getPlayerCoords selectPlayer)) && g == checkghost selectghost
            selectghost = (chooseGhost ap (auxo o (getPlayerCoords selectPlayer)))
            (y,x) | odd (length maze) && odd (length (head maze)) = ((div (length maze) 2),(div (length (head maze)) 2))
                  | odd (length maze) && even (length (head maze)) = ((div (length maze) 2),(div (length (head maze)) 2)-1)
                  | even (length maze) && odd (length (head maze)) = ((div (length maze) 2)-1,(div (length (head maze)) 2))
                  | even (length maze) && even (length (head maze)) = ((div (length maze) 2)-1,(div (length (head maze)) 2)-1)

-- | Do all the /Plays/ with all conditions
play :: Play -> State -> State
play (Move id o) (State maze ap l)
    | getPacmanMode(getPacman ap) == Dying = (State maze ap l)
    | isPacman (idplayer id ap) == False = validPlay (Move id o) (State maze ap l)
    | emptytunnels && getTimeMega ap == 0 = (State maze (turnsNormal id (subPlayer (setPlayerCoords selectPlayer (coordstunnel (getPlayerCoords selectPlayer) maze)) ap)) l)
    | emptytunnels = (State maze (subPlayer (setPlayerCoords selectPlayer (coordstunnel (getPlayerCoords selectPlayer) maze)) ap) l)
    | getTimeMega ap == 0 = (State m (allghostsalive (turnsNormal id pls)) lvl)
    | otherwise = validPlay (Move id o) (State maze ap l)
        where 
              (State m pls lvl) = validPlay (Move id o) (State maze ap l)
              selectPlayer = (idplayer id ap)
              emptytunnels = pieceNext maze (getPlayerCoords(selectPlayer)) o