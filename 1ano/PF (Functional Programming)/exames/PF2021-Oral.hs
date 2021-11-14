type BD = [Video]

data Video = Filme String Int       -- título, ano

           | Serie String Int Int   -- título, temporada, episódio

           | Show  String Int       -- título, ano

           | Outro String

   deriving (Eq)

espectaculos :: BD -> [(String,Int)]
espectaculos [] = []
espectaculos ((Show t a):xs) = (t,a) : espectaculos xs

   
type Data = (Int,Int,Int)

type TempMin = Int

type TempMax = Int

type Registo = (Data , TempMin, TempMax)

data Temperaturas = Vazia 

                  | Nodo Registo Temperaturas Temperaturas


temps :: Temperaturas -> Data -> Maybe (TempMin,TempMax)
temps Vazia (_,_,_) = Nothing
temps (Nodo ((d,m,a),tm,tM) l r) (d1,m1,a1) = if (d1 == d && m1 == m && a1 == a) then Just (tm,tM) else temps r (d1,m1,a1)

func :: Int -> [Int] -> [[Int]]
func x l = map (:[]) (filter (\y -> x<y) l)

func2 :: Int -> [Int] -> [[Int]]
func2 n [] = []
func2 n (x:xs)
    | x > n = [x] : func2 n xs
    | otherwise = func2 n xs


