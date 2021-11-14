{-|
Module      : TypesandDatas
Description : Auxiliar common functions 
-}
module TypesandDatas where

import Data.List

-- | state
data State = State 
    {
        maze :: Maze
    ,   playersState :: [Player]
    ,   level :: Int
    }

-- | list of corridors
type Maze = [Corridor]

-- | list of pieces
type Corridor = [Piece]

-- | types of pieces 
data Piece =  Food FoodType | PacPlayer Player| Empty | Wall deriving (Eq)

-- | player type: pacman or ghost
data Player =  Pacman PacState | Ghost GhoState deriving (Eq)

-- | orientation : left, right, up, down or null
data Orientation = L | R | U | D | Null deriving (Eq,Show)

-- | pacman state
data PacState = PacState 
    {   
        pacState :: PlayerState
    ,   timeMega :: Double
    ,   openClosed :: Mouth
    ,   pacmanMode :: PacMode
    
    } deriving Eq

-- | ghost state
data GhoState = GhoState 
    {
        ghostState :: PlayerState
    ,   ghostMode :: GhostMode
    } deriving Eq

-- | ghosts names
data AllGhosts = AllGhosts
    {
        clyde :: GhoState
    ,   blinky :: GhoState
    ,   inky :: GhoState
    ,   pinky :: GhoState

    } deriving Eq
-- | main manager
data Manager = Manager 
    {   
        state   :: State
    ,    pid    :: Int
    ,    step   :: Int
    ,    before :: Integer
    ,    delta  :: Integer
    ,    delay  :: Integer
    } 

-- | duplo
type Duplo = (Int, Piece)

-- | coords
type Coords = (Int,Int)

-- | player state
type PlayerState = (Int, Coords, Double , Orientation, Int, Int)
--                   (ID,  (x,y), velocity, orientation, points, lives)

-- | mouth open or closed               
data Mouth = Open | Closed deriving (Eq,Show)

-- | pacman mode
data PacMode = Dying | Mega | Normal deriving (Eq,Show)

-- | ghost mode
data GhostMode = Dead  | Alive deriving (Eq,Show)

-- | food type 
data FoodType = Big | Little deriving (Eq)

-- | colors
data Color = Blue | Green | Purple | Red | Yellow | None deriving Eq 

-- | play type
data Play = Move Int Orientation deriving (Eq,Show)

-- | list on instruction
type Instructions = [Instruction]

-- | duplo to instruction
data Instruction = Instruct [(Int, Piece)]
                 | Repeat Int deriving (Show, Eq)

-- | show State
instance Show State where
  show (State m ps p) = printMaze mz ++ "Level: " ++ show p ++ "\nPlayers: \n" ++ (foldr (++) "\n" (map (\y-> printPlayerStats y) ps))
                          where mz = placePlayersOnMap ps m
-- | show players state
instance Show PacState where
   show ( PacState s o m Dying  ) =  "X"
   show ( PacState (a,b,c,R,i,l) _ Open m  ) =  "{"
   show ( PacState (a,b,c,R,i,l) _ Closed m  ) =  "<"
   show ( PacState (a,b,c,L,i,l) _ Open m  ) =  "}"
   show ( PacState (a,b,c,L,i,l) _ Closed m  ) =  ">"
   show ( PacState (a,b,c,U,i,l) _ Open m  ) =  "V"
   show ( PacState (a,b,c,U,i,l) _ Closed m  ) =  "v"
   show ( PacState (a,b,c,D,i,l) _ Open m  ) =  "^"
   show ( PacState (a,b,c,D,i,l) _ Closed m  ) =  "|"
   show ( PacState (a,b,c,Null,i,l) _ Closed m  ) =  "<"
   show ( PacState (a,b,c,Null,i,l) _ Open m  ) =  "{"

-- | show player
instance Show Player where
   show ( Pacman x ) =  show x
   show ( Ghost x ) =   show x

-- | show ghost state
instance Show GhoState where
   show (GhoState x Dead ) =  "?"
   show (GhoState x Alive ) =  "M"

-- | show type of food
instance Show FoodType where
   show ( Big ) =  "o"
   show ( Little ) =  "."

