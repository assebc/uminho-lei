import Test.QuickCheck

import Data.List

-- exercise 1
mulL:: Num a => [a] -> a 
mulL [] = 1 -- changed (0 -> 1)
mulL [x] = x -- changed (added)
mulL (h:t) = h * mulL t

prop_mulL :: (Eq a, Num a) => [a] -> Bool
prop_mulL l = mulL(reverse l) == (mulL l)

prop_mulL2 :: (Eq a, Num a) => a -> Bool
prop_mulL2 x = mulL [x] == x

prop_mulL3 :: (Eq a, Num a) => [a] -> Bool
prop_mulL3 l = mulL l == product l

-- exercise 2
find' :: (a -> Bool) -> [a] -> Maybe a
find' f [] = Nothing
find' f (x:xs) = case find' f xs of
    Just k -> Just k
    Nothing -> if f x then Just x else Nothing

prop_find :: Eq a => (a -> Bool) -> [a] -> Bool
prop_find f l = find' f l == find f l