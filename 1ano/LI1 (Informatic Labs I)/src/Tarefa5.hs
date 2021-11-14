{-|
Module      : Tarefa5
Description : Task 5 - Pacman: /Ghosts/ Movement
Copyright   : (c) Claudio Bessa, 2021
                  Ana Pires, 2021 
License     : GPL-3

= INTRODUCTION

This task's main objective is to implement moves for the /Ghosts/ as well. 

= STRATEGY

The most effective way to obtain moves from the /Ghosts/, was to add play function conditions.
However, this is insubstantial. Their moves must react to Pacman's moves accordingly, since the 
movement of the /Ghosts/ is dictated by /Pacman's/ state. Given his /Normal/ state, they must chase him; 
oppositely, the /Ghosts/ must run away when /Pacman/ changes his state to the /Mega/ state. Hence is 
determined that when the /Ghosts/ are in the Alive mode, they are also in chaseMode, otherwise (Dead mode),
in scatterMode. To achieve effective chasing dexterity, the /Ghosts/ must locate the best, shortest path 
to reach /Pacman/. To do so, we implemented a function to calculate that path. Another required restriction, 
is to know how will Pacman react upon hitting a wall: he will have to rotate his directional movement to the 
right (in other words: if he's moving to the right, then, upon hitting a wall, he will now change to a downwards 
trajectory. Same applies to all other directions).

= CONCLUSION

We believe that this task was successful, since we did all of the game's demanded restrictions in an efficient 
manner. As far as we are concerned, this was the best way to conclude the task.

-}
{-# OPTIONS_HADDOCK prune #-}
module Tarefa5 where 

import TypesandDatas
import Tarefa2

--((ID,  (y,x), velocity, orientation, points, lives), timemega, mouth, pacmode)

-- ** WHEN THE GHOSTS ARE ALIVE (chasemode)

-- | Calculates the shortest distance between two players
distance :: Coords -> Coords -> Float
distance (x1,y1) (x2,y2) = sqrt( ( ( (fromIntegral x1) - (fromIntegral x2) )^2 ) + ( ( (fromIntegral y1) - (fromIntegral y2) )^2) )

-- | Auxiliar of chasemode
sdistance :: Orientation -> Coords -> Coords -> Orientation
sdistance U (x,y) pm
    | (distance (x+1,y) pm) <= min (distance pm (x,y-1)) (distance pm (x,y+1)) = D
    | (distance (x,y+1) pm) <= min (distance pm (x,y-1)) (distance pm (x+1,y)) = R
    | (distance (x,y-1) pm) <= min (distance pm (x+1,y)) (distance pm (x,y+1)) = L
sdistance D (x,y) pm
    | (distance (x-1,y) pm) <= min (distance pm (x,y-1)) (distance pm (x,y+1)) = U
    | (distance (x,y+1) pm) <= min (distance pm (x,y-1)) (distance pm (x-1,y)) = R
    | (distance (x,y-1) pm) <= min (distance pm (x-1,y)) (distance pm (x,y+1)) = L
sdistance R (x,y) pm
    | (distance (x+1,y) pm) <= min (distance pm (x,y-1)) (distance pm (x-1,y)) = D
    | (distance (x-1,y) pm) <= min (distance pm (x,y-1)) (distance pm (x+1,y)) = U
    | (distance (x,y-1) pm) <= min (distance pm (x+1,y)) (distance pm (x-1,y)) = L
sdistance L (x,y) pm
    | (distance (x+1,y) pm) <= min (distance pm (x-1,y)) (distance pm (x,y+1)) = D
    | (distance (x,y+1) pm) <= min (distance pm (x-1,y)) (distance pm (x+1,y)) = R
    | (distance (x-1,y) pm) <= min (distance pm (x+1,y)) (distance pm (x,y+1)) = U

-- | Final function when /Ghosts'/ are Alive
chasemode :: State -> Int -> Play
chasemode s@(State maze pls lvl) id 
 | p == Wall = Move id (sdistance (getPlayerOrientation (idplayer id pls)) (getPlayerCoords (idplayer id pls)) (getPlayerCoords(getPacman pls)))
 | p /= Wall = Move id (getPlayerOrientation (idplayer id pls))
    where
        p = nextPiece maze (getPlayerCoords (head(pls)) ) (getPlayerOrientation (head(pls))  )

-- ** WHEN THE GHOSTS ARE DEATH (scattermode)

-- | Rotation clockwise when death
clockwisedead :: Orientation -> Orientation
clockwisedead ori = case ori of R -> D
                                D -> L
                                L -> U
                                U -> R

-- | Final function when /Ghosts'/ are Dead
scattermode :: State -> Int -> Play
scattermode state@(State maze (g:gs) l) id 
    | p == Wall = (Move id (clockwisedead (getPlayerOrientation (idplayer id (g:gs)) ) ) )
    | p /= Wall = (Move id (getPlayerOrientation (idplayer id (g:gs)) ) )
    | otherwise = scattermode state id 
        where
           p = nextPiece maze (getPlayerCoords g) (getPlayerOrientation g)

-- ** FINAL FUNCTION

-- | Same as the function (!!)
list :: [a] -> Int -> a
list (x:xs) y 
    | y == 0 = x
    | otherwise = list xs (y-1)

-- | Final Function
ghostPlay :: State -> [Play]
ghostPlay state@(State maze [x] l) = []
ghostPlay state@(State maze (g:gs) l)
    | isPacman g = ghostPlay (State maze (gs ++ [g]) l)
    | getGhostMode g == Alive = chasemode state (getPlayerID g) : ghostPlay (State maze gs l)
    | getGhostMode g  == Dead = scattermode state (getPlayerID g) : ghostPlay (State maze gs l)
    | otherwise = ghostPlay state

-- | Plays of different /Ghosts'/
ghostsPlay :: Int -> [Play] -> Play
ghostsPlay idr (Move id ori :xs)
 | idr == id = Move id ori
 | otherwise = ghostsPlay idr xs