-- | show type of piece
instance Show Piece where
   show (  Wall ) = coloredString "#" None
   show (  Empty ) = coloredString " " None
   show (  Food z ) = coloredString (show z )   Green
   show ( PacPlayer ( Pacman ( PacState (i, c, x, y,z,l) o m Normal ) ) ) = coloredString (show ( PacState (i, c, x, y,z,l) o m Normal)  ) Yellow
   show ( PacPlayer ( Pacman ( PacState (i, c, x, y,z,l) o m Mega   ) ) ) = coloredString (show ( PacState (i, c, x, y,z,l) o m Mega)  ) Blue
   show ( PacPlayer ( Pacman ( PacState (i, c, x, y,z,l) o m Dying   ) ) ) = coloredString (show ( PacState (i, c, x, y,z,l) o m Dying)  ) Red
   show ( PacPlayer (Ghost z) ) = coloredString (show z)  Purple

-- | Returns a String with a given color
coloredString :: String -> Color -> String
coloredString x y = x{-
    | y == Blue ="\x1b[36m" ++  x ++ "\x1b[0m"
    | y == Red = "\x1b[31m" ++ x ++ "\x1b[0m"
    | y == Green = "\x1b[32m" ++ x ++ "\x1b[0m"
    | y == Purple ="\x1b[35m" ++ x ++ "\x1b[0m"
    | y == Yellow ="\x1b[33m" ++ x ++ "\x1b[0m"
    | otherwise =  "\x1b[0m" ++ x-}


-- | Puts the  given players on the /Maze/ 
placePlayersOnMap :: [Player] -> Maze -> Maze
placePlayersOnMap [] x = x
placePlayersOnMap (x:xs) m = placePlayersOnMap xs ( replaceElemInMaze (getPlayerCoords x) (PacPlayer x) m )

-- | Plots the /Maze/ in graphical symbols 
printMaze :: Maze -> String
printMaze []  =  ""
printMaze (x:xs) = foldr (++) "" ( map (\y -> show y) x )  ++ "\n" ++ printMaze ( xs )

-- | Shows the /Player/ stats
printPlayerStats :: Player -> String
printPlayerStats p = let (a,b,c,d,e,l) = getPlayerState p
                     in "ID:" ++ show a ++  " Points:" ++ show e ++ " Lives:" ++ show l ++"\n"

-- | Get the /Player's/ identity (ID)
getPlayerID :: Player -> Int
getPlayerID (Pacman (PacState (x,y,z,t,h,l) q c d )) = x
getPlayerID  (Ghost (GhoState (x,y,z,t,h,l) q )) = x
 
-- | Get the /Player's/ points  
getPlayerPoints :: Player -> Int
getPlayerPoints (Pacman (PacState (x,y,z,t,h,l) q c d )) = h
getPlayerPoints (Ghost (GhoState (x,y,z,t,h,l) q )) = h

-- | Set the /Player's/ coordinates
setPlayerCoords :: Player -> Coords -> Player
setPlayerCoords (Pacman (PacState (x,y,z,t,h,l) q c d )) (a,b) = Pacman (PacState (x,(a,b),z,t,h,l) q c d )
setPlayerCoords (Ghost (GhoState (x,y,z,t,h,l) q )) (a,b) = Ghost (GhoState (x,(a,b),z,t,h,l) q )

-- | Get the /Player's/ actual coordinates
getPlayerCoords :: Player -> Coords
getPlayerCoords (Pacman (PacState (x,y,z,t,h,l) b c d )) = y
getPlayerCoords (Ghost (GhoState (x,y,z,t,h,l) b )) = y

-- | Get the /Player State's/ actual coordinates
getPlayerSCoords :: PlayerState -> Coords
getPlayerSCoords (x,y,z,t,h,l) = y

-- | Get /Pacman's/ out of a list 
getPacman :: [Player] -> Player
getPacman (p:ps) 
  | isPacman p = p
  | otherwise = getPacman ps

-- | Get /Ghosts'/ from list of players
getGhosts :: [Player] -> [Player]
getGhosts [] = []
getGhosts (p:ps) 
  | isPacman p /= True = p : getGhosts ps
  | otherwise = getGhosts ps

