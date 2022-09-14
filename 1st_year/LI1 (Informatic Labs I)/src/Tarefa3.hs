{-|
Module      : Tarefa3
Description : Task 3 - Pacman: compacting the /Maze/ into /Instructions/
Copyright   : (c) Claudio Bessa, 2020
                  Ana Pires, 2020 
License     : GPL-3

= INTRODUCTION

This module aims to convert a Maze into a /Instruction's/ list to  give an easy reading. The difficult part of this task was 
finding an error on the /optimizeInstructions/ function. It was, briefly, executing on an infinite cycle. However, with some
patience and research we got rid of that infinite cycle, making it work properly.

= STRATEGY

An /Instruction/ is a /Tuplo's/ list, where the first value is an /Int/ and the second one is a /Piece/. After reading 
these instructions, the interpreter should return the /Maze/ (since the sum of all the Int should result in the /Maze's/ 
width and the length of that list must correspond to the /Maze's/ height). Our goal was to create a good compression function,
to minimize the number of /Instructions/ to be given towards the interpreter. With this in mind, we firstly create some funtions 
for convertions. We wanted to get /Duplos/ of pieces and their quantity from single pieces and get /Instructions/ not optimized 
from a /Maze/. Once the convertions were concluded, we examine if a certain /Instruction/ is valid and ultimately create the patterns 
(vertical and horizontal) with the optimized /Instructions/.  

= CONCLUSION

Much like the first task, this one wasn't very difficult either. We have successfully obtained a function that given a /Maze/ 
turns it into as few /Instructions/ lists as possible to give to the interpreter.

-}
{-# OPTIONS_HADDOCK prune #-}
module Tarefa3 where

import Tarefa1
import System.Random
import FileUtils
import TypesandDatas

-- ** Defining Instructions

-- | From a normal Piece, goes to a Duplo
pieceToDuplo :: Piece -> Duplo
pieceToDuplo p = (1, p)

-- | Turns a normal /Corridor/ into a Duplo's list
corridorToDuplos :: Corridor -> [Duplo]
corridorToDuplos [] = []
corridorToDuplos [c] = [pieceToDuplo c]
corridorToDuplos (c:cs) = (1,c): corridorToDuplos cs

-- | Turns a normal /Corridor/ into a list of Duplo's lists
mazeToDuplos :: Maze -> [[Duplo]] 
mazeToDuplos [] = []
mazeToDuplos [c] = [corridorToDuplos c]
mazeToDuplos (m:ms) = corridorToDuplos m : mazeToDuplos ms

-- | Turns Duplo's lists into a /Instruction/ not optimized
corridorToInstructions :: Corridor -> Instruction
corridorToInstructions [] = (Instruct[]) 
corridorToInstructions [c] = (Instruct [pieceToDuplo c])
corridorToInstructions c = (Instruct (corridorToDuplos c))

-- | After getting a normal maze transform it into /Instructions/ not optimized
mazeToInstructions :: Maze -> Instructions
mazeToInstructions [] = []
mazeToInstructions [m] = [corridorToInstructions m]
mazeToInstructions (m:ms) = corridorToInstructions m : mazeToInstructions ms

-- ** Verifying if the /Instructions/ are valid

-- | Aux that adds the quantity of total pieces
doubleSum :: [Duplo] -> Int
doubleSum [] = 0
doubleSum [x] = fst x
doubleSum (x:xs) = (fst x) + doubleSum xs

-- | Valid instructions for /Corridor/
validInstruction :: Corridor -> Instruction -> Bool
validInstruction [] (Instruct[]) = True
validInstruction [] (Instruct[a]) = False
validInstruction corr (Instruct[]) = False
validInstruction corr (Instruct[(x1,y1)]) = length corr == x1
validInstruction [x] (Instruct l) = doubleSum l == 1
validInstruction corr (Instruct ((n, p):(ns, ps):xs)) = length corr == n + ns + doubleSum xs 
                                            
-- | Valid /Instructions/ for /Maze/
validInstructions :: Maze -> Instructions -> Bool
validInstructions [] [Instruct[]] = True
validInstructions [] [Instruct[a]] = False
validInstructions maze [Instruct[]] = False
validInstructions [m] [Instruct l]= validInstruction m (Instruct l)
validInstructions (m:ms) (i:is) = (validInstruction m i) && (validInstructions ms is)

-- ** Building standards

-- | Turns the accumulator into a corridor of /Instruction/
optimizedInstructions :: [Duplo] -> Instruction
optimizedInstructions [] = Instruct []
optimizedInstructions [x] = Instruct [x]
optimizedInstructions (x:xs)= Instruct (duploaccum (x:xs))

-- | Accumulates /Instructions' Corridor/
duploaccum :: [Duplo] -> [Duplo] 
duploaccum  []= []
duploaccum [x] =  [x]
duploaccum (par1@(n,p):par2@(n1,p1):xs)
 | p == p1 = duploaccum ((n+n1,p1):xs)
 | otherwise = par1 : duploaccum (par2:xs)

-- | Turns the accumulator into a /Maze/ of /Instructions/
optimizedInstructionsm :: [[Duplo]] -> Instructions
optimizedInstructionsm [] = []
optimizedInstructionsm [[x]] = [Instruct [x]]
optimizedInstructionsm (x:xs)= optimizedInstructions x : optimizedInstructionsm xs

-- | Repeat /Instructions/ in every case
repeatInstructions :: Int -> Instructions -> Instructions
repeatInstructions n [] = []
repeatInstructions n [i] = [i]
repeatInstructions n (i:i1:is)
    | (poselem (i:i1:is) n) == (poselem (i:i1:is)) (n+1) = (take (n+1) (i:i1:is)) ++ (rInstructions n (drop n (i:i1:is)))
    | otherwise = (take (n+1) (i:i1:is)) ++ (rInstructions n (drop n (i:i1:is)))

-- | Put the /Repeat in/ on case
rInstructions :: Int -> Instructions -> Instructions
rInstructions n [i,is]
    | i == is = [Repeat n] 
    | otherwise = [is]
rInstructions n (i:i1:is)
    | i == i1 = (Repeat n) : rInstructions n (i:is)               
    | otherwise = i1:rInstructions n (i:is)

-- | Auxiliar function where we get the position of one /Instruction/ in a list of /Instructions'/ lists
poselem :: Instructions -> Int -> Instruction
poselem (x:xs) 0 = x
poselem (x:xs) n = poselem xs (n-1)

-- | Accumulates the compare fact between /Corridors/
accumR :: Int -> Instructions -> Instructions
accumR 0 l = repeatInstructions 0 l
accumR n [] = []
accumR n l = case (poselem l n) of Instruct x -> accumR (n+1) (repeatInstructions n l)
                                   Repeat x -> accumR (n+2) (repeatInstructions n l)

-- | Loop of accumR
generalcompact :: Instructions -> Instructions
generalcompact [] = accumR 0 []
generalcompact l = accumR 0 l 

-- ** Final function

-- | Transform a /Maze/ into the /Instructions/ method
compactMaze :: Maze -> Instructions
compactMaze [] = []
compactMaze maze = generalcompact (optimizedInstructionsm (mazeToDuplos maze))