{-|
Module      : Tarefa6
Description : Task 6 - Pacman: Creating a bot
Copyright   : (c) Claudio Bessa, 2021
                  Ana Pires, 2021 
License     : GPL-3

= INTRODUCTION

This task's main objective in to implement an bot that plays the Pacman based on the 
current state of the game and that it performs a singular command using the type Play

= STRATEGY

Since we need to cover all aspects and all plays that /Pacman's/ can do it was a very long and careful task for us. For the
start we decided to divide this task in three, something look a like others tasks and for that we started when /Pacman/ is Mega.
After that we created a radar with a raio of 1 and looking for Food Fig, not finding that, it would go the direction more away from
the closest /Ghost/ that had Food Little, if there were no Food Little we would just run from /Ghosts/ till it find Food Big or Little.

= CONCLUSION

This was one of the hardest quests but for sure it was the one that brang us the most amount of errors and concerns about beucase it was 
the joint of the most important tasks.

-}
{-# OPTIONS_HADDOCK prune #-}
module Tarefa6 where 

import Data.List
import TypesandDatas
import Tarefa2
import Tarefa4
import Tarefa5

-- (State maze (Pacman (PacState (x,y,z,t,h,ls) tm m pm ):ap) l)
-- ((ID,  (y,x), velocity, orientation, points, lives), timemega, mouth, pacmode)

-- ** WHEN MEGA

-- | Get's closer /Ghost/ from /Pacman's/
goaway :: State -> Coords 
goaway state = (head (sortOn (distance coordsp) coordsg) )
    where
        coordsg = map (getPlayerCoords) (getGhosts (getPlayers state) ) -- get ghost
        coordsp = getPlayerCoords (getPacman (getPlayers state) ) -- get pacman 

-- | Run for /Ghosts'/ when Mega
sdistancePm :: Maze -> Orientation -> Coords -> Coords -> Orientation
sdistancePm maze U (x,y) c
    | (distance (x+1,y) c) <= min (distance c (x,y-1)) (distance c (x,y+1)) = D
    | (distance (x,y+1) c) <= min (distance c (x,y-1)) (distance c (x+1,y)) = R 
    | (distance (x,y-1) c) <= min (distance c (x+1,y)) (distance c (x,y+1)) = L 
sdistancePm maze D (x,y) c
    | (distance (x-1,y) c) <= min (distance c (x,y-1)) (distance c (x,y+1)) = U
    | (distance (x,y+1) c) <= min (distance c (x,y-1)) (distance c (x-1,y)) = R
    | (distance (x,y-1) c) <= min (distance c (x-1,y)) (distance c (x,y+1)) = L
sdistancePm maze R (x,y) c
    | (distance (x+1,y) c) <= min (distance c (x,y-1)) (distance c (x-1,y)) = D
    | (distance (x-1,y) c) <= min (distance c (x,y-1)) (distance c (x+1,y)) = U
    | (distance (x,y-1) c) <= min (distance c (x+1,y)) (distance c (x-1,y)) = L
sdistancePm maze L (x,y) c
    | (distance (x+1,y) c) <= min (distance c (x-1,y)) (distance c (x,y+1)) = D
    | (distance (x,y+1) c) <= min (distance c (x-1,y)) (distance c (x+1,y)) = R
    | (distance (x-1,y) c) <= min (distance c (x+1,y)) (distance c (x,y+1)) = U

-- | Final function when /Pacman's/ is Mega
chasemodeP :: State -> Int -> Play
chasemodeP s@(State maze pls lvl) id 
 | p == Wall = Move id (sdistance (getPlayerOrientation (getPacman pls) ) (getPlayerCoords(getPacman pls) ) (getPlayerCoords (idplayer id pls)) )
 | p /= Wall = Move id (getPlayerOrientation (getPacman pls))
    where
        p = nextPiece maze (getPlayerCoords (head(pls)) ) (getPlayerOrientation (head(pls))  )

-- ** RADAR OF PACMAN

-- | Run from /Ghosts'/ when not Mega
sdistancePM :: Maze -> Orientation -> Coords -> Coords -> Orientation
sdistancePM maze U (x,y) c
    | (distance (x+1,y) c) >= max (distance c (x,y-1)) (distance c (x,y+1)) && getPiece maze (x+1,y) == Wall = sdistancePM maze U (x,y) c
    | (distance (x,y+1) c) >= max (distance c (x,y-1)) (distance c (x+1,y)) && getPiece maze (x,y+1) == Wall = sdistancePM maze U (x,y) c
    | (distance (x,y-1) c) >= max (distance c (x+1,y)) (distance c (x,y+1)) && getPiece maze (x,y-1) == Wall = sdistancePM maze U (x,y) c
    | (distance (x+1,y) c) >= max (distance c (x,y-1)) (distance c (x,y+1)) = D
    | (distance (x,y+1) c) >= max (distance c (x,y-1)) (distance c (x+1,y)) = R
    | (distance (x,y-1) c) >= max (distance c (x+1,y)) (distance c (x,y+1)) = L 
sdistancePM maze D (x,y) c
    | (distance (x-1,y) c) >= max (distance c (x,y-1)) (distance c (x,y+1)) && getPiece maze (x-1,y) == Wall = sdistancePM maze D (x,y) c
    | (distance (x,y+1) c) >= max (distance c (x,y-1)) (distance c (x-1,y)) && getPiece maze (x,y+1) == Wall = sdistancePM maze D (x,y) c
    | (distance (x,y-1) c) >= max (distance c (x-1,y)) (distance c (x,y+1)) && getPiece maze (x,y-1) == Wall = sdistancePM maze D (x,y) c
    | (distance (x-1,y) c) >= max (distance c (x,y-1)) (distance c (x,y+1)) = U
    | (distance (x,y+1) c) >= max (distance c (x,y-1)) (distance c (x-1,y)) = R
    | (distance (x,y-1) c) >= max (distance c (x-1,y)) (distance c (x,y+1)) = L
sdistancePM maze  R (x,y) c
    | (distance (x+1,y) c) >= max (distance c (x,y-1)) (distance c (x-1,y)) && getPiece maze (x+1,y) == Wall = sdistancePM maze R (x,y) c
    | (distance (x-1,y) c) >= max (distance c (x,y-1)) (distance c (x+1,y)) && getPiece maze (x-1,y) == Wall = sdistancePM maze R (x,y) c
    | (distance (x,y-1) c) >= max (distance c (x+1,y)) (distance c (x-1,y)) && getPiece maze (x,y-1) == Wall = sdistancePM maze R (x,y) c
    | (distance (x+1,y) c) >= max (distance c (x,y-1)) (distance c (x-1,y)) = U
    | (distance (x-1,y) c) >= max (distance c (x,y-1)) (distance c (x+1,y)) = D
    | (distance (x,y-1) c) >= max (distance c (x+1,y)) (distance c (x-1,y)) = L
sdistancePM maze L (x,y) c
    | (distance (x+1,y) c) >= max (distance c (x-1,y)) (distance c (x,y+1)) && getPiece maze (x+1,y) == Wall = sdistancePM maze L (x,y) c
    | (distance (x,y+1) c) >= max (distance c (x-1,y)) (distance c (x+1,y)) && getPiece maze (x,y+1) == Wall = sdistancePM maze L (x,y) c
    | (distance (x-1,y) c) >= max (distance c (x+1,y)) (distance c (x,y+1)) && getPiece maze (x-1,y) == Wall = sdistancePM maze L (x,y) c
    | (distance (x+1,y) c) >= max (distance c (x-1,y)) (distance c (x,y+1)) = D
    | (distance (x,y+1) c) >= max (distance c (x-1,y)) (distance c (x+1,y)) = R
    | (distance (x-1,y) c) >= max (distance c (x+1,y)) (distance c (x,y+1)) = U 

-- | See /Pieces'/ around /Pacman's/ in a radar of 1 
radar :: Maze -> PlayerState -> Piece -> Coords
radar maze ps@(id,(y,x),z,t,h,ls) piece
        | (piece == piece1 ) = radarn maze ps piece1
        | (piece == piece2) = radarn maze ps piece2
        | otherwise = (y,x) 
            where
                piece1 = (Food Big) -- 1 of 2 pieces we are looking for
                piece2 = (Food Little) -- 2 of 2 pieces we are looking for

-- | See /Pieces'/ around /Pacman's/ in a radar of 1 in all orientation's
radarn :: Maze -> PlayerState -> Piece -> Coords
radarn maze (id,(y,x),z,t,h,ls) piece
    | piece == Food Big && t == R && (nextPiece maze (y,x) R) == piece = (y,x+1)
    | piece == Food Big && t == L && (nextPiece maze (y,x) L) == piece = (y,x-1)
    | piece == Food Big && t == U && (nextPiece maze (y,x) U) == piece = (y+1,x)
    | piece == Food Big && t == D && (nextPiece maze (y,x) D) == piece = (y-1,x)
    | piece == Food Little && t == R && (nextPiece maze (y,x) R) == piece = (y,x+1)
    | piece == Food Little && t == L && (nextPiece maze (y,x) L) == piece = (y,x-1)
    | piece == Food Little && t == U && (nextPiece maze (y,x) U) == piece = (y+1,x)
    | piece == Food Little && t == D && (nextPiece maze (y,x) D) == piece = (y-1,x)
    | otherwise = (y,x)
 
-- | Restricted radar when close to limits
radarR :: Maze -> Player -> Piece -> Coords
radarR maze p piece
    | (isPacman p) && restrict = radar maze pacstate piece
    | otherwise = coords            
        where
            restrict = coords /= (heightL1e,(snd coords))
                    && coords /= (heightL2e,(snd coords))
                    && coords /= ((fst coords),corridorL1e)
                    && coords /= ((fst coords),corridorL2e)
            heightL1e = (length maze - 1) -- inside the restricted zone down
            heightL2e = (1) -- inside the restricted zone up
            corridorL1e = (length (head maze) - 1) -- inside the restricted zone rigth
            corridorL2e = (1) -- inside the restricted zone left
            pacstate = (getPlayerState p) -- get pacstate
            coords = (getPlayerCoords p) -- get pacman coords

-- ** WHEN THERE ARE FOOD BIG

-- | If there are /Food Big's/ around /Pacman's/ radar goes that way
pacmanshow :: Maze -> Player -> Piece -> Coords -> Orientation 
pacmanshow maze p@(Pacman (PacState (id,(y,x),z,t,h,ls) tm m pm )) piece (y1,x1)
    | (piece == Food Big ) && (radarR maze p piece) /= (y,x) && (y1 > y) = U
    | (piece == Food Big ) && (radarR maze p piece) /= (y,x) && (y1 < y) = D
    | (piece == Food Big ) && (radarR maze p piece) /= (y,x) && (x1 < x) = L
    | (piece == Food Big ) && (radarR maze p piece) /= (y,x) && (x1 > x) = R
    | otherwise = t

-- | Search for a /Food Big's/ in radar and do a play
searchFB :: State -> Piece -> Play
searchFB state piece 
    | p == Wall = (Move id (sdistance ori coords cfb) )  
    | p /= Wall = (Move id ofb)
    | otherwise = (Move id ori) 
        where
            p = nextPiece maze coords ori -- get next piece
            ofb = (pacmanshow maze pacman piece cfb ) -- orientation for the Food Big
            cfb = (radarR maze pacman piece) -- coords of the Food Big
            maze = (getMaze state) -- state maze
            pacman = (getPacman (getPlayers state) ) -- get pacman
            id = (getPlayerID (getPacman (getPlayers state) ) ) -- get pacman id
            coords = (getPlayerCoords (getPacman (getPlayers state) ) ) -- get pacman coords
            ori = (getPlayerOrientation (getPacman (getPlayers state) ) ) -- get pacman orientation               

-- | Checks if there are /Food Big's/ in radar
checksFB :: Maze -> Coords -> Bool
checksFB maze (y,x) = getPiece maze (y+1,x) == (Food Big) 
                    || getPiece maze (y-1,x) == (Food Big) 
                    || getPiece maze (y,x+1) == (Food Big) 
                    || getPiece maze (y,x-1) == (Food Big)

-- ** WHEN THERE ARE NO FOOD BIG

-- | If there are /Food Little's/ around /Pacman's/ radar goes that way
notpacmanshow :: Maze -> Player -> Piece -> Coords -> Orientation 
notpacmanshow maze p@(Pacman (PacState (id,(y,x),z,t,h,ls) tm m pm )) piece (y1,x1)
    | (piece == Food Little ) && (radarR maze p piece) /= (y,x) && (y1 > y) = U
    | (piece == Food Little ) && (radarR maze p piece) /= (y,x) && (y1 < y) = D
    | (piece == Food Little ) && (radarR maze p piece) /= (y,x) && (x1 < x) = L
    | (piece == Food Little ) && (radarR maze p piece) /= (y,x) && (x1 > x) = R
    | otherwise = t
        where

-- | Search for a /Food Little's/ in radar and do a play
searchFL :: State -> Piece -> Play
searchFL state piece 
    | p == Wall = (Move id (sdistance ori coords cfb) )  
    | p /= Wall = (Move id ofb)
    | otherwise = (Move id ori) 
        where
            p = nextPiece maze coords ori -- get next piece
            ofb = (notpacmanshow maze pacman piece cfb ) -- orientation for the Food Big
            cfb = (radarR maze pacman piece) -- coords of the Food Big
            maze = (getMaze state) -- state maze
            pacman = (getPacman (getPlayers state) ) -- get pacman
            id = (getPlayerID (getPacman (getPlayers state) ) ) -- get pacman id
            coords = (getPlayerCoords (getPacman (getPlayers state) ) ) -- get pacman coords
            ori = (getPlayerOrientation (getPacman (getPlayers state) ) ) -- get pacman orientation   

-- | Checks if there are /Food Little's/ in radar
checksFL :: Maze -> Coords -> Bool
checksFL maze (y,x) = getPiece maze (y+1,x) == (Food Little) 
                    || getPiece maze (y-1,x) == (Food Little) 
                    || getPiece maze (y,x+1) == (Food Little) 
                    || getPiece maze (y,x-1) == (Food Little) 

-- ** FINAL FUNCTION

-- | Final Function without when /Pacman's/ is not Mega
botFood :: Int -> State -> Play
botFood idr state
    | checksFB maze coords && id == idr = searchFB state piece1
    | checksFL maze coords && id == idr = searchFL state piece2
    | otherwise = (Move id med ) 
        where
            piece1 = (Food Big) -- 1 of 2 pieces we are looking for
            piece2 = (Food Little) -- 2 of 2 pieces we are looking for
            med = (sdistancePM maze ori coords coordsg) -- orientation to run from pacman
            maze = (getMaze state) -- state maze
            id = (getPlayerID (getPacman (getPlayers state) ) ) -- get pacman id
            ori = (getPlayerOrientation (getPacman (getPlayers state) ) ) -- get pacman orientation
            coords = (getPlayerCoords (getPacman (getPlayers state) ) ) -- get pacman coords
            coordsg = goaway state

-- | Final function
bot :: Int -> State -> Maybe Play
bot idr state
    | timega == 0 = Just (botFood id state)
    | pacmode == Mega = Just (chasemodeP state id)
    | p == Empty = Just (Move id ori)
    | pacmode == Normal = Just (botFood id state)
    | otherwise = Just (Move id ori)
        where
            p = nextPiece maze coords ori -- get next piece
            maze = (getMaze state) -- state maze
            pacmode = (getPacmanMode (getPacman (getPlayers state) ) ) -- get pacmode
            id = (getPlayerID (getPacman (getPlayers state) ) ) -- get pacman id
            coords = (getPlayerCoords (getPacman (getPlayers state) ) ) -- get pacman coords
            ori = (getPlayerOrientation (getPacman (getPlayers state) ) ) -- get pacman orientation
            timega = (getTimeMega (getPlayers state) )   

-- | Turns bot plays into actual plays
maybeToPlay :: Maybe Play -> Play
maybeToPlay (Just p) = p

-- | Make the bot play
auxpTB :: Int -> [Player] -> State -> State
auxpTB step [] state = state
auxpTB step (p:ps) state
    | isPacman p == True && (getPlayerVelocity p == 0.5) && (odd step) = auxpTB step ps state
    | isPacman p == True && (getPlayerVelocity p == 0.5) && (even step) && (step > 0) = auxpTB step ps (play (maybeToPlay (bot (getPlayerID p) state)) state)
    | isPacman p == True && (getPlayerVelocity p == 1) = auxpTB step ps (play (maybeToPlay (bot (getPlayerID p) state)) state)
    | isPacman p == False && (getPlayerVelocity p == 0.5) && (odd step) = auxpTB step ps state
    | isPacman p == False && (getPlayerVelocity p == 0.5) && (even step) && (step > 0) = auxpTB step ps (play (ghostsPlay getID playofghost) state)
    | isPacman p == False && (getPlayerVelocity p == 1) = auxpTB step ps invoghostplays
    | otherwise = auxpTB step ps state
        where
            getID = (getPlayerID p)
            playofghost = (ghostPlay state)
            invoghostplays = (play (ghostsPlay (getPlayerID p) (ghostPlay state)) state)

-- | Final Function for the bot
passTimeBot :: Int  -> State -> State
passTimeBot step state@(State m (p:ap) ls) = auxpTB step (p:ap) state 