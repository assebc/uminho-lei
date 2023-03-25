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


-- exercise 3

prop_positive :: Int -> Property
prop_positive x = x > 0 ==> (x * x * x) > 0

sorted' :: Ord a => [a] -> Bool
sorted' l = and (zipWith (<=) l (tail l))

insert' :: Ord a => a -> [a] -> [a]
insert' x [] = [x]
insert' x (y:ys)
    | x<y = x:y:ys
    | otherwise = y:insert x ys

prop_ins_ord :: Int -> [Int] -> Property
prop_ins_ord x l = sorted' l ==> sorted' (insert' x l)

prop_ins_ord2 :: Int -> [Int] -> Property
prop_ins_ord2 x l = collect (length l) $ sorted' (insert' x l)

prop_ins_ord_A :: Int -> Property
prop_ins_ord_A x = forAll orderedList (\l -> sorted' (insert' x l))

-- exercise 4

data BST = Empty | Node BST Int BST deriving Show

instance Eq BST where
  Empty == Empty = True
  Node a l r == Node b l' r' = a == b && l == l' && r == r'
  _ == _ = False

fromList :: [Int] -> BST
fromList [] = Empty
fromList (x:xs) = Node Empty x (fromList xs)

isBST :: BST -> Bool
isBST Empty = True
isBST (Node l x r) = isBST l && isBST r 
                && maybeBigger (Just x) (maybeMax l)
                && maybeBigger (maybeMin r) (Just x)
    where 
        maybeBigger _ Nothing = True
        maybeBigger Nothing _ = True
        maybeBigger (Just x) (Just y) = x >= y
        maybeMax Empty = Nothing
        maybeMax (Node _ x Empty) = Just x
        maybeMax (Node _ _ r) = maybeMax r
        maybeMin Empty = Nothing
        maybeMin (Node Empty x _) = Just x
        maybeMin (Node l _ _) = maybeMin l

genBST :: Gen BST
genBST = do
    l <- listOf arbitrary
    let l_sorted = sort l
    return (fromList l_sorted)

instance Arbitrary BST where
    arbitrary = genBST

prop_valid_BST :: Property
prop_valid_BST = forAll genBST $ \bst -> isBST bst

balanced :: BST -> Bool
balanced Empty = True
balanced (Node l x r) = abs(height l - height r) <= 1 && balanced l && balanced r    

fromList2 :: [Int] -> BST
fromList2 [] = Empty
fromList2 xs = Node (fromList2 l) x (fromList2 r)
    where
        n = length xs
        (l, x:r) = splitAt (div n 2) xs

prop_balanced :: Property
prop_balanced = forAll (listOf arbitrary) $ \xs -> balanced (fromList2 xs)

height :: BST -> Int
height Empty = 1
height (Node l _ r) = 1 + max (height l) (height r)

prop_height_x :: Property
prop_height_x = forAll genBST $ \bst -> height bst > 0

mirror :: BST -> BST
mirror Empty = Empty
mirror (Node l x r) = Node (mirror r) x (mirror l)

prop_mirror :: Property
prop_mirror = forAll genBST $ \bst -> mirror (mirror bst) == bst 

incBST :: BST -> BST 
incBST Empty = Empty
incBST (Node l x r) = Node (incBST l) (x+1) (incBST r)

prop_isBST :: Property
prop_isBST = forAll genBST $ \bst -> isBST (incBST bst)

-- exercise 5

-- zip function
f :: [a] -> [b] -> [(a,b)]
f [] _ = []
f _ [] = []
f (x:xs) (y:ys) = (x,y) : f xs ys

-- return [] if one of them is []
prop_f1 :: [a] -> Bool
prop_f1 l1 = null (f l1 []) && null (f [] l1)

-- length f l1 l2 == length of smaller list because of pairs
prop_f2 :: [a] -> [b] -> Bool
prop_f2 l1 l2 = length (f l1 l2) == min (length l1) (length l2)

-- which list has the smallest length has all members in the result pairs' list
prop_f3_1, prop_f3_2 :: (Eq a, Eq b) => [a] -> [b] -> Property
prop_f3_1 l1 l2 = length l1 < length l2 ==> l1 == map fst (f l1 l2)
prop_f3_2 l1 l2 = length l1 > length l2 ==> l2 == map snd (f l1 l2)

prop_fzip :: Property
prop_fzip = forAll (listOf arbitrary) $ \l1 ->
            forAll (listOf arbitrary) $ \l2 ->
            (f l1 l2) == (zip l1 l2 :: [(Int, Int)])