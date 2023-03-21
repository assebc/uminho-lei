import Test.QuickCheck

genNota :: Gen Word
genNota = choose (0,20)

genNota' :: Gen Word
genNota' = elements [0..20]

genMarca:: Gen String
genMarca = frequency [(120, return "Renault"), (85, return "Mercedes"), (12, return "Porsche"),(4, return "Ferrari")]

type Marca = String

--brands = [return "Audi", return "BMW", return "Buick", return "Cadillac", return "Chevrolet", return "Chrysler", return "Dodge", return "Ferrari", return "Ford", return "GM", return "GEM", return "GMC", return "Honda", return "Hummer", return "Hyundai",  return "Infiniti", return "Isuzu", return "Jaguar", return "Jeep", return "Kia", return "Lamborghini", return "Land Rover", return "Lexus", return "Lincoln", return "Lotus", return "Mazda", return "Mercedes-Benz", return "Mercury", return "Mitsubishi", return "Nissan", return "Oldsmobile", return "Peugeot", return "Pontiac", return "Porsche", return "Regal", return "Saab", return "Saturn", return "Subaru", return "Suzuki", return "Toyota", return "Volkswagen", return "Volvo"]

type Matricula = String
type NIF = String -- NIF Proprietario
type CPKm = Float -- Consumo por Km
type Autonomia = Int

data Tipo = Combustao | Eletrico | Hibrido deriving Show

data Carro = Carro Tipo Marca Matricula NIF CPKm Autonomia deriving Show

-- exercise 1a

genTipo :: Gen Tipo
genTipo = frequency [(70,return Combustao),(25, return Hibrido), (5, return Eletrico)]

-- exercise 1b
genCPKm :: Gen CPKm
genCPKm = choose (0.1,2.0)

-- exercise 1c
genAutonomia :: Gen Autonomia
genAutonomia = choose (500,800)

-- exercise 1d
--genMarca :: Gen Marca
--genMarca :: elements brands

-- exercise 1e
genMatricula :: Gen Matricula
genMatricula = do 
    p1 <- vectorOf 2 (choose ('A','Z'))
    p2 <- vectorOf 2 (choose ('0','9'))
    p3 <- vectorOf 2 (choose ('0','9'))
    return (p1 ++ "-" ++ p2 ++ "-" ++ p3)

-- exercise 1f
genCarro :: [NIF] -> Gen Carro
genCarro xs = do
    tipo <- genTipo
    marca <- genMarca
    matricula <- genMatricula
    nif <- elements xs
    cpkm <- genCPKm
    autonomia <- genAutonomia
    return (Carro tipo marca matricula nif cpkm autonomia) 


-- exercise 3

data Expr = Add Expr Expr
          | Mul Expr Expr
          | Const Float
            deriving Show

-- 80 add & 20 mul / 50/50 aritmathic expression or constant value




-- exercise 3a
genExpr :: Gen Expr
genExpr = do 
    expr1 <- genExpr
    expr2 <- genExpr
    n <- arbitrary
    operation <- frequency [
                    (80, return (Add expr1 expr2)), 
                    (20, return (Mul expr1 expr2))
                    ]
    expr_const <- frequency [
                    (50, return (Const n)),
                    (50, return operation)
                    ]
    return (expr_const)
