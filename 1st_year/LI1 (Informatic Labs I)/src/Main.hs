{-|
Module      : Main
Description : All Tasks
-}
{-# OPTIONS_HADDOCK prune #-}
module Main where

import Data.Time.Clock.POSIX
import Control.Monad.IO.Class
import UI.NCurses
import TypesandDatas
import FileUtils
import Tarefa1
import Tarefa2
import Tarefa3
import Tarefa4
import Tarefa5
import Tarefa6

-- (Manager (State maze (Pacman (PacState (x,y,z,t,h,l) q c d ):ap) l) pid step bf delt del)

-- | Loads maze
loadManager :: Manager
loadManager = ( Manager (loadMaze "maps/4.txt") 0 0 0 0 defaultDelayTime )

-- | Set orientation with key   
rotateplayer :: Key -> Orientation
rotateplayer key 
    | key == KeyLeftArrow = L
    | key == KeyUpArrow = U
    | key == KeyRightArrow = R
    | key == KeyDownArrow = D
    | otherwise = Null

-- | Controlls the player being the auxiliar of updateControlledPlayer
controlPlayer :: Orientation -> Int -> State -> State
controlPlayer ori pid state@(State maze (Pacman (PacState (x,y,z,t,h,ls) q c d ):ap) l)
    | pid == x = (State maze (Pacman (PacState (x,y,z,ori,h,ls) q c d ):ap) l)
    | otherwise = controlPlayer ori pid (State maze (ap ++ [(Pacman (PacState (x,y,z,t,h,ls) q c d ))]) l)
controlPlayer ori pid s@(State maze (Ghost (GhoState (x,y,z,t,h,ls) d ):ap) l)
    | pid == x = (State maze (Ghost (GhoState (x,y,z,ori,h,ls) d ):ap) l)
    | otherwise = controlPlayer ori pid (State maze (ap ++ [(Ghost (GhoState (x,y,z,ori,h,ls) d ))]) l)

-- | Update player controlled orientation
updateControlledPlayer :: Key -> Manager -> Manager
updateControlledPlayer key man@(Manager (State maze ap l) pid step bf delt del) = (Manager (controlPlayer (rotateplayer key) (getPlayerID(getPacman ap)) state) pid step bf delt del)
  where
    state = (State maze ap l)
    
-- | Visual updates player
updateScreen :: Window  -> ColorID -> Manager -> Curses ()
updateScreen w a man =
                  do
                    updateWindow w $ do
                      clear
                      setColor a
                      moveCursor 0 0 
                      drawString $ show (state man)
                    render

-- | Current time in map 
currentTime :: IO Integer
currentTime = fmap ( round . (* 1000) ) getPOSIXTime

-- | Updates delta
updateTime :: Integer -> Manager -> Manager
updateTime now man@(Manager s pid step bf delt del) = (Manager s pid step bf (now-bf) del)

-- | Resets deltas
resetTimer :: Integer -> Manager -> Manager
resetTimer now man@(Manager s pid step bf delt del)
    | delta < del = (Manager s pid step bf (now-bf) del) 
    | otherwise = (Manager s pid step now 0 del)
        where
            delta = now - bf

-- | Updates state 
nextFrame :: Integer -> Manager -> Manager
nextFrame now (Manager state pid step bef del delay) = Manager (reduceTimeMega (passTime step state)) pid (step+1) now 0 delay

-- | Movements
loop :: Window -> Manager -> Curses ()
loop w man@(Manager s pid step bf delt del ) = do 
  color_schema <- newColorID ColorWhite ColorDefault 10
  now <- liftIO  currentTime
  updateScreen w  color_schema man
  if ( delt > del )
    then loop w $ nextFrame now man
    else do
          ev <- getEvent w $ Just 0
          case ev of
                Nothing -> loop w (updateTime now man)
                Just (EventSpecialKey arrow ) -> loop w $ updateControlledPlayer arrow (updateTime now man)
                Just ev' ->
                  if (ev' == EventCharacter 'q')
                    then return ()
                    else loop w (updateTime now man)

-- | Running maze
main :: IO ()
main =
  runCurses $ do
    setEcho False
    setCursorMode CursorInvisible
    w <- defaultWindow
    loop w loadManager

