{-|
Module      : Tarefa4
Description : Task 4 - Pacman: Reacts in base with /time/
Copyright   : (c) Claudio Bessa, 2021
                  Ana Pires, 2021
License     : GPL-3

= INTRODUCTION

In this task, we intended to calculate the time's effect on the game's state. To do so, we needed to define the function /passTime/, 
which given a step and the actual game's state, it updates the game's state after a repetition. The most difficult part was making 
the /Ghosts/ move.

= STRATEGY

This task's goals are to define time and its influences on the game. In which we wanted to make the /Players/ move after the time 
set so we could register a new movement. To accomplish that, we have to consider some restrictions, such as: time cant stop, and by
that we mean that the /Player's/ need to be moving acoording to the time always. So for the starting point we decided to after make /Pacman's/
moving around we would be defining its' time Mega and when finishing, done in Task 2, and afterwards just define what time a movements it does 
with some restrictions such as step velocity. Also in this task we started in doing movements for /Ghosts/ as well.

= CONLUSION

Despite the difficulties we felt with regard to the players' movements, especially the /Ghosts/, we believe that we did a great job in the way
that this was the more difficult task after Task 6 and Task 2 and was the one that took as the more time to figure it how to do it.

-}
{-# OPTIONS_HADDOCK prune #-}
module Tarefa4 where 

import TypesandDatas
import Tarefa2
import Tarefa5

-- (Manager (State maze (Pacman (PacState (x,y,z,t,h,l) q c d ):ap) ls) pid step bf delt del)
-- ((ID,  (y,x), velocity, orientation, points, lives), timemega, mouth, pacmode)

-- | 250 ms is the default delay time
defaultDelayTime = 250

-- | Compare /Step's/ before and after Mega
comparesteps :: Int -> Int -> Bool
comparesteps step steps = steps == step + 40

-- | Make the /Players'/ move around
walkonthengbh :: Player -> State -> State
walkonthengbh p state@(State m ps lvl)
    | getPlayerOrientation p == R = play (Move (getPlayerID p) R) state
    | getPlayerOrientation p == L = play (Move (getPlayerID p) L) state
    | getPlayerOrientation p == U = play (Move (getPlayerID p) U) state
    | getPlayerOrientation p == D = play (Move (getPlayerID p) D) state
    | otherwise = state

-- | Update time Mega
updateTimeMega :: Double -> Player -> Player
updateTimeMega x (Pacman (PacState ps tm m pm)) = Pacman (PacState ps (tm-x) m pm)

-- | Auxiliar of reduceTimeMega
reduceTM :: [Player] -> [Player]
reduceTM [] = []
reduceTM (p:ps)
    | isPacman p = updateTimeMega 250 p : ps
    | otherwise = p : reduceTM ps

-- | Reduces time Mega 
reduceTimeMega :: State -> State
reduceTimeMega (State maze ap ls) = (State maze (reduceTM ap) ls)

-- ** FINAL FUNCTION

-- | Auxiliar of final function
auxpT :: Int -> [Player] -> State -> State
auxpT step [] state = state
auxpT step (p:ps) state
    | isPacman p == True && (getPlayerVelocity p == 0.5) && (odd step) = auxpT step ps state
    | isPacman p == True && (getPlayerVelocity p == 0.5) && (even step) && (step > 0) = auxpT step ps (walkonthengbh p state)
    | isPacman p == True && (getPlayerVelocity p == 1) = auxpT step ps (walkonthengbh p state)
    | isPacman p == False && (getPlayerVelocity p == 0.5) && (odd step) = auxpT step ps state
    | isPacman p == False && (getPlayerVelocity p == 0.5) && (even step) && (step > 0) = auxpT step ps (play (ghostsPlay getID playofghost) state)
    | isPacman p == False && (getPlayerVelocity p == 1) = auxpT step ps invoghostplays
    | otherwise = auxpT step ps state
        where
            getID = (getPlayerID p)
            playofghost = (ghostPlay state)
            invoghostplays = (play (ghostsPlay (getPlayerID p) (ghostPlay state)) state)

-- | Final Function
passTime :: Int  -> State -> State
passTime step state@(State m (p:ap) ls) = auxpT step (p:ap) state 