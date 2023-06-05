import Data.List
import Test.QuickCheck
import Text.Printf
import System.IO
import System.Directory (removeFile)
import Control.Monad

data SmartBulb = SmartBulb String Integer Float deriving Show
data SmartCamera = SmartCamera String Integer Float deriving Show
data SmartSpeaker = SmartSpeaker Integer String String Float deriving Show

vectorOfDistinct :: (Eq a) => Int -> Gen a -> Gen [a]
vectorOfDistinct n gen = vectorOf n gen >>= return . nub

genRandomFloat :: Gen Float
genRandomFloat = choose (1, 20)

genName :: Gen String
genName = do
    f_name <- elements ["João", "José", "Alberto", "Rui", "Marcelo", "Joana", "Ana", "Maria", "Sofia", "Ines"]
    l_name <- elements ["Mesquita", "Santos", "Bessa", "Silva", "Matos", "Freitas", "Martins", "Costa", "Cunha", "Ribeiro"]
    return (f_name ++ " " ++ l_name)

genResolution :: Gen String
genResolution = elements ["(1280x720)","(1980x1080)","(2160x1440)","(1024x768)","(3840x2160)","(1366x768)"]

genFornecedorAux :: Gen String
genFornecedorAux = elements ["EDP", "Iberdola", "Endesa", "Gold Energy", "MEO Energia", "SU Eletricidade"]

genFornecedor :: Gen String
genFornecedor = do
    forn <- genFornecedorAux
    return ("Fornecedor:" ++ forn)

genFornecedor2 :: [String] -> Gen String
genFornecedor2 forns = do
    return $ intercalate "\n" $ map (\f -> "Fornecedor:" ++ f) forns

genSmartBulbAux :: Gen SmartBulb
genSmartBulbAux = do 
    mode <- elements ["Cold", "Neutral", "Warm"]
    dimension <- choose (1,25)
    consume <- genRandomFloat
    return (SmartBulb mode dimension consume)

genSmartBulb :: Gen String
genSmartBulb = do
    sb <- genSmartBulbAux
    let (SmartBulb mode dimension consume) = sb 
    return $ printf "SmartBulb:%s,%d,%.2f" mode dimension consume

genSmartCameraAux :: Gen SmartCamera
genSmartCameraAux = do
    res <- genResolution
    dimension <- choose (10, 200)
    consume <- genRandomFloat
    return (SmartCamera res dimension consume)

genSmartCamera :: Gen String
genSmartCamera = do
    sc <- genSmartCameraAux
    let (SmartCamera res dimension consume) = sc
    return $ printf "SmartCamera:%s,%d,%.2f" res dimension consume

genSmartSpeakerAux :: Gen SmartSpeaker
genSmartSpeakerAux = do
    vol <- choose (0,100)
    name <- elements ["RFM", "MEGAHITS", "Radio Comercial", "RUM", "TSF", "Radio Renascenca", "Radio Santiago"]
    brand <- genMarcaAux
    consume <- genRandomFloat
    return (SmartSpeaker vol name brand consume)

genSmartSpeaker:: Gen String
genSmartSpeaker = do
    ss <- genSmartSpeakerAux
    let (SmartSpeaker vol name brand consume) = ss
    return $ printf "SmartSpeaker:%d,%s,%s,%.2f" vol name brand consume

genMarcaAux :: Gen String
genMarcaAux = elements ["JBL", "Marshall", "Sony", "LG", "XIAOMI", "Goodis", "Sonos", "Echo", "Apple", "Bose", "Anker", "Alcatel", "Amazon"]

genMarca :: Gen String
genMarca = do
    brand <- genMarcaAux
    consume <- genRandomFloat
    return $ printf "Marca:%s,%.2f" brand consume

genDivisao :: Gen String
genDivisao = do 
    division <- elements["Ninho", "Sala", "Cozinha", "Quarto", "Suite", "Corredor", "Casa de Banho", "Hall", "Escritorio", "Jardim", "Garagem"]
    return ("Divisao:" ++ division)

genCasa :: Gen String
genCasa = do 
    name <- genName
    nif <- vectorOf 9 (elements ['0'..'9'])
    fornecedor <- genFornecedorAux
    return ("Casa:" ++ name ++ "," ++ nif ++ "," ++ fornecedor)

genCasa2 :: String -> Gen String
genCasa2 fornecedor = do 
    name <- genName
    nif <- vectorOf 9 (elements ['0'..'9'])
    return ("Casa:" ++ name ++ "," ++ nif ++ "," ++ fornecedor)

genCasa3 :: [String] -> Gen String
genCasa3 fornecedores = do
    name <- genName
    nif <- vectorOf 9 (elements ['0'..'9'])
    fornecedor <- elements fornecedores
    return ("Casa:" ++ name ++ "," ++ nif ++ "," ++ fornecedor)

genHouse :: [String] -> Gen [String]
genHouse forns = do
    n <- choose (1, 3)
    divisions <- replicateM n $ do
        division <- genDivisao
        n1 <- choose (0, 5)
        n2 <- choose (0, 5)
        n3 <- choose (0, 5)
        smartBulbs <- replicateM n1 genSmartBulbAux
        smartCameras <- replicateM n2 genSmartCameraAux
        smartSpeakers <- replicateM n3 genSmartSpeakerAux
        let smartBulbsStr = map (\(SmartBulb mode dimension consume) -> printf "SmartBulb:%s,%d,%.2f" mode dimension consume) smartBulbs
        let smartCamerasStr = map (\(SmartCamera res dimension consume) -> printf "SmartCamera:%s,%d,%.2f" res dimension consume) smartCameras
        let smartSpeakersStr = map (\(SmartSpeaker vol name brand consume) -> printf "SmartSpeaker:%d,%s,%s,%.2f" vol name brand consume) smartSpeakers
        return ([division] ++ smartBulbsStr ++ smartCamerasStr ++ smartSpeakersStr)
    casa <- vectorOf 1 (genCasa3 forns)
    let casaStr = head casa
    return (casaStr : concat divisions)

clear :: IO()
clear = do
    let file = "data.txt"
    removeFile file

main :: IO()
main = do 
    file <- openFile "data.txt" WriteMode

    forns <- generate (vectorOfDistinct 3 genFornecedorAux)

    fornecedores <- generate (vectorOf 1 (genFornecedor2 forns))
    city <- generate (vectorOf 3 (genHouse forns))
    
    mapM_ (hPutStrLn file) fornecedores
    mapM_ (hPutStrLn file) (concat city)

    hClose file



