import Test.QuickCheck

prop_invert :: Eq a => [a] -> Bool
prop_invert xs = reverse (reverse xs) == xs

prop_capicua :: [Int] -> Bool
prop_capicua xs = reverse xs == xs

prop_palindrome :: String -> Bool
prop_palindrome xs = reverse xs == xs

prop_sum :: (Num a, Eq a) => [a] -> Bool
prop_sum xs = sum (reverse xs) == sum xs

prop_length :: [a] -> Bool
prop_length xs = length (reverse xs) == length xs 

prop_len :: [a] -> Property
prop_len l = not (null l) ==> length (tail l) + 1 == length l

number :: Gen Int 
number = do n <- arbitrary
            return n

date :: Gen (Int,Int,Int)
date = do d <- choose (1,31)
          m <- elements [1..12]
          y <- elements [1900..2023]
          return (d,m,y)

fstSem = elements [1..6]
sndSem = elements [7..12]

date2 :: Gen (Int,Int,Int)
date2 = do d <- choose (1,31)
           m <- frequency [(3,fstSem),(1,sndSem)]
           y <- elements [1900..2023]
           return (d,m,y)

data Age = Age Int deriving Show
type Name = String
data Person = Person Name Age deriving Show

instance Arbitrary Age where
    arbitrary = genAge

genAge :: Gen Age
genAge = do age <- choose (0,100)
            return (Age age)

genPerson = do n <- elements ["John", "Bob"]
               a <- arbitrary
               return (Person n a)

data Insc = Regular | TE | Militar | Craque deriving Show
data Student = Student Name Int Insc [Float] deriving Show

genStudent = do nome <- elements ["Ana", "To", "Ze", "Maria"]
                numero <- choose (1,100000) 
                inscr <- frequency [(79, return Regular), (15, return TE), (5, return Militar)]
                notas <- vectorOf 6 (choose (0,20))
                return (Student nome numero inscr notas)

-- another class

intersperse' :: a -> [a] -> [a]
intersperse' x [] = []
intersperse' x [a] = [a]
intersperse' x (h:t) = h : x : intersperse' x t

prop_inter :: a -> [a] -> Property
prop_inter s l = not (null l) ==> 
                length(intersperse' s l) == ((length l * 2) - 1)