-- | Get /Pacman's/ mode (Dying | Mega | Normal) 
getPacmanMode :: Player -> PacMode
getPacmanMode (Pacman (PacState a b c d)) = d

-- | Get /Ghosts'/ mode (Dead | Alive) 
getGhostMode :: Player -> GhostMode
getGhostMode (Ghost (GhoState a d)) = d

-- | Get the /Player's/ state    
getPlayerState :: Player -> PlayerState
getPlayerState (Pacman (PacState a b c d )) = a
getPlayerState (Ghost (GhoState a b ))  = a

-- | Set the /Player's/ orientation
setPlayerOrientation :: Player -> Orientation -> Player
setPlayerOrientation (Pacman (PacState (x,y,z,t,h,l) q c d )) ori = Pacman (PacState (x,y,z,ori,h,l) q c d )
setPlayerOrientation (Ghost (GhoState (x,y,z,t,h,l) q )) ori = Ghost (GhoState (x,y,z,ori,h,l) q )

-- | Get the /Player's/ actual orientation
getPlayerOrientation :: Player -> Orientation
getPlayerOrientation (Pacman (PacState (x,y,z,t,h,l) q c d )) = t
getPlayerOrientation  (Ghost (GhoState (x,y,z,t,h,l) q )) = t

-- | Get /Piece's/ in the maze
getPiece :: Maze -> Coords -> Piece 
getPiece (a:as) (x,y) = (!!) ((!!) (a:as) (x)) (y)

-- | Get the /Piece's/ orientation
getPieceOrientation :: Piece -> Orientation
getPieceOrientation (PacPlayer p) =  getPlayerOrientation p
getPieceOrientation _ = Null

-- | Get the /Player's/ velocity
getPlayerVelocity :: Player -> Double
getPlayerVelocity (Pacman (PacState (x,y,z,t,h,l) q c d )) = z
getPlayerVelocity (Ghost (GhoState (x,y,z,t,h,l) q )) = z

-- | Put the given piece on the choosen coordinates, replacing the old one
replaceElemInMaze :: Coords -> Piece -> Maze -> Maze
replaceElemInMaze (a,b) _ [] = []
replaceElemInMaze (a,b) p (x:xs) 
  | a == 0 = replaceNElem b p x : xs 
  | otherwise = x : replaceElemInMaze (a-1,b) p xs

-- | Replace a specific element of a list with a given element
replaceNElem :: Int -> a -> [a] -> [a]
replaceNElem i _ [] = [] 
replaceNElem i el (x:xs)
  | i == 0 = el : xs 
  | otherwise =  x : replaceNElem (i-1) el xs

-- | Gets the time when the /Pacman/ is /Mega/
getTimeMega :: [Player] -> Double
getTimeMega (Pacman (PacState _ tm _ _) : xs) = tm
getTimeMega (x:xs) = getTimeMega xs

-- | Get the /Player's/ actual mouth status
getMouth :: Player -> Mouth
getMouth (Pacman (PacState (x,y,z,t,h,l) q c d )) = c

-- | Change the /Player's/ mouth status
changeinMouth :: Player -> Player
changeinMouth (Pacman (PacState (x,y,z,t,h,l) q Open d )) = (Pacman (PacState (x,y,z,t,h,l) q Closed d ))
changeinMouth (Pacman (PacState (x,y,z,t,h,l) q Closed d )) = (Pacman (PacState (x,y,z,t,h,l) q Open d ))

-- | Get step
getStep :: Manager -> Int
getStep (Manager (State maze (Pacman (PacState (x,y,z,t,h,l) q c d ):ap) ls) pid step bf delt del) = step

-- | See if the /Player's/ is Pacman
isPacman :: Player -> Bool
isPacman (Pacman _) = True
isPacman (Ghost _) = False

-- | Get /Maze's/ out of a /State's/
getMaze :: State -> Maze
getMaze (State m ap l) = m

-- | Get /Players'/ out of /State's/
getPlayers :: State -> [Player]
getPlayers (State m ap l) = ap